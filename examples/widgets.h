// This file is generated via the BassieC Transpiler v0.1.0
// So editing has probably no use, edit the source file

#ifndef WIDGETS_H
#define WIDGETS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Rect {
    int x, y, width, height;
} Rect;

typedef enum Orientation {
    ORIENTATION_HORIZONTAL,
    ORIENTATION_VERTICAL
} Orientation;

typedef struct Object Object;

typedef struct ObjectVtbl {
    void (*Init)(Object *this);
    void (*Free)(Object *this);
} ObjectVtbl;

struct Object {
    const ObjectVtbl *vtbl;
};

#define OBJECT(object) ((Object *)object)
#define Object_Init(this) ((Object *)this)->vtbl->Init((Object *)this)
#define Object_Free(this) ((Object *)this)->vtbl->Free((Object *)this)

typedef struct List List;

typedef struct ListVtbl {
    void (*Init)(List *this, uint32_t capacity);
    void (*Free)(List *this);
    Object *(*Get)(List *this, uint32_t index);
    void (*Set)(List *this, uint32_t index, Object *item);
    void (*Add)(List *this, Object *item);
    void (*Insert)(List *this, uint32_t index, Object *item);
    void (*Remove)(List *this, uint32_t index);
    uint32_t (*GetCapacity)(List *this);
    uint32_t (*GetSize)(List *this);
} ListVtbl;

extern ListVtbl _ListVtbl;

struct List {
    const ListVtbl *vtbl;
    Object **items;
    uint32_t capacity;
    uint32_t size;
};

extern List *List_New(uint32_t capacity);

#define LIST(list) ((List *)list)
#define List_Init(this, capacity) ((List *)this)->vtbl->Init((List *)this, capacity)
#define List_Free(this) ((List *)this)->vtbl->Free((List *)this)
#define List_Get(this, index) ((List *)this)->vtbl->Get((List *)this, index)
#define List_Set(this, index, item) ((List *)this)->vtbl->Set((List *)this, index, item)
#define List_Add(this, item) ((List *)this)->vtbl->Add((List *)this, item)
#define List_Insert(this, index, item) ((List *)this)->vtbl->Insert((List *)this, index, item)
#define List_Remove(this, index) ((List *)this)->vtbl->Remove((List *)this, index)
#define List_GetCapacity(this) ((List *)this)->vtbl->GetCapacity((List *)this)
#define List_GetSize(this) ((List *)this)->vtbl->GetSize((List *)this)

typedef struct Context Context;

typedef struct ContextVtbl {
    void (*Init)(Object *this);
    void (*Free)(Object *this);
} ContextVtbl;

extern ContextVtbl _ContextVtbl;

struct Context {
    const ContextVtbl *vtbl;
};

extern Context *Context_New(void);

#define CONTEXT(context) ((Context *)context)
#define Context_Init(this) ((Object *)this)->vtbl->Init((Object *)this)
#define Context_Free(this) ((Object *)this)->vtbl->Free((Object *)this)

typedef struct Widget Widget;

typedef struct WidgetVtbl {
    void (*Init)(Widget *this, Context *context);
    void (*Free)(Object *this);
    Context *(*GetContext)(Widget *this);
    void (*SetContext)(Widget *this, Context *context);
    Rect *(*GetRect)(Widget *this);
    int (*GetRectX)(Widget *this);
    int (*GetRectY)(Widget *this);
    int (*GetRectWidth)(Widget *this);
    int (*GetRectHeight)(Widget *this);
    void (*SetRect)(Widget *this, Rect *rect);
    void (*SetRectX)(Widget *this, int rectX);
    void (*SetRectY)(Widget *this, int rectY);
    void (*SetRectWidth)(Widget *this, int rectWidth);
    void (*SetRectHeight)(Widget *this, int rectHeight);
    bool (*GetVisible)(Widget *this);
    void (*SetVisible)(Widget *this, bool visible);
} WidgetVtbl;

extern WidgetVtbl _WidgetVtbl;

struct Widget {
    const WidgetVtbl *vtbl;
    Context *context;
    Rect rect;
    bool visible;
};

extern Widget *Widget_New(Context *context);

#define WIDGET(widget) ((Widget *)widget)
#define Widget_Init(this, context) ((Widget *)this)->vtbl->Init((Widget *)this, context)
#define Widget_Free(this) ((Object *)this)->vtbl->Free((Object *)this)
#define Widget_GetContext(this) ((Widget *)this)->vtbl->GetContext((Widget *)this)
#define Widget_SetContext(this, context) ((Widget *)this)->vtbl->SetContext((Widget *)this, context)
#define Widget_GetRect(this) ((Widget *)this)->vtbl->GetRect((Widget *)this)
#define Widget_GetRectX(this) ((Widget *)this)->vtbl->GetRectX((Widget *)this)
#define Widget_GetRectY(this) ((Widget *)this)->vtbl->GetRectY((Widget *)this)
#define Widget_GetRectWidth(this) ((Widget *)this)->vtbl->GetRectWidth((Widget *)this)
#define Widget_GetRectHeight(this) ((Widget *)this)->vtbl->GetRectHeight((Widget *)this)
#define Widget_SetRect(this, rect) ((Widget *)this)->vtbl->SetRect((Widget *)this, rect)
#define Widget_SetRectX(this, rectX) ((Widget *)this)->vtbl->SetRectX((Widget *)this, rectX)
#define Widget_SetRectY(this, rectY) ((Widget *)this)->vtbl->SetRectY((Widget *)this, rectY)
#define Widget_SetRectWidth(this, rectWidth) ((Widget *)this)->vtbl->SetRectWidth((Widget *)this, rectWidth)
#define Widget_SetRectHeight(this, rectHeight) ((Widget *)this)->vtbl->SetRectHeight((Widget *)this, rectHeight)
#define Widget_GetVisible(this) ((Widget *)this)->vtbl->GetVisible((Widget *)this)
#define Widget_SetVisible(this, visible) ((Widget *)this)->vtbl->SetVisible((Widget *)this, visible)

typedef struct Container Container;

typedef struct ContainerVtbl {
    void (*Init)(Container *this, Context *context);
    void (*Free)(Container *this);
    Context *(*GetContext)(Widget *this);
    void (*SetContext)(Widget *this, Context *context);
    Rect *(*GetRect)(Widget *this);
    int (*GetRectX)(Widget *this);
    int (*GetRectY)(Widget *this);
    int (*GetRectWidth)(Widget *this);
    int (*GetRectHeight)(Widget *this);
    void (*SetRect)(Widget *this, Rect *rect);
    void (*SetRectX)(Widget *this, int rectX);
    void (*SetRectY)(Widget *this, int rectY);
    void (*SetRectWidth)(Widget *this, int rectWidth);
    void (*SetRectHeight)(Widget *this, int rectHeight);
    bool (*GetVisible)(Widget *this);
    void (*SetVisible)(Widget *this, bool visible);
    List *(*GetChildren)(Container *this);
    Object *(*ChildrenGet)(Container *this, uint32_t index);
    void (*ChildrenSet)(Container *this, uint32_t index, Object *item);
    void (*ChildrenAdd)(Container *this, Object *item);
    void (*ChildrenInsert)(Container *this, uint32_t index, Object *item);
    void (*ChildrenRemove)(Container *this, uint32_t index);
    uint32_t (*ChildrenGetCapacity)(Container *this);
    uint32_t (*ChildrenGetSize)(Container *this);
} ContainerVtbl;

struct Container {
    const ContainerVtbl *vtbl;
    Context *context;
    Rect rect;
    bool visible;
    List *children;
};

#define CONTAINER(container) ((Container *)container)
#define Container_Init(this, context) ((Container *)this)->vtbl->Init((Container *)this, context)
#define Container_Free(this) ((Container *)this)->vtbl->Free((Container *)this)
#define Container_GetContext(this) ((Widget *)this)->vtbl->GetContext((Widget *)this)
#define Container_SetContext(this, context) ((Widget *)this)->vtbl->SetContext((Widget *)this, context)
#define Container_GetRect(this) ((Widget *)this)->vtbl->GetRect((Widget *)this)
#define Container_GetRectX(this) ((Widget *)this)->vtbl->GetRectX((Widget *)this)
#define Container_GetRectY(this) ((Widget *)this)->vtbl->GetRectY((Widget *)this)
#define Container_GetRectWidth(this) ((Widget *)this)->vtbl->GetRectWidth((Widget *)this)
#define Container_GetRectHeight(this) ((Widget *)this)->vtbl->GetRectHeight((Widget *)this)
#define Container_SetRect(this, rect) ((Widget *)this)->vtbl->SetRect((Widget *)this, rect)
#define Container_SetRectX(this, rectX) ((Widget *)this)->vtbl->SetRectX((Widget *)this, rectX)
#define Container_SetRectY(this, rectY) ((Widget *)this)->vtbl->SetRectY((Widget *)this, rectY)
#define Container_SetRectWidth(this, rectWidth) ((Widget *)this)->vtbl->SetRectWidth((Widget *)this, rectWidth)
#define Container_SetRectHeight(this, rectHeight) ((Widget *)this)->vtbl->SetRectHeight((Widget *)this, rectHeight)
#define Container_GetVisible(this) ((Widget *)this)->vtbl->GetVisible((Widget *)this)
#define Container_SetVisible(this, visible) ((Widget *)this)->vtbl->SetVisible((Widget *)this, visible)
#define Container_GetChildren(this) ((Container *)this)->vtbl->GetChildren((Container *)this)
#define Container_ChildrenGet(this, index) ((Container *)this)->vtbl->ChildrenGet((Container *)this, index)
#define Container_ChildrenSet(this, index, item) ((Container *)this)->vtbl->ChildrenSet((Container *)this, index, item)
#define Container_ChildrenAdd(this, item) ((Container *)this)->vtbl->ChildrenAdd((Container *)this, item)
#define Container_ChildrenInsert(this, index, item) ((Container *)this)->vtbl->ChildrenInsert((Container *)this, index, item)
#define Container_ChildrenRemove(this, index) ((Container *)this)->vtbl->ChildrenRemove((Container *)this, index)
#define Container_ChildrenGetCapacity(this) ((Container *)this)->vtbl->ChildrenGetCapacity((Container *)this)
#define Container_ChildrenGetSize(this) ((Container *)this)->vtbl->ChildrenGetSize((Container *)this)

typedef struct Box Box;

typedef struct BoxVtbl {
    void (*Init)(Box *this, Context *context, Orientation orientation);
    void (*Free)(Container *this);
    Context *(*GetContext)(Widget *this);
    void (*SetContext)(Widget *this, Context *context);
    Rect *(*GetRect)(Widget *this);
    int (*GetRectX)(Widget *this);
    int (*GetRectY)(Widget *this);
    int (*GetRectWidth)(Widget *this);
    int (*GetRectHeight)(Widget *this);
    void (*SetRect)(Widget *this, Rect *rect);
    void (*SetRectX)(Widget *this, int rectX);
    void (*SetRectY)(Widget *this, int rectY);
    void (*SetRectWidth)(Widget *this, int rectWidth);
    void (*SetRectHeight)(Widget *this, int rectHeight);
    bool (*GetVisible)(Widget *this);
    void (*SetVisible)(Widget *this, bool visible);
    List *(*GetChildren)(Container *this);
    Object *(*ChildrenGet)(Container *this, uint32_t index);
    void (*ChildrenSet)(Container *this, uint32_t index, Object *item);
    void (*ChildrenAdd)(Container *this, Object *item);
    void (*ChildrenInsert)(Container *this, uint32_t index, Object *item);
    void (*ChildrenRemove)(Container *this, uint32_t index);
    uint32_t (*ChildrenGetCapacity)(Container *this);
    uint32_t (*ChildrenGetSize)(Container *this);
    Orientation (*GetOrientation)(Box *this);
    void (*SetOrientation)(Box *this, Orientation orientation);
} BoxVtbl;

extern BoxVtbl _BoxVtbl;

struct Box {
    const BoxVtbl *vtbl;
    Context *context;
    Rect rect;
    bool visible;
    List *children;
    Orientation orientation;
};

extern Box *Box_New(Context *context, Orientation orientation);

#define BOX(box) ((Box *)box)
#define Box_Init(this, context, orientation) ((Box *)this)->vtbl->Init((Box *)this, context, orientation)
#define Box_Free(this) ((Container *)this)->vtbl->Free((Container *)this)
#define Box_GetContext(this) ((Widget *)this)->vtbl->GetContext((Widget *)this)
#define Box_SetContext(this, context) ((Widget *)this)->vtbl->SetContext((Widget *)this, context)
#define Box_GetRect(this) ((Widget *)this)->vtbl->GetRect((Widget *)this)
#define Box_GetRectX(this) ((Widget *)this)->vtbl->GetRectX((Widget *)this)
#define Box_GetRectY(this) ((Widget *)this)->vtbl->GetRectY((Widget *)this)
#define Box_GetRectWidth(this) ((Widget *)this)->vtbl->GetRectWidth((Widget *)this)
#define Box_GetRectHeight(this) ((Widget *)this)->vtbl->GetRectHeight((Widget *)this)
#define Box_SetRect(this, rect) ((Widget *)this)->vtbl->SetRect((Widget *)this, rect)
#define Box_SetRectX(this, rectX) ((Widget *)this)->vtbl->SetRectX((Widget *)this, rectX)
#define Box_SetRectY(this, rectY) ((Widget *)this)->vtbl->SetRectY((Widget *)this, rectY)
#define Box_SetRectWidth(this, rectWidth) ((Widget *)this)->vtbl->SetRectWidth((Widget *)this, rectWidth)
#define Box_SetRectHeight(this, rectHeight) ((Widget *)this)->vtbl->SetRectHeight((Widget *)this, rectHeight)
#define Box_GetVisible(this) ((Widget *)this)->vtbl->GetVisible((Widget *)this)
#define Box_SetVisible(this, visible) ((Widget *)this)->vtbl->SetVisible((Widget *)this, visible)
#define Box_GetChildren(this) ((Container *)this)->vtbl->GetChildren((Container *)this)
#define Box_ChildrenGet(this, index) ((Container *)this)->vtbl->ChildrenGet((Container *)this, index)
#define Box_ChildrenSet(this, index, item) ((Container *)this)->vtbl->ChildrenSet((Container *)this, index, item)
#define Box_ChildrenAdd(this, item) ((Container *)this)->vtbl->ChildrenAdd((Container *)this, item)
#define Box_ChildrenInsert(this, index, item) ((Container *)this)->vtbl->ChildrenInsert((Container *)this, index, item)
#define Box_ChildrenRemove(this, index) ((Container *)this)->vtbl->ChildrenRemove((Container *)this, index)
#define Box_ChildrenGetCapacity(this) ((Container *)this)->vtbl->ChildrenGetCapacity((Container *)this)
#define Box_ChildrenGetSize(this) ((Container *)this)->vtbl->ChildrenGetSize((Container *)this)
#define Box_GetOrientation(this) ((Box *)this)->vtbl->GetOrientation((Box *)this)
#define Box_SetOrientation(this, orientation) ((Box *)this)->vtbl->SetOrientation((Box *)this, orientation)

typedef struct Label Label;

typedef struct LabelVtbl {
    void (*Init)(Label *this, Context *context, wchar_t *text);
    void (*Free)(Label *this);
    Context *(*GetContext)(Widget *this);
    void (*SetContext)(Widget *this, Context *context);
    Rect *(*GetRect)(Widget *this);
    int (*GetRectX)(Widget *this);
    int (*GetRectY)(Widget *this);
    int (*GetRectWidth)(Widget *this);
    int (*GetRectHeight)(Widget *this);
    void (*SetRect)(Widget *this, Rect *rect);
    void (*SetRectX)(Widget *this, int rectX);
    void (*SetRectY)(Widget *this, int rectY);
    void (*SetRectWidth)(Widget *this, int rectWidth);
    void (*SetRectHeight)(Widget *this, int rectHeight);
    bool (*GetVisible)(Widget *this);
    void (*SetVisible)(Widget *this, bool visible);
    wchar_t *(*GetText)(Label *this);
    void (*SetText)(Label *this, wchar_t *text);
} LabelVtbl;

extern LabelVtbl _LabelVtbl;

struct Label {
    const LabelVtbl *vtbl;
    Context *context;
    Rect rect;
    bool visible;
    wchar_t *text;
};

extern Label *Label_New(Context *context, wchar_t *text);

#define LABEL(label) ((Label *)label)
#define Label_Init(this, context, text) ((Label *)this)->vtbl->Init((Label *)this, context, text)
#define Label_Free(this) ((Label *)this)->vtbl->Free((Label *)this)
#define Label_GetContext(this) ((Widget *)this)->vtbl->GetContext((Widget *)this)
#define Label_SetContext(this, context) ((Widget *)this)->vtbl->SetContext((Widget *)this, context)
#define Label_GetRect(this) ((Widget *)this)->vtbl->GetRect((Widget *)this)
#define Label_GetRectX(this) ((Widget *)this)->vtbl->GetRectX((Widget *)this)
#define Label_GetRectY(this) ((Widget *)this)->vtbl->GetRectY((Widget *)this)
#define Label_GetRectWidth(this) ((Widget *)this)->vtbl->GetRectWidth((Widget *)this)
#define Label_GetRectHeight(this) ((Widget *)this)->vtbl->GetRectHeight((Widget *)this)
#define Label_SetRect(this, rect) ((Widget *)this)->vtbl->SetRect((Widget *)this, rect)
#define Label_SetRectX(this, rectX) ((Widget *)this)->vtbl->SetRectX((Widget *)this, rectX)
#define Label_SetRectY(this, rectY) ((Widget *)this)->vtbl->SetRectY((Widget *)this, rectY)
#define Label_SetRectWidth(this, rectWidth) ((Widget *)this)->vtbl->SetRectWidth((Widget *)this, rectWidth)
#define Label_SetRectHeight(this, rectHeight) ((Widget *)this)->vtbl->SetRectHeight((Widget *)this, rectHeight)
#define Label_GetVisible(this) ((Widget *)this)->vtbl->GetVisible((Widget *)this)
#define Label_SetVisible(this, visible) ((Widget *)this)->vtbl->SetVisible((Widget *)this, visible)
#define Label_GetText(this) ((Label *)this)->vtbl->GetText((Label *)this)
#define Label_SetText(this, text) ((Label *)this)->vtbl->SetText((Label *)this, text)

#endif
