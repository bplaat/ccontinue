#pragma once

#include "prelude.h"

class Object {
    usize refs = 1;

    void init();
    virtual void deinit();
    Self* ref();
    void free();
};
