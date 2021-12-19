// This file is generated via the BassieC Transpiler v0.1.0
// So editing has probably no use, edit the source file

#ifndef HELLO_H
#define HELLO_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Object Object;

typedef struct ObjectVtbl {
    void (*Init)(Object *this);
    void (*Free)(Object *this);
} ObjectVtbl;

struct Object {
    const ObjectVtbl *vtbl;
};

#define OBJECT(object) ((Object *)object)
#define Object_Init(this) ((Object *)this)->vtbl->Init((Object *)this)
#define Object_Free(this) ((Object *)this)->vtbl->Free((Object *)this)

typedef struct Person Person;

typedef struct PersonVtbl {
    void (*Init)(Person *this, char *name, int age);
    void (*Free)(Person *this);
    void (*Greet)(Person *this);
    char *(*GetName)(Person *this);
    void (*SetName)(Person *this, char *name);
    int (*GetAge)(Person *this);
    void (*SetAge)(Person *this, int age);
} PersonVtbl;

extern PersonVtbl _PersonVtbl;

struct Person {
    const PersonVtbl *vtbl;
    char *name;
    int age;
};

extern Person *Person_New(char *name, int age);

#define PERSON(person) ((Person *)person)
#define Person_Init(this, name, age) ((Person *)this)->vtbl->Init((Person *)this, name, age)
#define Person_Free(this) ((Person *)this)->vtbl->Free((Person *)this)
#define Person_Greet(this) ((Person *)this)->vtbl->Greet((Person *)this)
#define Person_GetName(this) ((Person *)this)->vtbl->GetName((Person *)this)
#define Person_SetName(this, name) ((Person *)this)->vtbl->SetName((Person *)this, name)
#define Person_GetAge(this) ((Person *)this)->vtbl->GetAge((Person *)this)
#define Person_SetAge(this, age) ((Person *)this)->vtbl->SetAge((Person *)this, age)

#endif
