#include <Map.hh>

static u32 hash(char* key) {
    u32 hash = 2166136261;
    while (*key) {
        hash ^= *key++;
        hash *= 16777619;
    }
    return hash;
}

void Map::init() {
    Object::init();
    this->keys = calloc(this->capacity, sizeof(char*));
    this->values = calloc(this->capacity, sizeof(Object*));
}

void Map::deinit() {
    for (usize i = 0; i < this->filled; i++) {
        if (this->keys[i] != NULL)
            free(this->keys[i]);
        if (this->values[i] != NULL)
            object_free(this->values[i]);
    }
    free(this->keys);
    free(this->values);
    Object::deinit();
}

Object* Map::get(char* key) {
    size_t index = hash(key) & (this->capacity - 1);
    while (this->keys[index]) {
        if (!strcmp(this->keys[index], key)) {
            return this->values[index];
        }
        index = (index + 1) & (this->capacity - 1);
    }
    return NULL;
}

void Map::set(char* key, Object* value) {
    if (this->filled >= this->capacity * 3 / 4) {
        this->capacity <<= 1;
        char** new_keys = calloc(this->capacity, sizeof(char*));
        Object** new_values = calloc(this->capacity, sizeof(Object*));
        for (size_t i = 0; i < this->capacity >> 1; i++) {
            if (this->keys[i]) {
                size_t index = hash(this->keys[i]) & (this->capacity - 1);
                while (new_keys[index]) {
                    index = (index + 1) & (this->capacity - 1);
                }
                new_keys[index] = this->keys[i];
                new_values[index] = this->values[i];
            }
        }
        free(this->keys);
        free(this->values);
        this->keys = new_keys;
        this->values = new_values;
    }

    size_t index = hash(key) & (this->capacity - 1);
    while (this->keys[index]) {
        if (!strcmp(this->keys[index], key)) {
            this->values[index] = value;
            return;
        }
        index = (index + 1) & (this->capacity - 1);
    }
    this->keys[index] = strdup(key);
    this->values[index] = value;
    this->filled++;
}

void Map::remove(char* key) {
    size_t index = hash(key) & (this->capacity - 1);
    while (this->keys[index]) {
        if (!strcmp(this->keys[index], key)) {
            free(this->keys[index]);
            object_free(this->values[index]);
            this->keys[index] = NULL;
            this->values[index] = NULL;
            this->filled--;
            return;
        }
        index = (index + 1) & (this->capacity - 1);
    }
}
