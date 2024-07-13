#include <List.hh>

void List::init() {
    object_init(this);
    this->items = malloc(sizeof(Object*) * this->capacity);
}

void List::free() {
    for (size_t i = 0; i < this->size; i++)
        object_free(this->items[i]);
    free(this->items);
    _object_free((Object*)this);
}

Object* List::get(size_t index) {
    return this->items[index];
}

void List::set(size_t index, Object* item) {
    if (index > this->capacity) {
        while (index > this->capacity)
            this->capacity <<= 1;
        this->items = realloc(this->items, sizeof(Object*) * this->capacity);
    }
    while (this->size <= index)
        this->items[this->size++] = NULL;
    this->items[index] = item;
}

void List::add(Object* item) {
    if (this->size == this->capacity) {
        this->capacity <<= 1;
        this->items = realloc(this->items, sizeof(Object*) * this->capacity);
    }
    this->items[this->size++] = item;
}

void List::insert(size_t index, Object* item) {
    if (this->size == this->capacity) {
        this->capacity <<= 1;
        this->items = realloc(this->items, sizeof(Object*) * this->capacity);
    }
    for (size_t i = this->size - 1; i >= index; i--)
        this->items[i + 1] = this->items[i];
    this->size++;
    this->items[index] = item;
}

void List::remove(size_t index) {
    for (size_t i = index; i < this->size; i++)
        this->items[i] = this->items[i + 1];
    this->size--;
}
