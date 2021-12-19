#!/usr/bin/env python
# The BassieC Transpiler v0.1.0
# This code is an ugly mess I know, but hey it works quite well!
# Also I want to clean it up in the future...

import argparse, os, re

version = '0.1.0'

parser = argparse.ArgumentParser(description='The BassieC Transpiler v' + version)
parser.add_argument('file')
parser.add_argument('-d', '--debug', action='store_true', help='Add debug prints for object allocations')
parser.add_argument('-H', '--headers', action='store_true', help='Only generated headers')
args = parser.parse_args()

stdlib = '''
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

abstract class Object {
    void Init();
    void Free();
}

void Object::Init() {}

void Object::Free() {
    ''' + (args.debug and 'printf("Object_Free(0x%p)\\n", this);' or '') + '''
    free(this);
}'''

with open(args.file, 'r') as inFile:
    headers = ''
    code = stdlib + inFile.read()
    classes = {}

    # Helper functions
    def studentCase(str):
        return str[0].upper() + str[1:]
    def camelCase(str):
        return str[0].lower() + str[1:]
    def screamCase(str):
        return re.sub(r'([A-Z])', '_\\1', camelCase(str)).upper()
    def printType(item):
        item = type(item) is dict and item['type'] or item
        if item[len(item) - 1] == '*':
            return item
        return item + ' '

    # Remove comments
    code = re.sub(re.compile(r'\/\*.+\*\/', re.S), '', code)
    code = re.sub(r'\/\/[^\n]*', '', code)

    # Include BassieC files
    stdDirname = os.path.dirname(__file__) + '/std'
    stdFiles = [os.path.splitext(filename)[0] for filename in os.listdir(stdDirname)]

    dirname = os.path.dirname(args.file)
    if dirname != '':
        os.chdir(dirname)

    def includeIncludes(code):
        def convertInclude(match):
            path = match.group(1)
            with open((path in stdFiles and stdDirname + '/' + path or path) + '.bc', 'r') as includeFile:
                return includeIncludes(includeFile.read())
        return re.sub(r'#include "(.+).bc"', convertInclude, code)
    code = includeIncludes(code)

    # Remove comments again for included files
    code = re.sub(re.compile(r'\/\*.+\*\/', re.S), '', code)
    code = re.sub(r'\/\/[^\n]*', '', code)

    # Move all header stuff to header string
    def moveToHeaders(match):
        global headers
        headers += match.group(0)
        return ''
    code = re.sub(r'#define\s*(.+)\n(\s*)', moveToHeaders, code)
    code = re.sub(r'#include\s*(.+)\n(\s*)', moveToHeaders, code)
    code = re.sub(r'typedef\s+(.+);(\s*)', moveToHeaders, code)
    code = re.sub(r'typedef\s+([a-z]+)\s+([_A-Za-z][_A-Za-z0-9]*)\s*{([^}]*)}\s*([_A-Za-z][_A-Za-z0-9]*);(\s*)', moveToHeaders, code)

    # Convert new class syntax sugar
    def convertNew(match):
        name = match.group(1)
        return name + '_New('
    code = re.sub(r'new\s+([_A-Za-z][_A-Za-z0-9]*)\(', convertNew, code)

    # Convert class declerations
    def convertClass(match):
        global headers
        data = match.group(4)
        name = match.group(2)
        abstract = match.group(1) != None

        # Find parent class
        parent = match.group(3) != None and classes[re.search(r'extends\s+([_A-Za-z][_A-Za-z0-9]*)\s*', match.group(3)).group(1)] or (name != 'Object' and classes['Object'] or None)

        # Index fields
        fields = []
        for field in re.findall(r'(.+[^=][\s|\*])([_A-Za-z][_A-Za-z0-9]*)(\s*=\s*[^;]+)?;', data):
            attributes = {}
            def convertAttribute(match):
                attributes[match.group(1)] = match.group(2) != None and [arg.strip() for arg in match.group(2)[1:len(match.group(2)) - 1].split(',')] or []
                return ''
            fieldType = re.sub(r'@([_A-Za-z][_A-Za-z0-9]*)(\([^\)]*\))?', convertAttribute, field[0]).strip()
            fields.append({'class': name, 'name': field[1], 'type': fieldType, 'attributes': attributes,
                'default': field[2] != '' and re.search(r'\s*=\s*([^;]+)', field[2]).group(1) or None})

        def mergeParentFields(parent):
            for field in reversed(parent['fields']):
                fields.insert(0, field)
            if parent['parent'] != None:
                mergeParentFields(parent['parent'])
        if parent != None:
            mergeParentFields(parent)

        fields = [field for field in {field['name']: field for field in fields}.values()]

        # Index methods
        methods = []
        for method in re.findall(r'(.+[^=][\s|\*])([_A-Za-z][_A-Za-z0-9]*)\(([^\)]*)\);', data):
            attributes = {}
            def convertAttribute(match):
                attributes[match.group(1)] = match.group(2) != None and [arg.strip() for arg in match.group(2)[1:len(match.group(2)) - 1].split(',')] or []
                return ''
            returnType = re.sub(r'@([_A-Za-z][_A-Za-z0-9]*)(\([^\)]*\))?', convertAttribute, method[0]).strip()

            methodsArgs = [{'name': 'this', 'type': name + ' *'}]
            if method[2] != '':
                for arg in method[2].split(','):
                    parts = re.search(r'([_A-Za-z][_A-Za-z0-9 ]*[\**|\s+])\s*([_A-Za-z][_A-Za-z0-9]*)', arg)
                    methodsArgs.append({'name': parts.group(2), 'type': parts.group(1).strip()})
            methods.append({'class': name, 'name': method[1], 'args': methodsArgs, 'attributes': attributes, 'return': returnType, 'generated': False})

        for field in fields:
            if field['class'] != name:
                continue

            if 'Get' in field['attributes'] or 'Prop' in field['attributes']:
                attributeArgs = field['attributes']['Get' in field['attributes'] and 'Get' or 'Prop']
                fieldType = len(attributeArgs) >= 1 and attributeArgs[0] or field['type']
                methods.append({'class': name, 'name': 'Get' + studentCase(field['name']), 'args': [{'name': 'this', 'type': name + ' *'}], 'return': fieldType,
                    'generated': True, 'field': field, 'variable': field['name'], 'type': fieldType, 'oldType': field['type']})
                if len(attributeArgs) >= 2:
                    for arg in attributeArgs[1:]:
                        argParts = re.search(r'([_A-Za-z][_A-Za-z0-9 ]*[\**|\s+])\s*([_A-Za-z][_A-Za-z0-9]*)', arg)
                        argType = argParts.group(1).strip()
                        methods.append({'class': name, 'name': 'Get' + studentCase(field['name']) + studentCase(argParts.group(2)), 'args': [{'name': 'this', 'type': name + ' *'}], 'return': argType,
                            'generated': True, 'field': field, 'variable': field['name'] + (argType[len(argType) - 1] == '*' and '->' or '.') + argParts.group(2), 'type': argType, 'oldType': argType})

            if 'Set' in field['attributes'] or 'Prop' in field['attributes']:
                attributeArgs = field['attributes']['Set' in field['attributes'] and 'Set' or 'Prop']
                fieldType = len(attributeArgs) >= 1 and attributeArgs[0] or field['type']
                methods.append({'class': name, 'name': 'Set' + studentCase(field['name']), 'args': [{'name': 'this', 'type': name + ' *'}, {'name': field['name'], 'type': fieldType}], 'return': 'void',
                    'generated': True, 'field': field, 'variable': field['name'], 'type': fieldType, 'oldType': field['type']})
                if len(attributeArgs) >= 2:
                    for arg in attributeArgs[1:]:
                        argParts = re.search(r'([_A-Za-z][_A-Za-z0-9 ]*[\**|\s+])\s*([_A-Za-z][_A-Za-z0-9]*)', arg)
                        argType = argParts.group(1).strip()
                        methods.append({'class': name, 'name': 'Set' + studentCase(field['name']) + studentCase(argParts.group(2)), 'args': [{'name': 'this', 'type': name + ' *'}, {'name': field['name'] + studentCase(argParts.group(2)), 'type': argType}], 'return': 'void',
                            'generated': True, 'field': field, 'variable': field['name'] + (argType[len(argType) - 1] == '*' and '->' or '.') + argParts.group(2), 'type': argType, 'oldType': argType})

            if 'Extend' in field['attributes'] and len(field['attributes']['Extend']) >= 1:
                other = field['attributes']['Extend'][0]
                for method in classes[other]['methods']:
                    if method['name'] != 'Init' and method['name'] != 'Free':
                        methods.append({'class': name, 'name': studentCase(field['name']) + method['name'], 'args': [{'name': arg['name'], 'type': arg['name'] == 'this' and name + ' *' or arg['type']} for arg in method['args']], 'return': method['return'],
                            'generated': True, 'field': field, 'variable': field['name'], 'otherClass': other, 'method': method['name']})

        def mergeParentMethods(parent):
            for method in reversed(parent['methods']):
                methods.insert(0, method)
            if parent['parent'] != None:
                mergeParentMethods(parent['parent'])
        if parent != None:
            mergeParentMethods(parent)

        methods = [method for method in {method['name']: method for method in methods}.values()]

        # Create init method when defaults
        if methods[0]['class'] != name and (
            any(field['default'] != None for field in fields if field['class'] == name) or
            any('Init' in field['attributes'] for field in fields if field['class'] == name)
        ):
            initArgs = [{'name': arg['name'], 'type': arg['name'] == 'this' and name + ' *' or arg['type']} for arg in methods[0]['args']]
            for field in [field for field in fields if field['class'] == name and 'Init' in field['attributes']]:
                initArgs.append({'name': field['name'], 'type': field['type']})
            methods[0] = { 'class': name, 'name': 'Init', 'args': initArgs, 'return': 'void', 'generated': True }

        # Create free method when free attributes
        if methods[1]['class'] != name and any('Free' in field['attributes'] for field in fields if field['class'] == name):
            methods[1] = { 'class': name, 'name': 'Free', 'args': [{'name': 'this', 'type': name + ' *'}], 'return': 'void', 'generated': True }

        classes[name] = {'name': name, 'parent': parent, 'abstract': abstract, 'fields': fields, 'methods': methods}

        # Create new method if not exists
        generatedMethods = []

        # For now always generate new method when not abstract
        if not abstract:
            generatedMethods.append(
                name + ' *' + name + '_New(' + (len(methods[0]['args']) >= 2 and (', '.join([printType(arg) + arg['name'] for arg in methods[0]['args'] if arg['name'] != 'this'])) or 'void') + ') {\n' +
                '    ' + name + ' *this = calloc(1, sizeof(' + name + '));\n'
                '    this->vtbl = &_' + name + 'Vtbl;\n' +
                (args.debug and '    printf("0x%p = ' + name + '_New()\\n", this);\n' or '') +
                '    ' + name + '_Init(this' + (''.join([', ' + arg['name'] for arg in methods[0]['args'] if arg['name'] != 'this'])) + ');\n' +
                '    return this;\n'
                '}'
            )

        for method in methods:
            if not (method['generated'] and method['class'] == name):
                continue
            if method['name'] == 'Init':
                generatedMethods.append(
                    'void _' + name + '_Init(' + (', '.join([printType(arg) + arg['name'] for arg in method['args']])) + ') {\n' +
                    (parent['methods'][0]['class'] != 'Object' and ('    ' + name + '::Init(' + (', '.join([arg['name'] for arg in parent['methods'][0]['args'] if arg['name'] != 'this'])) + ');\n') or '') +
                    ''.join(['    this->' + field['name'] + ' = ' + (len(field['attributes']['Init']) >= 1 and field['attributes']['Init'][0] or '') + '(' + (field['default'] != None and field['name'] + ' != NULL ? ' or '') + field['name'] +
                        (field['default'] != None and ' : ' + field['default'] or '') + ');\n' for field in fields if field['class'] == name and 'Init' in field['attributes']]) +
                    ''.join(['    this->' + field['name'] + ' = ' + field['default'] + ';\n' for field in fields if field['class'] == name and field['default'] != None and 'Init' not in field['attributes']]) +
                    '}'
                )
            if method['name'] == 'Free':
                generatedMethods.append(
                    'void _' + name + '_Free(' + name + ' *this) {\n' +
                    ''.join(['    if (this->' + field['name'] + ' != NULL) ' + (len(field['attributes']['Free']) >= 1 and field['attributes']['Free'][0] or 'free') + '(this->' + field['name'] + ');\n' for field in fields if field['class'] == name and 'Free' in field['attributes']]) +
                    '    ' + name + '::Free();\n' +
                    '}'
                )
            if method['name'].startswith('Get'):
                generatedMethods.append(
                    printType(method['return']) + '_' + name + '_' + method['name'] + '(' + name + ' *this) {\n' +
                       '    return ' + ((method['type'] != method['oldType'] and method['type'][len(method['type']) - 1] == '*') and '&' or '') + 'this->' + method['variable'] + ';\n' +
                    '}'
                )
            if method['name'].startswith('Set'):
                variable = ((method['type'] != method['oldType'] and method['args'][1]['type'][len(method['args'][1]['type']) - 1] == '*') and '*' or '') + method['args'][1]['name']
                generatedMethods.append(
                    'void _' + name + '_' + method['name'] + '(' + (', '.join([printType(arg) + arg['name'] for arg in method['args']])) + ') {\n' +
                       ('Free' in method['field']['attributes'] and ('    if (this->' + method['variable'] + ' != NULL) ' + (len(method['field']['attributes']['Free']) >= 1 and method['field']['attributes']['Free'][0] or 'free') + '(this->' + method['variable'] + ');\n') or '') +
                       '    this->' + method['variable'] + ' = ' + ('Init' in method['field']['attributes'] and len(method['field']['attributes']['Init']) >= 1 and method['field']['attributes']['Init'][0] + '(' + variable + ')' or variable) + ';\n' +
                    '}'
                )
            if 'method' in method:
                generatedMethods.append(
                    printType(method['return']) + '_' + name + '_' + method['name'] + '(' + (', '.join([printType(arg) + arg['name'] for arg in method['args']])) + ') {\n' +
                       '    ' + (method['return'] != 'void' and 'return ' or '') + method['otherClass'] + '_' + method['method'] + '(this->' + method['variable'] + ''.join([', ' + arg['name'] for arg in method['args'][1:]]) + ');\n' +
                    '}'
                )

        headers += (
            'typedef struct ' + name + ' ' + name + ';\n\n' +

            'typedef struct ' + name + 'Vtbl {\n' +
                (''.join(['    ' + printType(method['return']) + '(*' + method['name'] + ')(' +
                    (', '.join([printType(arg) + arg['name'] for arg in method['args']])) +
                ');\n' for method in methods])) +
            '} ' + name + 'Vtbl;\n\n' +

            (not abstract and ('extern ' + name + 'Vtbl _' + name + 'Vtbl;\n\n') or '') +

            'struct ' + name + ' {\n' +
                '    const ' + name + 'Vtbl *vtbl;\n' +
                (''.join(['    ' + printType(field) + field['name'] + ';\n' for field in fields])) +
            '};\n\n' +

            (not abstract and ('extern ' + name + ' *' + name + '_New(' + (len(methods[0]['args']) >= 2 and (', '.join([printType(arg) + arg['name'] for arg in methods[0]['args'] if arg['name'] != 'this'])) or 'void') + ');\n\n') or '') +

            '#define ' + screamCase(name) + '(' + camelCase(name) + ') ((' + name + ' *)' + camelCase(name) + ')\n' +

            (''.join(['#define ' + name + '_' + method['name'] + '(' +
                (', '.join([arg['name'] for arg in method['args']])) +
            ') ((' + method['class'] + ' *)this)->vtbl->' + method['name'] + '(' +
                (', '.join([(arg['name'] == 'this' and '(' + method['class'] + ' *)' + arg['name'] or arg['name']) for arg in method['args']])) +
            ')\n' for method in methods])) + (len(methods) >= 1 and '\n' or '')
        )

        return (
            (not abstract and (
                (''.join([printType(method['return']) + '_' + name + '_' + method['name'] + '(' +
                    (', '.join([printType(arg) + arg['name'] for arg in method['args']])) +
                ');\n' for method in methods if method['class'] == name])) +

                '\n' + name + 'Vtbl _' + name + 'Vtbl = {\n' +
                    (',\n'.join(['    &_' + method['class'] + '_' + method['name'] for method in methods])) +
                '\n};\n\n'
            ) or '') +

            '\n\n'.join(generatedMethods)
        )
    code = re.sub(r'(abstract\s+)?class\s+([_A-Za-z][_A-Za-z0-9]*)\s*(extends\s+[_A-Za-z][_A-Za-z0-9]*\s*)?{([^}]*)}', convertClass, code)

    # Convert methods
    def convertMethod(match):
        name = match.group(2)
        method = match.group(3)
        args = len(match.group(4)) > 0 and ', ' + match.group(4) or ''
        return (match.group(1) + '_' + name + '_' + method + '(' + name + ' *this' + args + ') {' +
            (method == 'Init' and ''.join(['\n    this->' + field['name'] + ' = ' + field['default'] + ';'
            for field in classes[name]['fields'] if field['class'] == name and field['default'] != None and 'Init' not in field['attributes']]) or '') +
            (method == 'Free' and ''.join(['\n    ' + (len(field['attributes']['Free']) >= 1 and field['attributes']['Free'][0] or 'free') +
            '(this->' + field['name'] + ');' for field in classes[name]['fields'] if field['class'] == name and 'Free' in field['attributes']]) or '')
        )
    code = re.sub(r'([_A-Za-z][_A-Za-z0-9 ]*[\**|\s+])\s*([_A-Za-z][_A-Za-z0-9]*)::([_A-Za-z][_A-Za-z0-9]*)\(([^\)]*)\)\s*{', convertMethod, code)

    # Convert super calls
    def convertSuper(match):
        if match.group(1) not in classes:
            print('Can\'t find the ' + match.group(1) + ' class!')
            exit(1)
        _class = classes[match.group(1)]

        method = next((method for method in _class['parent']['methods'] if method['name'] == match.group(2)), None)
        if method == None:
            print('Can not find method ' + match.group(2) + ' in the ' + _class['parent']['name'] + ' class!')
            exit(1)

        args = len(match.group(3)) > 0 and ', ' + match.group(3) or ''
        return '_' + method['class'] + '_' + method['name'] + '((' + method['class'] + '*)this' + args + ');'

    code = re.sub(r'([_A-Za-z][_A-Za-z0-9]*)::([_A-Za-z][_A-Za-z0-9]*)\(([^\)]*)\);', convertSuper, code)

    # Convert instanceof calls
    for name in classes:
        classes[name]['children'] = []
        if not classes[name]['abstract'] and classes[name]['parent'] != None:
            classes[classes[name]['parent']['name']]['children'].append(classes[name])
    def convertInstanceof(match):
        name = match.group(2)
        if name not in classes:
            print('Can\'t find the ' + name + ' class!')
            exit(1)
        _data = classes[name]
        variable = match.group(1)
        return ('((' + name + 'Vtbl *)' + variable + '->vtbl == &_' + name + 'Vtbl' +
            (''.join([' || (' + child['name'] + 'Vtbl *)' + variable + '->vtbl == &_' + child['name'] + 'Vtbl' for child in _data['children']])) +
        ')')
    code = re.sub(r'instanceof\(([_A-Za-z][_A-Za-z0-9]*),\s*([_A-Za-z][_A-Za-z0-9]*)\)', convertInstanceof, code)

    # Writer headers and code back to files
    moduleName = os.path.splitext(os.path.basename(args.file))[0]
    headerPath = moduleName + '.h'
    codePath = moduleName + '.c'

    with open(headerPath, 'w') as headerFile:
        headerFile.write(
            '// This file is generated via the BassieC Transpiler v' + version + '\n' +
            '// So editing has probably no use, edit the source file\n\n' +
            '#ifndef ' + moduleName.upper() + '_H\n' +
            '#define ' + moduleName.upper() + '_H\n\n' +
            headers +
            '#endif\n'
        )

    with open(codePath, 'w') as codeFile:
        codeFile.write(
            '// This file is generated via the BassieC Transpiler v' + version + '\n' +
            '// So editing has probably no use, edit the source file\n\n' +
            '#include "' + headerPath + '"\n\n' +
            code
        )
