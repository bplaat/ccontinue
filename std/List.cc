#include <List.hh>

void List::init() {
    object_init(this);
    this->items = malloc(sizeof(Object*) * this->capacity);
}

void List::free() {
    for (usize i = 0; i < this->size; i++)
        object_free(this->items[i]);
    free(this->items);
    _object_free((Object*)this);
}

Object* List::get(usize index) {
    return this->items[index];
}

void List::set(usize index, Object* item) {
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

void List::insert(usize index, Object* item) {
    if (this->size == this->capacity) {
        this->capacity <<= 1;
        this->items = realloc(this->items, sizeof(Object*) * this->capacity);
    }
    for (usize i = this->size - 1; i >= index; i--)
        this->items[i + 1] = this->items[i];
    this->size++;
    this->items[index] = item;
}

void List::remove(usize index) {
    for (usize i = index; i < this->size; i++)
        this->items[i] = this->items[i + 1];
    this->size--;
}
