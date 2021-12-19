// This file is generated via the BassieC Transpiler v0.1.0
// So editing has probably no use, edit the source file

#include "hello.h"




void _Object_Init(Object *this) {}

void _Object_Free(Object *this) {
    
    free(this);
}

void _Person_Init(Person *this, char *name, int age);
void _Person_Free(Person *this);
void _Person_Greet(Person *this);
char *_Person_GetName(Person *this);
void _Person_SetName(Person *this, char *name);
int _Person_GetAge(Person *this);
void _Person_SetAge(Person *this, int age);

PersonVtbl _PersonVtbl = {
    &_Person_Init,
    &_Person_Free,
    &_Person_Greet,
    &_Person_GetName,
    &_Person_SetName,
    &_Person_GetAge,
    &_Person_SetAge
};

Person *Person_New(char *name, int age) {
    Person *this = calloc(1, sizeof(Person));
    this->vtbl = &_PersonVtbl;
    Person_Init(this, name, age);
    return this;
}

void _Person_Init(Person *this, char *name, int age) {
    this->name = strdup(name);
    this->age = (age);
}

void _Person_Free(Person *this) {
    if (this->name != NULL) free(this->name);
    _Object_Free((Object*)this);
}

char *_Person_GetName(Person *this) {
    return this->name;
}

void _Person_SetName(Person *this, char *name) {
    if (this->name != NULL) free(this->name);
    this->name = strdup(name);
}

int _Person_GetAge(Person *this) {
    return this->age;
}

void _Person_SetAge(Person *this, int age) {
    this->age = age;
}

void _Person_Greet(Person *this) {
    printf("Hello %s, you are %d years old!\n", this->name, this->age);
}

int main(void) {
    Person *person = Person_New("Bastiaan", 18);
    Person_SetAge(person, Person_GetAge(person) + 1);
    Person_Greet(person);
    Person_Free(person);

    return EXIT_SUCCESS;
}
