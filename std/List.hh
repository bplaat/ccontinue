#pragma once

#include "Object.hh"

class List : Object {
    Object** items;
    @get usize capacity = 8;
    @get usize size = 0;

    void init();
    virtual List* ref();
    virtual void free();
    Object* get(usize index);
    void set(usize index, Object* item);
    void add(Object* item);
    void insert(usize index, Object* item);
    void remove(usize index);
};
