// @generated
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *strdup(const char *s) {
    char *n = malloc(strlen(s) + 1);
    strcpy(n, s);
    return n;
}


typedef struct Object Object;

typedef struct ObjectVtbl {
    // Object
    void  (*free)(Object *this);
} ObjectVtbl;

struct Object {
    ObjectVtbl *vtbl;
    // Object
    size_t refs;
};

void  _object_init(Object *this);
Object * _object_ref(Object *this);
void  _object_free(Object *this);

ObjectVtbl _ObjectVtbl = {
    // Object
    &_object_free,
};

#define object_init(this) _object_init((Object *)(this))
#define object_ref(this) _object_ref((Object *)(this))
#define object_free(this) ((Object *)(this))->vtbl->free((Object *)(this))



void _object_init(Object *this) {
    this->refs = 1;}

Object * _object_ref(Object *this) {
    this->refs++;
    return this;
}

void _object_free(Object *this) {
    if (--this->refs <= 0)
        free(this);
}


typedef struct List List;

typedef struct ListVtbl {
    // List
    void  (*free)(List *this);
} ListVtbl;

struct List {
    ListVtbl *vtbl;
    // Object
    size_t refs;
    // List
    Object ** items;
    size_t capacity;
    size_t size;
};

void  _list_init(List *this);
void  _list_free(List *this);
Object * _list_get(List *this, size_t  index);
void  _list_set(List *this, size_t  index, Object * item);
void  _list_add(List *this, Object * item);
void  _list_insert(List *this, size_t  index, Object * item);
void  _list_remove(List *this, size_t  index);
size_t _list_get_capacity(List *this);
size_t _list_get_size(List *this);

ListVtbl _ListVtbl = {
    // List
    &_list_free,
};

#define list_init(this) _list_init((List *)(this))
#define list_ref(this) _object_ref((Object *)(this))
#define list_free(this) ((List *)(this))->vtbl->free((List *)(this))
#define list_get(this, index) _list_get((List *)(this), (index))
#define list_set(this, index, item) _list_set((List *)(this), (index), (Object *)(item))
#define list_add(this, item) _list_add((List *)(this), (Object *)(item))
#define list_insert(this, index, item) _list_insert((List *)(this), (index), (Object *)(item))
#define list_remove(this, index) _list_remove((List *)(this), (index))
#define list_get_capacity(this) _list_get_capacity((List *)(this))
#define list_get_size(this) _list_get_size((List *)(this))

size_t _list_get_capacity(List *this) {
    return this->capacity;
}

size_t _list_get_size(List *this) {
    return this->size;
}

List *list_new(void) {
    List *this = malloc(sizeof(List));
    this->vtbl = &_ListVtbl;
    list_init(this);
    return this;
}



void _list_init(List *this) {
    this->capacity = 8;
    this->size = 0;
    object_init(this);
    this->items = malloc(sizeof(Object *) * this->capacity);
}

void _list_free(List *this) {
    for (size_t i = 0; i < this->size; i++)
        object_free(this->items[i]);
    free(this->items);
    _object_free((Object *)this);
}

Object * _list_get(List *this, size_t index) {
    return this->items[index];
}

void _list_set(List *this, size_t index, Object *item) {
    if (index > this->capacity) {
        while (index > this->capacity)
            this->capacity *= 2;
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    while (this->size <= index)
        this->items[this->size++] = NULL;
    this->items[index] = item;
}

void _list_add(List *this, Object *item) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    this->items[this->size++] = item;
}

void _list_insert(List *this, size_t index, Object *item) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    for (size_t i = this->size - 1; i >= index; i--)
        this->items[i + 1] = this->items[i];
    this->size++;
    this->items[index] = item;
}

void _list_remove(List *this, size_t index) {
    for (size_t i = index; i < this->size; i++)
        this->items[i] = this->items[i + 1];
    this->size--;
}

// Run: ../ccc.py hello.cc && gcc --std=c11 -Wall -Wextra -Wpedantic -Werror hello.c -o hello.exe && ./hello.exe

// Person
typedef struct Person Person;

typedef struct PersonVtbl {
    // Person
    void  (*free)(Person *this);
} PersonVtbl;

struct Person {
    PersonVtbl *vtbl;
    // Object
    size_t refs;
    // Person
    char * name;
    int32_t age;
};

void _person_init(Person *this, char * name, int32_t age);
void  _person_free(Person *this);
void  _person_greet(Person *this);
char * _person_get_name(Person *this);
int32_t _person_get_age(Person *this);
void _person_set_age(Person *this, int32_t age);

PersonVtbl _PersonVtbl = {
    // Person
    &_person_free,
};

#define person_init(this, name, age) _person_init((Person *)(this), (name), (age))
#define person_ref(this) _object_ref((Object *)(this))
#define person_free(this) ((Person *)(this))->vtbl->free((Person *)(this))
#define person_greet(this) _person_greet((Person *)(this))
#define person_get_name(this) _person_get_name((Person *)(this))
#define person_get_age(this) _person_get_age((Person *)(this))
#define person_set_age(this, age) _person_set_age((Person *)(this), (age))

void _person_init(Person *this, char * name, int32_t age) {
    object_init(this);
    this->name = strdup(name);
    this->age = age;
}

void _person_free(Person *this) {
    free(this->name);
    _object_free((Object *)this);
}

char * _person_get_name(Person *this) {
    return this->name;
}

int32_t _person_get_age(Person *this) {
    return this->age;
}

void _person_set_age(Person *this, int32_t age) {
    this->age = age;
}

Person *person_new(char * name, int32_t age) {
    Person *this = malloc(sizeof(Person));
    this->vtbl = &_PersonVtbl;
    person_init(this, name, age);
    return this;
}



void _person_greet(Person *this) { printf("Hello %s, you are %d years old!\n", this->name, this->age); }

// Main
int main(void) {
    // Simple class instance
    Person *bastiaan = person_new("Bastiaan", 21);
    person_set_age(bastiaan, person_get_age(bastiaan) + 1);
    person_greet(bastiaan);
    person_free(bastiaan);

    // Build in dynamic lists
    List *persons = list_new();
    list_add(persons, person_new("Bastiaan", 21));
    list_add(persons, person_new("Sander", 20));
    list_add(persons, person_new("Leonard", 17));
    list_add(persons, person_new("Jiska", 16));

    for (size_t i = 0; i < list_get_size(persons); i++) {
        Person *person = (Person *)list_get(persons, i);
        person_greet(person);
    }

    list_free(persons);
    return EXIT_SUCCESS;
}
