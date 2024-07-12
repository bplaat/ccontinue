#include "Object.hh"

void Object::init() {}

Object* Object::ref() {
    this->refs++;
    return this;
}

void Object::free() {
    if (--this->refs == 0) free(this);
}
