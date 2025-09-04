#include "Object.hh"

void Object::init() {}

void Object::deinit() {
    free(this);
}

Self* Object::ref() {
    this->refs++;
    return this;
}

void Object::free() {
    if (--this->refs <= 0)
        object_deinit(this);
}
