# BassieC: A object oriented extention of C
*And simple transpiler that coverts an object oriented extention of C back to C code with nice codegen features*

I created this thingy because I love the simplicity of the C programming language and I have a small to big distaste for C++. It is just a tool that allows you to write Object Oriented code in C without all the boilerplate of generating and syncing function pointer tables of init, free, getters and setters methods.

The transpiler is super basic and a single bad written Python script that uses regular expressions for the parsing of the code.

This repo also contains the [Jan](jan/) experimental GUI library written in BassieC wich uses a lot of it unique codegen features to generate a lot of stub methods and other nice stuff, the main reason for the creation of BassieC was to create a nice object oriented GUI library easily.

## Language description
This needs a lot of work, i know...

### Basic classes
Create an class:
```
class Person {
    char *name;
    int age;
}
```

Create an instance of that class:
```
int main(void) {
    Person *person = new Person();
    person->name = "BassieBAS";
    person->age = 19;
    Person_Free(person);
}
```

### Class field attributes
Use field attributes to generate methods:
```
class Person {
    @Prop @Init(strdup) @Free char *name;
    @Prop int age;
}
```

This is quite powerfull and does the same as this code:
```
class Person {
    char *name;
    int age;
}

void Person::Init(char *name, int age) {
    this->name = strdup(name);
    this->age = age;
}

char *Person::GetName() {
    return this->name;
}

void Person::SetName(char *name) {
    if (this->name != NULL) free(this->name);
    this->name = strdup(name);
}

int Person::GetAge() {
    return this->age;
}

void Person::SetAge(int age) {
    this->age = age;
}

void Person::Free() {
    if (this->name != NULL) free(this->name);
    Object::Free(this); // <-- Super method call to previous class
}
```

The attributes that are implemented are for now and it arguments:
- `@Get(type)` Generate a getter method for this field
- `@Set(type)` Generate a setter method for this field
- `@Prop(type)` A shortcut to generate a setter and a getter (same as `@Get` `@Set`)
- `@Init(initFunction)` Use this field as an argument for the generated `Init` method
- `@Free(freeFunction)` Free this field in the generated `Free` method
- `@Extend(class)` For a class pointer as a field: generate wrapper functions for all methods of this class field

### Class inheritance
The last code is a super method call to previous class. All classe inherit from the base class called `Object` with the defination this is handy because now we can enforce that the first function in the vtbl always is the `Init` method and the second is always the `Free` method. We can also do some more generic stuff like that the build in [List](std/list.bc) class frees all its object when it is self freed:
```
abstract class Object {
    void Init();
    void Free();
}

void Object::Init() {}

void Object::Free() {
    free(this);
}
```

Of course classes can inherit from other classes to reduce code, because all methods calls are using a single static function pointer table and so all methods are automaticly virtual and can changed by child classes. This system is inspired by the ABI of [Microsoft COM](https://en.wikipedia.org/wiki/Component_Object_Model):
```
abstract class Animal {
    @Prop @Init(strdup) @Free char *name;
    void Greet();
}

class Dog extends Animal {
    void Greet();
}

void Dog::Greet() {
    printf("The dog %s greets you!\n", this->name);
}

class Cat extends Animal {
    void Greet();
}

void Cat::Greet() {
    printf("The cat %s greets you!\n", this->name);
}
```

Because that every class instance has an pointer to a function pointer table of that class type we can use that to do dynamic checking of class types with the `instanceof` function:
```
int main(void) {
    Cat *cat = new Cat();
    Dog *dog = new Dog();
    if (instanceof(cat, Animal)) printf("cat is an animal!\n");
    if (instanceof(dog, Animal)) printf("dog is an animal!\n");
    if (!instanceof(dog, Cat)) printf("dog is not an Cat!\n");
}
```

### The transpiler options
This needs a lot of work, so to learn more about the language compile some code and see the generated C code. With the `-d` option you can generate print statements when an new class is created an when freed. The transpiler will always create one header file and one C code file:
```
$ ./bc.py test.bc
$ ls
test.bc test.h test.c    # <-- The generated files
```

## License
Copyright (c) 2021 Bastiaan van der Plaat

Licensed under the [MIT](LICENSE) license.
