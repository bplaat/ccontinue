#pragma once

#include "Object.hh"

class List : Object {
    Object** items;
    @get size_t capacity = 8;
    @get size_t size = 0;

    void init();
    virtual void free();
    Object* get(size_t index);
    void set(size_t index, Object* item);
    void add(Object* item);
    void insert(size_t index, Object* item);
    void remove(size_t index);
};
