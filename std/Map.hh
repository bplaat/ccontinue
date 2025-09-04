#pragma once

#include "Object.hh"

class Map {
    char** keys;
    Object** values;
    @get usize capacity = 8;
    @get usize filled = 0;

    void init();
    virtual void deinit();
    Object* get(char* key);
    void set(char* key, Object* value);
    void remove(char* key);
};
