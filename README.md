# CContinue Transpiler
*A transpiler that translates an OOP-extension for the C programming language back to C*

I like C and I like C++, both are powerful languages in there own right. But C++ is quite complicated and sometimes I just want to create some classes with inheritance in my C project. So I've created the weird hacky Python transpiler that can translate a custom syntax inspired by C++ and Java back to C code.

## The syntax
*The documentation is bad I know*

### A basic class
You can create a class with some fields with the following syntax:
```
class Person {
    char *name;
    int age;
}
```

All classes are structs that inherit from the root `Object` class which is heap allocated and ref counted. A `new`, `ref` and `free` method are automatically generated for you and you can use the fields just like a struct:
```
int main(void) {
    Person *person = person_new();
    person->name = "Bastiaan";
    person->age = 21;
    person_free(person);
}
```

### Field attributes
You can add attributes with the `@attribute` syntax before a class field to generated methods automatically. This is useful because it saves a lot of typing work, we can extend the `Person` class with the following attributes:
```
class Person {
    @get @init @free(string_free) String *name;
    @prop @init int age;
}
```

This will inturn generated the following methods for us:
```
class Person {
    // ...
    void init(String *name, int32_t age);
    virtual Person *ref();
    virtual void free();
    String * get_name();
    int32_t get_age();
    void set_age(int32_t age);
}
```

You can use the following attributes:
- `@get` Generate a getter method for this field
- `@set` Generate a setter method for this field
- `@prop` Short cut for `@get` and `@set`
- `@init(init_function)` Use this field as an argument for the generated `init` method
- `@free(free_function)` Free this field in the generated `free` method

### Class inheritance
Classes can inherit from other classes with the `extends` keyword and classes can be made `abstract`:
```
abstract class Animal {
    @prop @init(strdup) @free char *name;
    virtual void greet();
}

class Dog extends Animal {
    void greet();
}
void Dog::greet() {
    printf("The dog %s greets you!\n", this->name);
}

class Cat extends Animal {
    void Greet();
}
void Cat::greet() {
    printf("The cat %s greets you!\n", this->name);
}
```

See the code examples in [examples/](examples/) for more info

## TODO
- Add support for separate code and header files
- Add interfaces that work like Java interfaces and like Rust traits

## License
Copyright (c) 2021 - 2024 Bastiaan van der Plaat

Licensed under the [MIT](LICENSE) license.
