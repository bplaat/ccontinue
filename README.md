# cContinue Transpiler

_A transpiler that translates an OOP-extension for the C programming language back to C_

I like C and I like C++, both are powerful languages in there own right. But C++ is quite complicated and sometimes I just want to create some classes with inheritance in my C project. So I've created the weird hacky Python transpiler that can translate a C++ like syntax with a Java like class system back to C code 🤓.

## The syntax

### Basic class

A basic class can be created with the `class` keyword, a class can contain fields:

```cpp
class Person {
    char* name;
    i32 age;
};
```

A class is just a `struct` that inherit fields and (virtual) methods from its parent. If no parent class is defined the class will inherit from the base `Object` class. All class instances are heap allocated and reference counted. You can create a class instance with the created `_new()` method and free the instance with the created `_free()` method:

```cpp
int main(void) {
    Person* person = person_new();
    person->name = "Bastiaan";
    person->age = 21;
    person_free(person);
}
```

### Class methods

Classes can also have methods, you can't implement methods inline in the class definition like C++ but you have to use the separated method impl syntax:

```cpp
class Person {
    // ...
    void greet();
};

void Person::greet() {
    printf("Hello %s, you are %d years old!\n", this->name, this->age);
}
```

You can call the method like the `free` method:

```cpp
int main(void) {
    // ...
    person_greet(person);
    person_free(person);
}
```

### Field attributes

You can add attributes with the `@attribute` syntax before class fields to generated methods automatically. This is useful because it saves a lot of typing work, we can extend the `Person` class with the following attributes:

```cpp
class Person {
    @get @init(strdup) @deinit char* name;
    @prop @init i32 age;
};
```

This will in turn generated the following methods for us:

```cpp
class Person {
    // ...
    void init(char* name, i32 age);
    virtual void deinit();
    Person* ref();
    void free();

    char* get_name();
    i32 get_age();
    void set_age(i32 age);
};
```

All the fields of the `init` method are also present in the `new` method, so our main function can be:

```cpp
int main(void) {
    Person* person = person_new("Bastiaan", 21);
    // ...
    person_free(person);
}
```

You can use the following attributes:

- `@get` Generate a getter method for this field
- `@set` Generate a setter method for this field
- `@prop` alias for `@get` and `@set`
- `@init` or `@init(init_function)` Use this field as an argument for the generated `init` method
- `@deinit` or `@deinit(free_function)` Free this field in the generated `deinit` method

### Abstract classes

Classes can be made abstract when they have a virtual method without implementation:

```cpp
class Animal {
    @prop @init(strdup) @deinit char* name;
    virtual void greet() = 0;
};
```

### Class inheritance

Classes can inherit from **one** other parent class:

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

### Super call

You can call the parent class method with the super call syntax:

```cpp
void Dog::greet() {
    Animal::greet();
}
```

### Self\* type

When a class method returns itself a.k.a. `return this;` you need to use the `Self*` return type:

```cpp
class PersonBuilder {
    Self* name();
};

Self* PersonBuilder::name() {
    return this;
}
```

## TODO

- Add interfaces that work like Java interfaces

## License

Copyright © 2021-2025 Bastiaan van der Plaat

Licensed under the [MIT](LICENSE) license.
