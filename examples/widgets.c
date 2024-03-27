// @generated
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *strdup(const char *s) {
    char *n = malloc(strlen(s) + 1);
    strcpy(n, s);
    return n;
}


typedef struct Object Object;

typedef struct ObjectVtbl {
    // Object
    void  (*free)(Object *this);
} ObjectVtbl;

struct Object {
    ObjectVtbl *vtbl;
    // Object
    size_t refs;
};

void  _object_init(Object *this);
Object * _object_ref(Object *this);
void  _object_free(Object *this);

ObjectVtbl _ObjectVtbl = {
    // Object
    &_object_free,
};

#define object_init(this) _object_init((Object *)(this))
#define object_ref(this) _object_ref((Object *)(this))
#define object_free(this) ((Object *)(this))->vtbl->free((Object *)(this))



void _object_init(Object *this) {
    this->refs = 1;}

Object * _object_ref(Object *this) {
    this->refs++;
    return this;
}

void _object_free(Object *this) {
    if (--this->refs <= 0)
        free(this);
}


typedef struct List List;

typedef struct ListVtbl {
    // List
    void  (*free)(List *this);
} ListVtbl;

struct List {
    ListVtbl *vtbl;
    // Object
    size_t refs;
    // List
    Object ** items;
    size_t capacity;
    size_t size;
};

void  _list_init(List *this);
void  _list_free(List *this);
Object * _list_get(List *this, size_t  index);
void  _list_set(List *this, size_t  index, Object * item);
void  _list_add(List *this, Object * item);
void  _list_insert(List *this, size_t  index, Object * item);
void  _list_remove(List *this, size_t  index);
size_t _list_get_capacity(List *this);
size_t _list_get_size(List *this);

ListVtbl _ListVtbl = {
    // List
    &_list_free,
};

#define list_init(this) _list_init((List *)(this))
#define list_ref(this) _object_ref((Object *)(this))
#define list_free(this) ((List *)(this))->vtbl->free((List *)(this))
#define list_get(this, index) _list_get((List *)(this), (index))
#define list_set(this, index, item) _list_set((List *)(this), (index), (Object *)(item))
#define list_add(this, item) _list_add((List *)(this), (Object *)(item))
#define list_insert(this, index, item) _list_insert((List *)(this), (index), (Object *)(item))
#define list_remove(this, index) _list_remove((List *)(this), (index))
#define list_get_capacity(this) _list_get_capacity((List *)(this))
#define list_get_size(this) _list_get_size((List *)(this))

size_t _list_get_capacity(List *this) {
    return this->capacity;
}

size_t _list_get_size(List *this) {
    return this->size;
}

List *list_new(void) {
    List *this = malloc(sizeof(List));
    this->vtbl = &_ListVtbl;
    list_init(this);
    return this;
}



void _list_init(List *this) {
    this->capacity = 8;
    this->size = 0;
    object_init(this);
    this->items = malloc(sizeof(Object *) * this->capacity);
}

void _list_free(List *this) {
    for (size_t i = 0; i < this->size; i++)
        object_free(this->items[i]);
    free(this->items);
    _object_free((Object *)this);
}

Object * _list_get(List *this, size_t index) {
    return this->items[index];
}

void _list_set(List *this, size_t index, Object *item) {
    if (index > this->capacity) {
        while (index > this->capacity)
            this->capacity *= 2;
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    while (this->size <= index)
        this->items[this->size++] = NULL;
    this->items[index] = item;
}

void _list_add(List *this, Object *item) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    this->items[this->size++] = item;
}

void _list_insert(List *this, size_t index, Object *item) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    for (size_t i = this->size - 1; i >= index; i--)
        this->items[i + 1] = this->items[i];
    this->size++;
    this->items[index] = item;
}

void _list_remove(List *this, size_t index) {
    for (size_t i = index; i < this->size; i++)
        this->items[i] = this->items[i + 1];
    this->size--;
}

// Run: ../ccc.py widgets.cc && gcc --std=c11 -Wall -Wextra -Wpedantic -Werror widgets.c -o widgets.exe && ./widgets.exe

// Context
typedef struct Context Context;

typedef struct ContextVtbl {
    // Object
    void  (*free)(Object *this);
} ContextVtbl;

struct Context {
    ContextVtbl *vtbl;
    // Object
    size_t refs;
};


ContextVtbl _ContextVtbl = {
    // Object
    &_object_free,
};

#define context_init(this) _object_init((Object *)(this))
#define context_ref(this) _object_ref((Object *)(this))
#define context_free(this) ((Context *)(this))->vtbl->free((Object *)(this))

Context *context_new(void) {
    Context *this = malloc(sizeof(Context));
    this->vtbl = &_ContextVtbl;
    context_init(this);
    return this;
}



// Widget
typedef struct Widget Widget;

typedef struct WidgetVtbl {
    // Object
    void  (*free)(Object *this);
    // Widget
    void  (*draw)(Widget *this);
} WidgetVtbl;

struct Widget {
    WidgetVtbl *vtbl;
    // Object
    size_t refs;
    // Widget
    Context * context;
    bool visible;
};

void _widget_init(Widget *this, Context * context);
void  _widget_draw(Widget *this);
Context * _widget_get_context(Widget *this);
bool _widget_get_visible(Widget *this);
void _widget_set_visible(Widget *this, bool visible);

WidgetVtbl _WidgetVtbl = {
    // Object
    &_object_free,
    // Widget
    &_widget_draw,
};

#define widget_init(this, context) _widget_init((Widget *)(this), (Context *)(context))
#define widget_ref(this) _object_ref((Object *)(this))
#define widget_free(this) ((Widget *)(this))->vtbl->free((Object *)(this))
#define widget_draw(this) ((Widget *)(this))->vtbl->draw((Widget *)(this))
#define widget_get_context(this) _widget_get_context((Widget *)(this))
#define widget_get_visible(this) _widget_get_visible((Widget *)(this))
#define widget_set_visible(this, visible) _widget_set_visible((Widget *)(this), (visible))

void _widget_init(Widget *this, Context * context) {
    object_init(this);
    this->context = context;
    this->visible = true;
}

Context * _widget_get_context(Widget *this) {
    return this->context;
}

bool _widget_get_visible(Widget *this) {
    return this->visible;
}

void _widget_set_visible(Widget *this, bool visible) {
    this->visible = visible;
}

Widget *widget_new(Context * context) {
    Widget *this = malloc(sizeof(Widget));
    this->vtbl = &_WidgetVtbl;
    widget_init(this, context);
    return this;
}



void _widget_draw(Widget *this) { (void)this; }

// Container
typedef struct Container Container;

typedef struct ContainerVtbl {
    // Container
    void  (*free)(Container *this);
    // Widget
    void  (*draw)(Widget *this);
} ContainerVtbl;

struct Container {
    ContainerVtbl *vtbl;
    // Object
    size_t refs;
    // Widget
    Context * context;
    bool visible;
    // Container
    List * children;
};

void _container_init(Container *this, Context * context);
void  _container_free(Container *this);
void  _container_add(Container *this, Widget * widget);
List * _container_get_children(Container *this);

ContainerVtbl _ContainerVtbl = {
    // Container
    &_container_free,
    // Widget
    &_widget_draw,
};

#define container_init(this, context) _container_init((Container *)(this), (Context *)(context))
#define container_ref(this) _object_ref((Object *)(this))
#define container_free(this) ((Container *)(this))->vtbl->free((Container *)(this))
#define container_draw(this) ((Container *)(this))->vtbl->draw((Widget *)(this))
#define container_get_context(this) _widget_get_context((Widget *)(this))
#define container_get_visible(this) _widget_get_visible((Widget *)(this))
#define container_set_visible(this, visible) _widget_set_visible((Widget *)(this), (visible))
#define container_add(this, widget) _container_add((Container *)(this), (Widget *)(widget))
#define container_get_children(this) _container_get_children((Container *)(this))

void _container_init(Container *this, Context * context) {
    widget_init(this, context);
    this->children = list_new();
}

void _container_free(Container *this) {
    list_free(this->children);
    _object_free((Object *)this);
}

List * _container_get_children(Container *this) {
    return this->children;
}

Container *container_new(Context * context) {
    Container *this = malloc(sizeof(Container));
    this->vtbl = &_ContainerVtbl;
    container_init(this, context);
    return this;
}



void _container_add(Container *this, Widget *widget) { list_add(this->children, widget); }

// Orientation
typedef enum Orientation { ORIENTATION_HORIZONTAL, ORIENTATION_VERTICAL } Orientation;

// Box
typedef struct Box Box;

typedef struct BoxVtbl {
    // Box
    void  (*free)(Box *this);
    // Widget
    void  (*draw)(Widget *this);
} BoxVtbl;

struct Box {
    BoxVtbl *vtbl;
    // Object
    size_t refs;
    // Widget
    Context * context;
    bool visible;
    // Container
    List * children;
    // Box
    Orientation orientation;
};

void _box_init(Box *this, Context * context, Orientation orientation);
void  _box_free(Box *this);
Orientation _box_get_orientation(Box *this);
void _box_set_orientation(Box *this, Orientation orientation);

BoxVtbl _BoxVtbl = {
    // Box
    &_box_free,
    // Widget
    &_widget_draw,
};

#define box_init(this, context, orientation) _box_init((Box *)(this), (Context *)(context), (orientation))
#define box_ref(this) _object_ref((Object *)(this))
#define box_free(this) ((Box *)(this))->vtbl->free((Box *)(this))
#define box_draw(this) ((Box *)(this))->vtbl->draw((Widget *)(this))
#define box_get_context(this) _widget_get_context((Widget *)(this))
#define box_get_visible(this) _widget_get_visible((Widget *)(this))
#define box_set_visible(this, visible) _widget_set_visible((Widget *)(this), (visible))
#define box_add(this, widget) _container_add((Container *)(this), (Widget *)(widget))
#define box_get_children(this) _container_get_children((Container *)(this))
#define box_get_orientation(this) _box_get_orientation((Box *)(this))
#define box_set_orientation(this, orientation) _box_set_orientation((Box *)(this), (orientation))

void _box_init(Box *this, Context * context, Orientation orientation) {
    container_init(this, context);
    this->orientation = orientation;
}

void _box_free(Box *this) {
    _container_free((Container *)this);
}

Orientation _box_get_orientation(Box *this) {
    return this->orientation;
}

void _box_set_orientation(Box *this, Orientation orientation) {
    this->orientation = orientation;
}

Box *box_new(Context * context, Orientation orientation) {
    Box *this = malloc(sizeof(Box));
    this->vtbl = &_BoxVtbl;
    box_init(this, context, orientation);
    return this;
}



// Label
typedef struct Label Label;

typedef struct LabelVtbl {
    // Label
    void  (*free)(Label *this);
    // Widget
    void  (*draw)(Widget *this);
} LabelVtbl;

struct Label {
    LabelVtbl *vtbl;
    // Object
    size_t refs;
    // Widget
    Context * context;
    bool visible;
    // Label
    char * text;
};

void _label_init(Label *this, Context * context, char * text);
void  _label_free(Label *this);
char * _label_get_text(Label *this);
void _label_set_text(Label *this, char * text);

LabelVtbl _LabelVtbl = {
    // Label
    &_label_free,
    // Widget
    &_widget_draw,
};

#define label_init(this, context, text) _label_init((Label *)(this), (Context *)(context), (text))
#define label_ref(this) _object_ref((Object *)(this))
#define label_free(this) ((Label *)(this))->vtbl->free((Label *)(this))
#define label_draw(this) ((Label *)(this))->vtbl->draw((Widget *)(this))
#define label_get_context(this) _widget_get_context((Widget *)(this))
#define label_get_visible(this) _widget_get_visible((Widget *)(this))
#define label_set_visible(this, visible) _widget_set_visible((Widget *)(this), (visible))
#define label_get_text(this) _label_get_text((Label *)(this))
#define label_set_text(this, text) _label_set_text((Label *)(this), (text))

void _label_init(Label *this, Context * context, char * text) {
    widget_init(this, context);
    this->text = strdup(text);
}

void _label_free(Label *this) {
    free(this->text);
    _object_free((Object *)this);
}

char * _label_get_text(Label *this) {
    return this->text;
}

void _label_set_text(Label *this, char * text) {
    this->text = text;
}

Label *label_new(Context * context, char * text) {
    Label *this = malloc(sizeof(Label));
    this->vtbl = &_LabelVtbl;
    label_init(this, context, text);
    return this;
}



// Main
int main(void) {
    Context *context = context_new();

    Box *box = box_new(context, ORIENTATION_VERTICAL);
    box_add(box, label_new(context, "Line 1"));
    box_add(box, label_new(context, "Line 2"));
    box_add(box, label_new(context, "Line 3"));
    box_free(box);

    context_free(context);
    return EXIT_SUCCESS;
}
