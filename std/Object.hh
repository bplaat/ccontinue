#pragma once

#include <pollyfills.h>

class Object {
    size_t refs = 1;

    void init();
    virtual Object* ref();
    virtual void free();
};
