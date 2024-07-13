# cContinue Transpiler
*A transpiler that translates an OOP-extension for the C programming language back to C*

I like C and I like C++, both are powerful languages in there own right. But C++ is quite complicated and sometimes I just want to create some classes with inheritance in my C project. So I've created the weird hacky Python transpiler that can translate a C++ like syntax with a Java like class system back to C code 🤓.

## The syntax
*The documentation is bad I know*

### A basic class
You can create a class with some fields with the following syntax:
```cpp
class Person {
    char* name;
    i32 age;
};
```

All classes are structs that inherit from the root `Object` class which is heap allocated and ref counted. The `new`, `ref` and `free` methods are automatically generated for you and you can use the fields just like a struct:
```cpp
int main(void) {
    Person* person = person_new();
    person->name = "Bastiaan";
    person->age = 21;
    person_free(person);
}
```

### Field attributes
You can add attributes with the `@attribute` syntax before a class field to generated methods automatically. This is useful because it saves a lot of typing work, we can extend the `Person` class with the following attributes:
```cpp
class Person {
    @get @init(strdup) @free(free) char* name;
    @prop @init i32 age;
};
```

This will inturn generated the following methods for us:
```cpp
class Person {
    // ...
    void init(char* name, i32 age);
    virtual Person* ref();
    virtual void free();

    char* get_name();
    i32 get_age();
    void set_age(i32 age);
};
```

You can use the following attributes:
- `@get` Generate a getter method for this field
- `@set` Generate a setter method for this field
- `@prop` alias for `@get @set`
- `@init(init_function)` Use this field as an argument for the generated `init` method
- `@free(free_function)` Free this field in the generated `free` method

### Abstract classes
Classes can be made abstract when they have a virtual method without implementation:
```cpp
class Animal {
    @prop @init(strdup) @free char* name;
    virtual void greet() = 0;
};
```

### Class inheritance
Classes can inherit from **one** other class:
```cpp
class Dog : Animal {
    virtual void greet();
};
void Dog::greet() {
    printf("The dog %s greets you!\n", this->name);
}

class Cat : Animal {
    virtual void Greet();
};
void Cat::greet() {
    printf("The cat %s greets you!\n", this->name);
}
```

## TODO
- Add interfaces that work like Java interfaces

## License
Copyright (c) 2021 - 2024 Bastiaan van der Plaat

Licensed under the [MIT](LICENSE) license.
