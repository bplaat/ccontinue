#pragma once

#include "prelude.h"

class Object {
    i32 refs = 1;

    void init();
    virtual Object* ref();
    virtual void free();
};
