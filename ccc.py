#!/usr/bin/env python3
""" cContinue Transpiler v0.1.0
"""

import argparse
import copy
from dataclasses import dataclass
import logging
import os
import platform
import re
import subprocess
import sys
import tempfile
from typing import Dict, List, Optional


@dataclass
class Field:
    """Class field metadata"""

    name: str
    type: str
    default: Optional[str]
    attributes: Dict[str, List[str]]
    class_: str


@dataclass
class Argument:
    """Argument metadata"""

    name: str
    type: str


@dataclass
class Method:
    """Class method metadata"""

    name: str
    return_type: str
    is_virtual: bool
    arguments: List[Argument]
    class_: str
    origin_class: str


class Class:
    """Class metadata"""

    name: str
    snake_name: str
    parent_name: Optional[str]
    is_abstract: bool
    fields: Dict[str, Field]
    methods: Dict[str, Method]

    def __init__(self, name: str, parent_name: Optional[str]) -> None:
        self.name = name
        self.snake_name = to_snake_case(name)
        self.parent_name = parent_name
        self.is_abstract = False
        self.fields = {}
        self.methods = {}


include_paths: List[str] = []
classes: Dict[str, Class] = {}


def file_read(path: str) -> str:
    """Read file"""
    with open(path, "r", encoding="utf-8") as file:
        return file.read()


def file_write(path: str, text: str) -> None:
    """Write file"""
    with open(path, "w", encoding="utf-8") as file:
        file.write(text)


def to_snake_case(camel_case: str) -> str:
    """Camel case to snake case"""
    string = "".join(["_" + char.lower() if char.isupper() else char for char in camel_case])
    return string[1:] if string.startswith("_") else string


def find_class_for_method(class_: Class, method_name: str) -> Class:
    """Find first class that implements method"""
    if class_.methods[method_name].class_ == class_.name:
        return class_
    if class_.parent_name is None:
        logging.error("No class implements method: %s", method_name)
        sys.exit(1)
    return find_class_for_method(classes[class_.parent_name], method_name)


class ConvertInclude:
    """Convert class"""

    def __init__(self, current_path: str) -> None:
        self.current_path = current_path

    def __call__(self, match: re.Match[str]) -> str:
        """Convert include"""
        base_path = f"{match.groups()[0]}.hh"
        for include_path in include_paths:
            complete_path = f"{include_path}/{base_path}"
            if os.path.exists(complete_path):
                is_header = base_path.endswith(".hh") and os.path.abspath(complete_path) != os.path.abspath(
                    self.current_path.replace(".cc", ".hh")
                )
                return transpile_text(complete_path, is_header, file_read(complete_path))
        logging.error("Can't find include: %s", base_path)
        sys.exit(1)


class ConvertClass:
    """Convert class"""

    def __init__(self, is_header: bool) -> None:
        self.is_header = is_header

    def __call__(self, match: re.Match[str]) -> str:
        # ==== Indexing ====
        class_name, extends_str, contents = match.groups()

        # Get parent class
        parent_name = None if class_name == "Object" else "Object"
        if extends_str is not None:
            parent_name = extends_str[1:].strip()

        parent_class = None
        if parent_name is not None:
            if parent_name not in classes:
                logging.error("Can't find parent class %s for %s", parent_name, class_name)
                sys.exit(1)
            parent_class = classes[parent_name]

        # Create class object
        class_ = Class(class_name, parent_name)
        if parent_class is not None:
            class_.fields = copy.deepcopy(parent_class.fields)
            class_.methods = copy.deepcopy(parent_class.methods)
        classes[class_.name] = class_

        # Index fields
        for field_parts in re.findall(r"(.+[^=][\s|\*])([_A-Za-z][_A-Za-z0-9]*)\s*(=\s*[^;]+)?;", contents):
            attributes_and_type_str, name, default_str = field_parts

            # Parse attributes
            attributes = {}

            def convert_attribute(match: re.Match[str]) -> str:
                name, arguments = match.groups()
                if arguments is not None:
                    attributes[name] = [  # pylint: disable=cell-var-from-loop
                        argument.strip() for argument in arguments[1 : len(arguments) - 1].split(",")
                    ]
                else:
                    attributes[name] = []  # pylint: disable=cell-var-from-loop
                return ""

            field_type = re.sub(
                r"@([_A-Za-z][_A-Za-z0-9]*)(\([^\)]*\))?",
                convert_attribute,
                attributes_and_type_str,
            ).strip()

            # Add field to class
            if name in class_.fields:
                logging.error("Can't inherit field: %s", name)
                sys.exit(1)
            class_.fields[name] = Field(
                name, field_type, default_str[1:].strip() if default_str != "" else None, attributes, class_.name
            )

        # Index methods
        for method_parts in re.findall(
            r"([_A-Za-z][_A-Za-z0-9 ]*[\**|\s+])\s*([_A-Za-z][_A-Za-z0-9]*)\(([^\)]*)\)\s*(=\s*0)?;",
            contents,
        ):
            return_type, name, arguments_str, is_zero = method_parts

            arguments = []
            if arguments_str != "":
                for argument_str in arguments_str.split(","):
                    argument_parts = re.search(
                        r"([_A-Za-z][_A-Za-z0-9 ]*[\**|\s+])\s*([_A-Za-z][_A-Za-z0-9]*)",
                        argument_str,
                    )
                    if argument_parts is not None:
                        arguments.append(Argument(argument_parts[2].strip(), argument_parts[1]))

            is_virtual = False
            if "virtual " in return_type:
                return_type = return_type.replace("virtual ", "")
                is_virtual = True

            if is_zero != "":
                if is_virtual:
                    class_.is_abstract = True
                else:
                    logging.error("Only virtual methods can be set to zero: %s", name)
                    sys.exit(1)

            if name in class_.methods:
                class_.methods[name].return_type = return_type
                class_.methods[name].arguments = arguments
                class_.methods[name].class_ = class_.name
            else:
                class_.methods[name] = Method(name, return_type, is_virtual, arguments, class_.name, class_.name)

        # ==== Generate missing methods ====
        g = ""
        if parent_class is not None:
            # Init method
            field_needs_init = next(
                (field for field in class_.fields.values() if "init" in field.attributes or field.default is not None),
                None,
            )
            if class_.methods["init"].class_ != class_.name and field_needs_init is not None:
                class_.methods["init"].class_ = class_.name
                class_.methods["init"].arguments = [
                    Argument(field.name, field.type) for field in class_.fields.values() if "init" in field.attributes
                ]

                init_method = class_.methods["init"]
                parent_init_method = classes[parent_class.name].methods["init"]

                g += f"void _{class_.snake_name}_init("
                g += ", ".join(
                    [f"{class_.name}* this"]
                    + [f"{argument.type} {argument.name}" for argument in init_method.arguments]
                )
                g += ") {\n"
                g += f"    {parent_class.snake_name}_init("
                g += ", ".join(["this"] + [argument.name for argument in parent_init_method.arguments])
                g += ");\n"
                for field in class_.fields.values():
                    if field.class_ == class_.name:
                        if field.default is not None:
                            g += f"    this->{field.name} = {field.default};\n"
                        if "init" in field.attributes:
                            if len(field.attributes["init"]) > 0:
                                g += f"    this->{field.name} = {field.attributes['init'][0]}({field.name});\n"
                            else:
                                g += f"    this->{field.name} = {field.name};\n"
                g += "}\n\n"

            # Free method
            field_needs_free = next((field for field in class_.fields.values() if "free" in field.attributes), None)
            if class_.methods["free"].class_ != class_.name and field_needs_free is not None:
                class_.methods["free"].class_ = class_.name

                g += f"void _{class_.snake_name}_free({class_.name}* this) {{\n"
                for field in class_.fields.values():
                    if field.class_ == class_.name and "free" in field.attributes:
                        if len(field.attributes["free"]) > 0:
                            g += f"    {field.attributes['free'][0]}(this->{field.name});\n"
                        else:
                            for other_class in classes.values():
                                if field.type.startswith(other_class.name):
                                    g += f"    {other_class.snake_name}_free(this->{field.name});\n"
                                    break
                            else:
                                g += f"    free(this->{field.name});\n"
                class_with_free = find_class_for_method(classes[parent_class.name], "free")
                g += f"    _{class_with_free.snake_name}_free(({class_with_free.name}*)this);\n"
                g += "}\n\n"

            # Get attribute
            for field in class_.fields.values():
                if field.class_ == class_.name and ("get" in field.attributes or "prop" in field.attributes):
                    method_name = f"get_{field.name}"
                    class_.methods[method_name] = Method(method_name, field.type, False, [], class_.name, class_.name)

                    g += f"{field.type} _{class_.snake_name}_get_{field.name}({class_.name}* this) {{\n"
                    g += f"    return this->{field.name};\n"
                    g += "}\n\n"

            # Set attribute
            for field in class_.fields.values():
                if field.class_ == class_.name and ("set" in field.attributes or "prop" in field.attributes):
                    method_name = f"set_{field.name}"
                    class_.methods[method_name] = Method(
                        method_name, "void", False, [Argument(field.name, field.type)], class_.name, class_.name
                    )

                    g += f"void _{class_.snake_name}_set_{field.name}({class_.name}* this, "
                    g += f"{field.type} {field.name}) {{\n"
                    g += f"    this->{field.name} = {field.name};\n"
                    g += "}\n\n"

            # New method
            if not class_.is_abstract:
                init_method = class_.methods["init"]
                g += f"{class_.name}* {class_.snake_name}_new("
                if len(init_method.arguments) > 0:
                    g += ", ".join([f"{argument.type} {argument.name}" for argument in init_method.arguments])
                else:
                    g += "void"
                g += (
                    ") {\n"
                    + f"    {class_.name}* this = malloc(sizeof({class_.name}));\n"
                    + f"    this->vtbl = &_{class_.name}Vtbl;\n"
                    + f"    {class_.snake_name}_init("
                    + ", ".join(["this"] + [argument.name for argument in init_method.arguments])
                    + ");\n"
                    + "    return this;\n"
                    + "}\n\n"
                )

        # ==== Codegen ====

        # Class Vtbl struct
        c = f"typedef struct {class_.name} {class_.name};\n\n"
        c += f"typedef struct {class_.name}Vtbl {{\n"
        current_class_name = ""
        for method in class_.methods.values():
            if method.is_virtual:
                if method.origin_class != current_class_name:
                    c += f"    // {method.origin_class}\n"
                    current_class_name = method.origin_class
                c += f"    {method.return_type} (*{method.name})("
                c += ", ".join(
                    [f"{method.class_}* this"] + [f"{argument.type} {argument.name}" for argument in method.arguments]
                )
                c += ");\n"

        c += f"}} {class_.name}Vtbl;\n\n"

        # Class struct
        c += f"struct {class_.name} {{\n"
        c += f"    {class_.name}Vtbl* vtbl;\n"
        current_class_name = ""
        for field in class_.fields.values():
            if field.class_ != current_class_name:
                c += f"    // {field.class_}\n"
                current_class_name = field.class_
            c += f"    {field.type} {field.name};\n"
        c += "};\n\n"

        # Class method forward defines
        if not class_.is_abstract:
            init_method = class_.methods["init"]
            c += f"{class_.name}* {class_.snake_name}_new("
            if len(init_method.arguments) > 0:
                c += ", ".join([f"{argument.type} {argument.name}" for argument in init_method.arguments])
            else:
                c += "void"
            c += ");\n"
        for method in class_.methods.values():
            if method.class_ == class_.name:
                c += (
                    f"{method.return_type} _{class_.snake_name}_{method.name}("
                    + ", ".join(
                        [f"{class_.name}* this"] + [f"{argument.type} {argument.name}" for argument in method.arguments]
                    )
                    + ");\n"
                )
        c += "\n"

        # Class Vtbl instance
        if not self.is_header and not class_.is_abstract:
            c += f"{class_.name}Vtbl _{class_.name}Vtbl = {{\n"
            current_class_name = ""
            for method in class_.methods.values():
                if method.is_virtual:
                    if method.origin_class != current_class_name:
                        c += f"    // {method.origin_class}\n"
                        current_class_name = method.origin_class
                    c += f"    &_{to_snake_case(method.class_)}_{method.name},\n"
            c += "};\n\n"

        # Class macro method wrappers
        for method in class_.methods.values():
            target = ""
            if method.is_virtual:
                target = f"(({class_.name}*)(this))->vtbl->{method.name}"
            else:
                target = f"_{to_snake_case(method.class_)}_{method.name}"
            c += f"#define {class_.snake_name}_{method.name}("
            c += ", ".join(["this"] + [argument.name for argument in method.arguments])
            c += f") {target}(({method.class_}*)(this)"
            for argument in method.arguments:
                for other_class in classes.values():
                    if argument.type.startswith(other_class.name):
                        c += f", ({other_class.name}*)({argument.name})"
                        break
                else:
                    c += f", ({argument.name})"
            c += ")\n"
        c += "\n"

        # Generated methods
        if not self.is_header:
            c += g

        return c


def convert_method(match: re.Match[str]) -> str:
    """Convert method define"""
    return_type, class_name, method_name, arguments = match.groups()

    if class_name not in classes:
        logging.error("Can't find class: %s", class_name)
        sys.exit(1)
    class_ = classes[class_name]

    arguments_str = f", {arguments}" if len(arguments) > 0 else ""
    c = f"{return_type.strip()} _{class_.snake_name}_{method_name}({class_name}* this{arguments_str}) {{"

    if method_name == "init":
        for field in class_.fields.values():
            if field.class_ == class_.name and field.default is not None:
                c += f"\n    this->{field.name} = {field.default};"

    if method_name == "free":
        for field in class_.fields.values():
            if field.class_ == class_.name and "free" in field.attributes:
                if len(field.attributes["free"]) > 0:
                    c += f"\n    {field.attributes['free'][0]}(this->{field.name});"
                else:
                    c += f"\n    free(this->{field.name});"

    return c


def transpile_text(path: str, is_header: bool, text: str) -> str:
    """Transpile text"""

    # Remove #pragma once
    text = re.sub(r"#pragma once\n", "", text)
    # Convert includes
    text = re.sub(
        r"#include\s*[\"<](.+).hh[\">]",
        ConvertInclude(path),
        text,
    )
    # Convert class defines
    text = re.sub(
        r"class\s+([_A-Za-z][_A-Za-z0-9]*)\s*(:\s*[_A-Za-z][_A-Za-z0-9]*\s*)?{([^}]*)};",
        ConvertClass(is_header),
        text,
    )

    if not is_header:
        # Convert method defines
        text = re.sub(
            r"([_A-Za-z][_A-Za-z0-9 ]*[\**|\s+])\s*([_A-Za-z][_A-Za-z0-9]*)::([_A-Za-z][_A-Za-z0-9]*)\(([^\)]*)\)\s*{",
            convert_method,
            text,
        )

    return text


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="[%(levelname)s] %(message)s")

    # Parse arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("file", help="cContinue file", nargs="*")
    parser.add_argument("--output", "-o", help="Output file", required=False)
    parser.add_argument("--include", "-I", help="Include headers", action="append", default=[])
    parser.add_argument("--source", "-S", help="Only run transpile step", action="store_true")
    parser.add_argument("--compile", "-c", help="Only run transpile and compile steps", action="store_true")
    parser.add_argument("--run", "-r", help="Run linked binary", action="store_true")
    parser.add_argument("--run-leaks", "-R", help="Run linked binary with memory leaks checks", action="store_true")
    args = parser.parse_args()

    # Get paths
    cc = os.environ["CC"] if "CC" in os.environ else "gcc"
    include_paths = [".", f"{os.path.dirname(__file__)}/std"] + args.include
    source_paths = args.file
    if not args.source and not args.compile:
        for path in os.listdir(f"{os.path.dirname(__file__)}/std"):
            if path.endswith(".c") or path.endswith(".cc"):
                source_paths.append(f"{os.path.dirname(__file__)}/std/{path}")

    # Compile objects
    object_paths = []
    for path in source_paths:
        # Skip already compiled object files
        if path.endswith(".o"):
            object_paths.append(path)
            continue

        # Transpile file
        source_path = path
        if path.endswith(".hh") or path.endswith(".cc"):
            source_path = (
                args.output
                if args.output is not None
                else path.replace(".cc", ".c").replace(".hh", ".h") if args.source else tempfile.mktemp(".c")
            )
            file_write(source_path, transpile_text(path, path.endswith(".hh"), f"// @generated\n{file_read(path)}"))
            if args.source:
                sys.exit(0)

        # Compile file
        object_path = (
            (args.output if args.output is not None else path.replace(".c", ".o").replace(".cc", ".o"))
            if args.compile
            else tempfile.mktemp(".o")
        )
        object_paths.append(object_path)
        subprocess.run(
            [cc]
            + ["--std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Werror"]
            + [f"-I{include_path}" for include_path in include_paths]
            + ["-c", source_path, "-o", object_path],
            check=True,
        )
        if args.compile:
            sys.exit(0)

    # Link objects
    exe_path = (
        args.output
        if args.output is not None
        else args.file[0].replace(".cc", ".exe" if platform.system() == "Windows" else "")
    )
    subprocess.run(
        [cc] + object_paths + ["-o", exe_path],
        check=True,
    )

    # Run executable
    if args.run:
        os.system(f"./{exe_path}")
    elif args.run_leaks:
        if platform.system() == "Darwin":
            os.system(f"leaks --atExit -- ./{exe_path}")
        elif platform.system() == "Linux":
            os.system(f"valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./{exe_path}")
        else:
            logging.error("Memory leak checks are not supported on this platform")
            sys.exit(1)
