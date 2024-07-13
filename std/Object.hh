#pragma once

#include "prelude.h"

class Object {
    usize refs = 1;

    void init();
    virtual Object* ref();
    virtual void free();
};
