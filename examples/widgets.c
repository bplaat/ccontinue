// This file is generated via the BassieC Transpiler v0.1.0
// So editing has probably no use, edit the source file

#include "widgets.h"




void _Object_Init(Object *this) {}

void _Object_Free(Object *this) {
    printf("Object_Free(0x%p)\n", this);
    free(this);
}



void _List_Init(List *this, uint32_t capacity);
void _List_Free(List *this);
Object *_List_Get(List *this, uint32_t index);
void _List_Set(List *this, uint32_t index, Object *item);
void _List_Add(List *this, Object *item);
void _List_Insert(List *this, uint32_t index, Object *item);
void _List_Remove(List *this, uint32_t index);
uint32_t _List_GetCapacity(List *this);
uint32_t _List_GetSize(List *this);

ListVtbl _ListVtbl = {
    &_List_Init,
    &_List_Free,
    &_List_Get,
    &_List_Set,
    &_List_Add,
    &_List_Insert,
    &_List_Remove,
    &_List_GetCapacity,
    &_List_GetSize
};

List *List_New(uint32_t capacity) {
    List *this = calloc(1, sizeof(List));
    this->vtbl = &_ListVtbl;
    printf("0x%p = List_New()\n", this);
    List_Init(this, capacity);
    return this;
}

uint32_t _List_GetCapacity(List *this) {
    return this->capacity;
}

uint32_t _List_GetSize(List *this) {
    return this->size;
}

void _List_Init(List *this, uint32_t capacity) {
    this->size = 0;
    this->capacity = capacity;
    this->items = malloc(sizeof(Object *) * capacity);
}

Object *_List_Get(List *this, uint32_t index) {
    return this->items[index];
}

void _List_Set(List *this, uint32_t index, Object *item) {
    if (index > this->capacity) {
        while (index > this->capacity) {
            this->capacity *= 2;
        }
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    while (this->size <= index) {
        this->items[this->size++] = NULL;
    }
    this->items[index] = item;
}

void _List_Add(List *this, Object *item) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    this->items[this->size++] = item;
}

void _List_Insert(List *this, uint32_t index, Object *item) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        this->items = realloc(this->items, sizeof(Object *) * this->capacity);
    }
    for (uint32_t i = this->size - 1; i >= index; i--) {
        this->items[i + 1] = this->items[i];
    }
    this->size++;
    this->items[index] = item;
}

void _List_Remove(List *this, uint32_t index) {
    for (uint32_t i = index; i < this->size; i++) {
        this->items[i] = this->items[i + 1];
    }
    this->size--;
}

void _List_Free(List *this) {
    for (uint32_t i = 0; i < this->size; i++) {
        if (this->items[i] != NULL) {
            Object_Free(this->items[i]);
        }
    }
    free(this->items);
    _Object_Free((Object*)this);
}



ContextVtbl _ContextVtbl = {
    &_Object_Init,
    &_Object_Free
};

Context *Context_New(void) {
    Context *this = calloc(1, sizeof(Context));
    this->vtbl = &_ContextVtbl;
    printf("0x%p = Context_New()\n", this);
    Context_Init(this);
    return this;
}

void _Widget_Init(Widget *this, Context *context);
Context *_Widget_GetContext(Widget *this);
void _Widget_SetContext(Widget *this, Context *context);
Rect *_Widget_GetRect(Widget *this);
int _Widget_GetRectX(Widget *this);
int _Widget_GetRectY(Widget *this);
int _Widget_GetRectWidth(Widget *this);
int _Widget_GetRectHeight(Widget *this);
void _Widget_SetRect(Widget *this, Rect *rect);
void _Widget_SetRectX(Widget *this, int rectX);
void _Widget_SetRectY(Widget *this, int rectY);
void _Widget_SetRectWidth(Widget *this, int rectWidth);
void _Widget_SetRectHeight(Widget *this, int rectHeight);
bool _Widget_GetVisible(Widget *this);
void _Widget_SetVisible(Widget *this, bool visible);

WidgetVtbl _WidgetVtbl = {
    &_Widget_Init,
    &_Object_Free,
    &_Widget_GetContext,
    &_Widget_SetContext,
    &_Widget_GetRect,
    &_Widget_GetRectX,
    &_Widget_GetRectY,
    &_Widget_GetRectWidth,
    &_Widget_GetRectHeight,
    &_Widget_SetRect,
    &_Widget_SetRectX,
    &_Widget_SetRectY,
    &_Widget_SetRectWidth,
    &_Widget_SetRectHeight,
    &_Widget_GetVisible,
    &_Widget_SetVisible
};

Widget *Widget_New(Context *context) {
    Widget *this = calloc(1, sizeof(Widget));
    this->vtbl = &_WidgetVtbl;
    printf("0x%p = Widget_New()\n", this);
    Widget_Init(this, context);
    return this;
}

void _Widget_Init(Widget *this, Context *context) {
    this->context = (context);
}

Context *_Widget_GetContext(Widget *this) {
    return this->context;
}

void _Widget_SetContext(Widget *this, Context *context) {
    this->context = context;
}

Rect *_Widget_GetRect(Widget *this) {
    return &this->rect;
}

int _Widget_GetRectX(Widget *this) {
    return this->rect.x;
}

int _Widget_GetRectY(Widget *this) {
    return this->rect.y;
}

int _Widget_GetRectWidth(Widget *this) {
    return this->rect.width;
}

int _Widget_GetRectHeight(Widget *this) {
    return this->rect.height;
}

void _Widget_SetRect(Widget *this, Rect *rect) {
    this->rect = *rect;
}

void _Widget_SetRectX(Widget *this, int rectX) {
    this->rect.x = rectX;
}

void _Widget_SetRectY(Widget *this, int rectY) {
    this->rect.y = rectY;
}

void _Widget_SetRectWidth(Widget *this, int rectWidth) {
    this->rect.width = rectWidth;
}

void _Widget_SetRectHeight(Widget *this, int rectHeight) {
    this->rect.height = rectHeight;
}

bool _Widget_GetVisible(Widget *this) {
    return this->visible;
}

void _Widget_SetVisible(Widget *this, bool visible) {
    this->visible = visible;
}

void _Container_Init(Container *this, Context *context) {
    _Widget_Init((Widget*)this, context);
    this->children = List_New(8);
}

void _Container_Free(Container *this) {
    if (this->children != NULL) List_Free(this->children);
    _Object_Free((Object*)this);
}

List *_Container_GetChildren(Container *this) {
    return this->children;
}

Object *_Container_ChildrenGet(Container *this, uint32_t index) {
    return List_Get(this->children, index);
}

void _Container_ChildrenSet(Container *this, uint32_t index, Object *item) {
    List_Set(this->children, index, item);
}

void _Container_ChildrenAdd(Container *this, Object *item) {
    List_Add(this->children, item);
}

void _Container_ChildrenInsert(Container *this, uint32_t index, Object *item) {
    List_Insert(this->children, index, item);
}

void _Container_ChildrenRemove(Container *this, uint32_t index) {
    List_Remove(this->children, index);
}

uint32_t _Container_ChildrenGetCapacity(Container *this) {
    return List_GetCapacity(this->children);
}

uint32_t _Container_ChildrenGetSize(Container *this) {
    return List_GetSize(this->children);
}

void _Box_Init(Box *this, Context *context, Orientation orientation);
Orientation _Box_GetOrientation(Box *this);
void _Box_SetOrientation(Box *this, Orientation orientation);

BoxVtbl _BoxVtbl = {
    &_Box_Init,
    &_Container_Free,
    &_Widget_GetContext,
    &_Widget_SetContext,
    &_Widget_GetRect,
    &_Widget_GetRectX,
    &_Widget_GetRectY,
    &_Widget_GetRectWidth,
    &_Widget_GetRectHeight,
    &_Widget_SetRect,
    &_Widget_SetRectX,
    &_Widget_SetRectY,
    &_Widget_SetRectWidth,
    &_Widget_SetRectHeight,
    &_Widget_GetVisible,
    &_Widget_SetVisible,
    &_Container_GetChildren,
    &_Container_ChildrenGet,
    &_Container_ChildrenSet,
    &_Container_ChildrenAdd,
    &_Container_ChildrenInsert,
    &_Container_ChildrenRemove,
    &_Container_ChildrenGetCapacity,
    &_Container_ChildrenGetSize,
    &_Box_GetOrientation,
    &_Box_SetOrientation
};

Box *Box_New(Context *context, Orientation orientation) {
    Box *this = calloc(1, sizeof(Box));
    this->vtbl = &_BoxVtbl;
    printf("0x%p = Box_New()\n", this);
    Box_Init(this, context, orientation);
    return this;
}

void _Box_Init(Box *this, Context *context, Orientation orientation) {
    _Container_Init((Container*)this, context);
    this->orientation = (orientation);
}

Orientation _Box_GetOrientation(Box *this) {
    return this->orientation;
}

void _Box_SetOrientation(Box *this, Orientation orientation) {
    this->orientation = orientation;
}

void _Label_Init(Label *this, Context *context, wchar_t *text);
void _Label_Free(Label *this);
wchar_t *_Label_GetText(Label *this);
void _Label_SetText(Label *this, wchar_t *text);

LabelVtbl _LabelVtbl = {
    &_Label_Init,
    &_Label_Free,
    &_Widget_GetContext,
    &_Widget_SetContext,
    &_Widget_GetRect,
    &_Widget_GetRectX,
    &_Widget_GetRectY,
    &_Widget_GetRectWidth,
    &_Widget_GetRectHeight,
    &_Widget_SetRect,
    &_Widget_SetRectX,
    &_Widget_SetRectY,
    &_Widget_SetRectWidth,
    &_Widget_SetRectHeight,
    &_Widget_GetVisible,
    &_Widget_SetVisible,
    &_Label_GetText,
    &_Label_SetText
};

Label *Label_New(Context *context, wchar_t *text) {
    Label *this = calloc(1, sizeof(Label));
    this->vtbl = &_LabelVtbl;
    printf("0x%p = Label_New()\n", this);
    Label_Init(this, context, text);
    return this;
}

void _Label_Init(Label *this, Context *context, wchar_t *text) {
    _Widget_Init((Widget*)this, context);
    this->text = wcsdup(text);
}

void _Label_Free(Label *this) {
    if (this->text != NULL) free(this->text);
    _Object_Free((Object*)this);
}

wchar_t *_Label_GetText(Label *this) {
    return this->text;
}

void _Label_SetText(Label *this, wchar_t *text) {
    if (this->text != NULL) free(this->text);
    this->text = wcsdup(text);
}

int main(void) {
    Context *context = Context_New();

    Box *box = Box_New(context, ORIENTATION_VERTICAL);
    Box_ChildrenAdd(box, OBJECT(Label_New(context, L"Line 1")));
    Box_ChildrenAdd(box, OBJECT(Label_New(context, L"Line 2")));
    Box_ChildrenAdd(box, OBJECT(Label_New(context, L"Line 3")));
    Box_Free(box);

    Context_Free(context);

    return EXIT_SUCCESS;
}
