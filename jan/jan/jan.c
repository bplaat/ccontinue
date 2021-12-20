// This file is generated via the BassieC Transpiler v0.1.0
// So editing has probably no use, edit the source file

#include "jan.h"




void _Object_Init(Object *this) {}

void _Object_Free(Object *this) {
    
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

void _JanFont_Init(JanFont *this, wchar_t *name, JanUnit size);
void _JanFont_Free(JanFont *this);
wchar_t *_JanFont_GetName(JanFont *this);
void _JanFont_SetName(JanFont *this, wchar_t *name);
JanUnit _JanFont_GetSize(JanFont *this);
void _JanFont_SetSize(JanFont *this, JanUnit size);
JanFontWeight _JanFont_GetWeight(JanFont *this);
void _JanFont_SetWeight(JanFont *this, JanFontWeight weight);
bool _JanFont_GetItalic(JanFont *this);
void _JanFont_SetItalic(JanFont *this, bool italic);
bool _JanFont_GetUnderline(JanFont *this);
void _JanFont_SetUnderline(JanFont *this, bool underline);
bool _JanFont_GetLineThrough(JanFont *this);
void _JanFont_SetLineThrough(JanFont *this, bool lineThrough);

JanFontVtbl _JanFontVtbl = {
    &_JanFont_Init,
    &_JanFont_Free,
    &_JanFont_GetName,
    &_JanFont_SetName,
    &_JanFont_GetSize,
    &_JanFont_SetSize,
    &_JanFont_GetWeight,
    &_JanFont_SetWeight,
    &_JanFont_GetItalic,
    &_JanFont_SetItalic,
    &_JanFont_GetUnderline,
    &_JanFont_SetUnderline,
    &_JanFont_GetLineThrough,
    &_JanFont_SetLineThrough
};

JanFont *JanFont_New(wchar_t *name, JanUnit size) {
    JanFont *this = calloc(1, sizeof(JanFont));
    this->vtbl = &_JanFontVtbl;
    JanFont_Init(this, name, size);
    return this;
}

void _JanFont_Init(JanFont *this, wchar_t *name, JanUnit size) {
    this->name = wcsdup(name);
    this->size = (size);
    this->weight = JAN_FONT_WEIGHT_NORMAL;
    this->italic = false;
    this->underline = false;
    this->lineThrough = false;
}

void _JanFont_Free(JanFont *this) {
    if (this->name != NULL) free(this->name);
    _Object_Free((Object*)this);
}

wchar_t *_JanFont_GetName(JanFont *this) {
    return this->name;
}

void _JanFont_SetName(JanFont *this, wchar_t *name) {
    if (this->name != NULL) free(this->name);
    this->name = wcsdup(name);
}

JanUnit _JanFont_GetSize(JanFont *this) {
    return this->size;
}

void _JanFont_SetSize(JanFont *this, JanUnit size) {
    this->size = size;
}

JanFontWeight _JanFont_GetWeight(JanFont *this) {
    return this->weight;
}

void _JanFont_SetWeight(JanFont *this, JanFontWeight weight) {
    this->weight = weight;
}

bool _JanFont_GetItalic(JanFont *this) {
    return this->italic;
}

void _JanFont_SetItalic(JanFont *this, bool italic) {
    this->italic = italic;
}

bool _JanFont_GetUnderline(JanFont *this) {
    return this->underline;
}

void _JanFont_SetUnderline(JanFont *this, bool underline) {
    this->underline = underline;
}

bool _JanFont_GetLineThrough(JanFont *this) {
    return this->lineThrough;
}

void _JanFont_SetLineThrough(JanFont *this, bool lineThrough) {
    this->lineThrough = lineThrough;
};

void _JanContext_Init(JanContext *this, Canvas *canvas);
void _JanContext_Free(JanContext *this);
void _JanContext_Resize(JanContext *this, int32_t width, int32_t height, int32_t dpi);
float _JanContext_ConvertUnit(JanContext *this, JanUnit unit, float parentSize);
Canvas *_JanContext_GetCanvas(JanContext *this);
int32_t _JanContext_GetWidth(JanContext *this);
int32_t _JanContext_GetHeight(JanContext *this);
int32_t _JanContext_GetDpi(JanContext *this);
bool _JanContext_GetDebug(JanContext *this);
void _JanContext_SetDebug(JanContext *this, bool debug);
JanFont *_JanContext_GetDefaultFont(JanContext *this);
void _JanContext_SetDefaultFont(JanContext *this, JanFont *defaultFont);

JanContextVtbl _JanContextVtbl = {
    &_JanContext_Init,
    &_JanContext_Free,
    &_JanContext_Resize,
    &_JanContext_ConvertUnit,
    &_JanContext_GetCanvas,
    &_JanContext_GetWidth,
    &_JanContext_GetHeight,
    &_JanContext_GetDpi,
    &_JanContext_GetDebug,
    &_JanContext_SetDebug,
    &_JanContext_GetDefaultFont,
    &_JanContext_SetDefaultFont
};

JanContext *JanContext_New(Canvas *canvas) {
    JanContext *this = calloc(1, sizeof(JanContext));
    this->vtbl = &_JanContextVtbl;
    JanContext_Init(this, canvas);
    return this;
}

void _JanContext_Init(JanContext *this, Canvas *canvas) {
    this->canvas = (canvas);
    this->width = -1;
    this->height = -1;
    this->dpi = -1;
    this->debug = false;
    this->defaultFont = JanFont_New(L"Segoe UI", JAN_UNIT(12, JAN_UNIT_TYPE_SP));
}

void _JanContext_Free(JanContext *this) {
    if (this->defaultFont != NULL) JanFont_Free(this->defaultFont);
    _Object_Free((Object*)this);
}

Canvas *_JanContext_GetCanvas(JanContext *this) {
    return this->canvas;
}

int32_t _JanContext_GetWidth(JanContext *this) {
    return this->width;
}

int32_t _JanContext_GetHeight(JanContext *this) {
    return this->height;
}

int32_t _JanContext_GetDpi(JanContext *this) {
    return this->dpi;
}

bool _JanContext_GetDebug(JanContext *this) {
    return this->debug;
}

void _JanContext_SetDebug(JanContext *this, bool debug) {
    this->debug = debug;
}

JanFont *_JanContext_GetDefaultFont(JanContext *this) {
    return this->defaultFont;
}

void _JanContext_SetDefaultFont(JanContext *this, JanFont *defaultFont) {
    if (this->defaultFont != NULL) JanFont_Free(this->defaultFont);
    this->defaultFont = defaultFont;
};

void _JanContext_Resize(JanContext *this, int32_t width, int32_t height, int32_t dpi) {
    this->width = width;
    this->height = height;
    this->dpi = dpi;
}

float _JanContext_ConvertUnit(JanContext *this, JanUnit unit, float parentSize) {
    if (unit.type == JAN_UNIT_TYPE_MATCH) return parentSize;
    if (unit.type == JAN_UNIT_TYPE_PX) return unit.value;
    if (unit.type == JAN_UNIT_TYPE_PT) return unit.value;
    if (unit.type == JAN_UNIT_TYPE_DP) return unit.value * ((float)this->dpi / 96);
    if (unit.type == JAN_UNIT_TYPE_SP) return unit.value; 
    if (unit.type == JAN_UNIT_TYPE_VW) return unit.value * ((float)this->width / 100);
    if (unit.type == JAN_UNIT_TYPE_VH) return unit.value * ((float)this->height / 100);
    if (unit.type == JAN_UNIT_TYPE_VMIN) return unit.value * ((float)MIN(this->width, this->height) / 100);
    if (unit.type == JAN_UNIT_TYPE_VMAX) return unit.value * ((float)MAX(this->width, this->height) / 100);
    if (unit.type == JAN_UNIT_TYPE_PERCENT) return unit.value * ((float)parentSize / 100);
    return 0;
}

void _JanWidget_Init(JanWidget *this, JanContext *context);
void _JanWidget_Measure(JanWidget *this, float parentWidth, float parentHeight);
void _JanWidget_ConvertOffsets(JanWidget *this, float parentWidth, float parentHeight);
void _JanWidget_Place(JanWidget *this, float x, float y);
void _JanWidget_Draw(JanWidget *this);
JanContext *_JanWidget_GetContext(JanWidget *this);
JanUnit _JanWidget_GetWidth(JanWidget *this);
void _JanWidget_SetWidth(JanWidget *this, JanUnit width);
JanUnit _JanWidget_GetHeight(JanWidget *this);
void _JanWidget_SetHeight(JanWidget *this, JanUnit height);
JanOffset *_JanWidget_GetPadding(JanWidget *this);
JanUnit _JanWidget_GetPaddingTop(JanWidget *this);
JanUnit _JanWidget_GetPaddingLeft(JanWidget *this);
JanUnit _JanWidget_GetPaddingRight(JanWidget *this);
JanUnit _JanWidget_GetPaddingBottom(JanWidget *this);
void _JanWidget_SetPadding(JanWidget *this, JanOffset *padding);
void _JanWidget_SetPaddingTop(JanWidget *this, JanUnit paddingTop);
void _JanWidget_SetPaddingLeft(JanWidget *this, JanUnit paddingLeft);
void _JanWidget_SetPaddingRight(JanWidget *this, JanUnit paddingRight);
void _JanWidget_SetPaddingBottom(JanWidget *this, JanUnit paddingBottom);
JanOffset *_JanWidget_GetMargin(JanWidget *this);
JanUnit _JanWidget_GetMarginTop(JanWidget *this);
JanUnit _JanWidget_GetMarginLeft(JanWidget *this);
JanUnit _JanWidget_GetMarginRight(JanWidget *this);
JanUnit _JanWidget_GetMarginBottom(JanWidget *this);
void _JanWidget_SetMargin(JanWidget *this, JanOffset *margin);
void _JanWidget_SetMarginTop(JanWidget *this, JanUnit marginTop);
void _JanWidget_SetMarginLeft(JanWidget *this, JanUnit marginLeft);
void _JanWidget_SetMarginRight(JanWidget *this, JanUnit marginRight);
void _JanWidget_SetMarginBottom(JanWidget *this, JanUnit marginBottom);
JanColor _JanWidget_GetBackgroundColor(JanWidget *this);
void _JanWidget_SetBackgroundColor(JanWidget *this, JanColor backgroundColor);
bool _JanWidget_GetVisible(JanWidget *this);
void _JanWidget_SetVisible(JanWidget *this, bool visible);

JanWidgetVtbl _JanWidgetVtbl = {
    &_JanWidget_Init,
    &_Object_Free,
    &_JanWidget_Measure,
    &_JanWidget_ConvertOffsets,
    &_JanWidget_Place,
    &_JanWidget_Draw,
    &_JanWidget_GetContext,
    &_JanWidget_GetWidth,
    &_JanWidget_SetWidth,
    &_JanWidget_GetHeight,
    &_JanWidget_SetHeight,
    &_JanWidget_GetPadding,
    &_JanWidget_GetPaddingTop,
    &_JanWidget_GetPaddingLeft,
    &_JanWidget_GetPaddingRight,
    &_JanWidget_GetPaddingBottom,
    &_JanWidget_SetPadding,
    &_JanWidget_SetPaddingTop,
    &_JanWidget_SetPaddingLeft,
    &_JanWidget_SetPaddingRight,
    &_JanWidget_SetPaddingBottom,
    &_JanWidget_GetMargin,
    &_JanWidget_GetMarginTop,
    &_JanWidget_GetMarginLeft,
    &_JanWidget_GetMarginRight,
    &_JanWidget_GetMarginBottom,
    &_JanWidget_SetMargin,
    &_JanWidget_SetMarginTop,
    &_JanWidget_SetMarginLeft,
    &_JanWidget_SetMarginRight,
    &_JanWidget_SetMarginBottom,
    &_JanWidget_GetBackgroundColor,
    &_JanWidget_SetBackgroundColor,
    &_JanWidget_GetVisible,
    &_JanWidget_SetVisible
};

JanWidget *JanWidget_New(JanContext *context) {
    JanWidget *this = calloc(1, sizeof(JanWidget));
    this->vtbl = &_JanWidgetVtbl;
    JanWidget_Init(this, context);
    return this;
}

void _JanWidget_Init(JanWidget *this, JanContext *context) {
    this->context = (context);
    this->width = JAN_UNIT_UNDEFINED;
    this->height = JAN_UNIT_UNDEFINED;
    this->padding = JAN_OFFSET(JAN_UNIT_ZERO, JAN_UNIT_ZERO, JAN_UNIT_ZERO, JAN_UNIT_ZERO);
    this->margin = JAN_OFFSET(JAN_UNIT_ZERO, JAN_UNIT_ZERO, JAN_UNIT_ZERO, JAN_UNIT_ZERO);
    this->backgroundColor = 0;
    this->visible = true;
}

JanContext *_JanWidget_GetContext(JanWidget *this) {
    return this->context;
}

JanUnit _JanWidget_GetWidth(JanWidget *this) {
    return this->width;
}

void _JanWidget_SetWidth(JanWidget *this, JanUnit width) {
    this->width = width;
}

JanUnit _JanWidget_GetHeight(JanWidget *this) {
    return this->height;
}

void _JanWidget_SetHeight(JanWidget *this, JanUnit height) {
    this->height = height;
}

JanOffset *_JanWidget_GetPadding(JanWidget *this) {
    return &this->padding;
}

JanUnit _JanWidget_GetPaddingTop(JanWidget *this) {
    return this->padding.top;
}

JanUnit _JanWidget_GetPaddingLeft(JanWidget *this) {
    return this->padding.left;
}

JanUnit _JanWidget_GetPaddingRight(JanWidget *this) {
    return this->padding.right;
}

JanUnit _JanWidget_GetPaddingBottom(JanWidget *this) {
    return this->padding.bottom;
}

void _JanWidget_SetPadding(JanWidget *this, JanOffset *padding) {
    this->padding = *padding;
}

void _JanWidget_SetPaddingTop(JanWidget *this, JanUnit paddingTop) {
    this->padding.top = paddingTop;
}

void _JanWidget_SetPaddingLeft(JanWidget *this, JanUnit paddingLeft) {
    this->padding.left = paddingLeft;
}

void _JanWidget_SetPaddingRight(JanWidget *this, JanUnit paddingRight) {
    this->padding.right = paddingRight;
}

void _JanWidget_SetPaddingBottom(JanWidget *this, JanUnit paddingBottom) {
    this->padding.bottom = paddingBottom;
}

JanOffset *_JanWidget_GetMargin(JanWidget *this) {
    return &this->margin;
}

JanUnit _JanWidget_GetMarginTop(JanWidget *this) {
    return this->margin.top;
}

JanUnit _JanWidget_GetMarginLeft(JanWidget *this) {
    return this->margin.left;
}

JanUnit _JanWidget_GetMarginRight(JanWidget *this) {
    return this->margin.right;
}

JanUnit _JanWidget_GetMarginBottom(JanWidget *this) {
    return this->margin.bottom;
}

void _JanWidget_SetMargin(JanWidget *this, JanOffset *margin) {
    this->margin = *margin;
}

void _JanWidget_SetMarginTop(JanWidget *this, JanUnit marginTop) {
    this->margin.top = marginTop;
}

void _JanWidget_SetMarginLeft(JanWidget *this, JanUnit marginLeft) {
    this->margin.left = marginLeft;
}

void _JanWidget_SetMarginRight(JanWidget *this, JanUnit marginRight) {
    this->margin.right = marginRight;
}

void _JanWidget_SetMarginBottom(JanWidget *this, JanUnit marginBottom) {
    this->margin.bottom = marginBottom;
}

JanColor _JanWidget_GetBackgroundColor(JanWidget *this) {
    return this->backgroundColor;
}

void _JanWidget_SetBackgroundColor(JanWidget *this, JanColor backgroundColor) {
    this->backgroundColor = backgroundColor;
}

bool _JanWidget_GetVisible(JanWidget *this) {
    return this->visible;
}

void _JanWidget_SetVisible(JanWidget *this, bool visible) {
    this->visible = visible;
};

void _JanWidget_Measure(JanWidget *this, float parentWidth, float parentHeight) {
    JanWidget_ConvertOffsets(this, parentWidth, parentHeight);

    this->contentRect.width = JanContext_ConvertUnit(this->context, this->width, parentWidth - this->convertedPadding.left - this->convertedPadding.right - this->convertedMargin.left - this->convertedMargin.right);
    this->paddingRect.width = this->convertedPadding.left + this->contentRect.width + this->convertedPadding.right;
    this->marginRect.width = this->convertedMargin.left + this->paddingRect.width + this->convertedMargin.right;

    this->contentRect.height = JanContext_ConvertUnit(this->context, this->height, parentHeight - this->convertedPadding.top - this->convertedPadding.bottom - this->convertedMargin.top - this->convertedMargin.bottom);
    this->paddingRect.height = this->convertedPadding.top + this->contentRect.height + this->convertedPadding.bottom;
    this->marginRect.height = this->convertedMargin.top + this->paddingRect.height + this->convertedMargin.bottom;
}

void _JanWidget_ConvertOffsets(JanWidget *this, float parentWidth, float parentHeight) {
    this->convertedPadding.top = JanContext_ConvertUnit(this->context, this->padding.top, parentHeight);
    this->convertedPadding.left = JanContext_ConvertUnit(this->context, this->padding.left, parentWidth);
    this->convertedPadding.right = JanContext_ConvertUnit(this->context, this->padding.right, parentWidth);
    this->convertedPadding.bottom = JanContext_ConvertUnit(this->context, this->padding.bottom, parentHeight);

    this->convertedMargin.top = JanContext_ConvertUnit(this->context, this->margin.top, parentHeight);
    this->convertedMargin.left = JanContext_ConvertUnit(this->context, this->margin.left, parentWidth);
    this->convertedMargin.right = JanContext_ConvertUnit(this->context, this->margin.right, parentWidth);
    this->convertedMargin.bottom = JanContext_ConvertUnit(this->context, this->margin.bottom, parentHeight);
}

void _JanWidget_Place(JanWidget *this, float x, float y) {
    this->marginRect.x = x;
    this->marginRect.y = y;

    this->paddingRect.x = this->marginRect.x + this->convertedMargin.left;
    this->paddingRect.y = this->marginRect.y + this->convertedMargin.top;

    this->contentRect.x = this->paddingRect.x + this->convertedPadding.left;
    this->contentRect.y = this->paddingRect.y + this->convertedPadding.top;
}

void _JanWidget_Draw(JanWidget *this) {
    if (!this->visible) return;
    Canvas_FillRect(this->context->canvas, (CanvasRect *)&this->paddingRect, this->backgroundColor);

    if (this->context->debug) {
        Canvas_StrokeRect(this->context->canvas, (CanvasRect *)&this->marginRect, CANVAS_RGB(255, 0, 0), 2);
        Canvas_StrokeRect(this->context->canvas, (CanvasRect *)&this->paddingRect, CANVAS_RGB(255, 128, 0), 2);
        Canvas_StrokeRect(this->context->canvas, (CanvasRect *)&this->contentRect, CANVAS_RGB(255, 255, 0), 2);
    }
}

void _JanBin_Free(JanBin *this) {
    if (this->child != NULL) JanWidget_Free(this->child);
    _Object_Free((Object*)this);
}

JanWidget *_JanBin_GetChild(JanBin *this) {
    return this->child;
}

void _JanBin_SetChild(JanBin *this, JanWidget *child) {
    if (this->child != NULL) JanWidget_Free(this->child);
    this->child = child;
};


JanScrollVtbl _JanScrollVtbl = {
    &_JanWidget_Init,
    &_JanBin_Free,
    &_JanWidget_Measure,
    &_JanWidget_ConvertOffsets,
    &_JanWidget_Place,
    &_JanWidget_Draw,
    &_JanWidget_GetContext,
    &_JanWidget_GetWidth,
    &_JanWidget_SetWidth,
    &_JanWidget_GetHeight,
    &_JanWidget_SetHeight,
    &_JanWidget_GetPadding,
    &_JanWidget_GetPaddingTop,
    &_JanWidget_GetPaddingLeft,
    &_JanWidget_GetPaddingRight,
    &_JanWidget_GetPaddingBottom,
    &_JanWidget_SetPadding,
    &_JanWidget_SetPaddingTop,
    &_JanWidget_SetPaddingLeft,
    &_JanWidget_SetPaddingRight,
    &_JanWidget_SetPaddingBottom,
    &_JanWidget_GetMargin,
    &_JanWidget_GetMarginTop,
    &_JanWidget_GetMarginLeft,
    &_JanWidget_GetMarginRight,
    &_JanWidget_GetMarginBottom,
    &_JanWidget_SetMargin,
    &_JanWidget_SetMarginTop,
    &_JanWidget_SetMarginLeft,
    &_JanWidget_SetMarginRight,
    &_JanWidget_SetMarginBottom,
    &_JanWidget_GetBackgroundColor,
    &_JanWidget_SetBackgroundColor,
    &_JanWidget_GetVisible,
    &_JanWidget_SetVisible,
    &_JanBin_GetChild,
    &_JanBin_SetChild
};

JanScroll *JanScroll_New(JanContext *context) {
    JanScroll *this = calloc(1, sizeof(JanScroll));
    this->vtbl = &_JanScrollVtbl;
    JanScroll_Init(this, context);
    return this;
};

void _JanContainer_Init(JanContainer *this, JanContext *context) {
    _JanWidget_Init((JanWidget*)this, context);
    this->children = List_New(4);
}

void _JanContainer_Free(JanContainer *this) {
    if (this->children != NULL) List_Free(this->children);
    _Object_Free((Object*)this);
}

List *_JanContainer_GetChildren(JanContainer *this) {
    return this->children;
}

Object *_JanContainer_ChildrenGet(JanContainer *this, uint32_t index) {
    return List_Get(this->children, index);
}

void _JanContainer_ChildrenSet(JanContainer *this, uint32_t index, Object *item) {
    List_Set(this->children, index, item);
}

void _JanContainer_ChildrenAdd(JanContainer *this, Object *item) {
    List_Add(this->children, item);
}

void _JanContainer_ChildrenInsert(JanContainer *this, uint32_t index, Object *item) {
    List_Insert(this->children, index, item);
}

void _JanContainer_ChildrenRemove(JanContainer *this, uint32_t index) {
    List_Remove(this->children, index);
}

uint32_t _JanContainer_ChildrenGetCapacity(JanContainer *this) {
    return List_GetCapacity(this->children);
}

uint32_t _JanContainer_ChildrenGetSize(JanContainer *this) {
    return List_GetSize(this->children);
};


JanStackVtbl _JanStackVtbl = {
    &_JanContainer_Init,
    &_JanContainer_Free,
    &_JanWidget_Measure,
    &_JanWidget_ConvertOffsets,
    &_JanWidget_Place,
    &_JanWidget_Draw,
    &_JanWidget_GetContext,
    &_JanWidget_GetWidth,
    &_JanWidget_SetWidth,
    &_JanWidget_GetHeight,
    &_JanWidget_SetHeight,
    &_JanWidget_GetPadding,
    &_JanWidget_GetPaddingTop,
    &_JanWidget_GetPaddingLeft,
    &_JanWidget_GetPaddingRight,
    &_JanWidget_GetPaddingBottom,
    &_JanWidget_SetPadding,
    &_JanWidget_SetPaddingTop,
    &_JanWidget_SetPaddingLeft,
    &_JanWidget_SetPaddingRight,
    &_JanWidget_SetPaddingBottom,
    &_JanWidget_GetMargin,
    &_JanWidget_GetMarginTop,
    &_JanWidget_GetMarginLeft,
    &_JanWidget_GetMarginRight,
    &_JanWidget_GetMarginBottom,
    &_JanWidget_SetMargin,
    &_JanWidget_SetMarginTop,
    &_JanWidget_SetMarginLeft,
    &_JanWidget_SetMarginRight,
    &_JanWidget_SetMarginBottom,
    &_JanWidget_GetBackgroundColor,
    &_JanWidget_SetBackgroundColor,
    &_JanWidget_GetVisible,
    &_JanWidget_SetVisible,
    &_JanContainer_GetChildren,
    &_JanContainer_ChildrenGet,
    &_JanContainer_ChildrenSet,
    &_JanContainer_ChildrenAdd,
    &_JanContainer_ChildrenInsert,
    &_JanContainer_ChildrenRemove,
    &_JanContainer_ChildrenGetCapacity,
    &_JanContainer_ChildrenGetSize
};

JanStack *JanStack_New(JanContext *context) {
    JanStack *this = calloc(1, sizeof(JanStack));
    this->vtbl = &_JanStackVtbl;
    JanStack_Init(this, context);
    return this;
};

void _JanBox_Init(JanBox *this, JanContext *context, JanOrientation orientation);
void _JanBox_Measure(JanBox *this, float parentWidth, float parentHeight);
void _JanBox_Place(JanBox *this, float x, float y);
void _JanBox_Draw(JanBox *this);
JanOrientation _JanBox_GetOrientation(JanBox *this);
void _JanBox_SetOrientation(JanBox *this, JanOrientation orientation);

JanBoxVtbl _JanBoxVtbl = {
    &_JanBox_Init,
    &_JanContainer_Free,
    &_JanBox_Measure,
    &_JanWidget_ConvertOffsets,
    &_JanBox_Place,
    &_JanBox_Draw,
    &_JanWidget_GetContext,
    &_JanWidget_GetWidth,
    &_JanWidget_SetWidth,
    &_JanWidget_GetHeight,
    &_JanWidget_SetHeight,
    &_JanWidget_GetPadding,
    &_JanWidget_GetPaddingTop,
    &_JanWidget_GetPaddingLeft,
    &_JanWidget_GetPaddingRight,
    &_JanWidget_GetPaddingBottom,
    &_JanWidget_SetPadding,
    &_JanWidget_SetPaddingTop,
    &_JanWidget_SetPaddingLeft,
    &_JanWidget_SetPaddingRight,
    &_JanWidget_SetPaddingBottom,
    &_JanWidget_GetMargin,
    &_JanWidget_GetMarginTop,
    &_JanWidget_GetMarginLeft,
    &_JanWidget_GetMarginRight,
    &_JanWidget_GetMarginBottom,
    &_JanWidget_SetMargin,
    &_JanWidget_SetMarginTop,
    &_JanWidget_SetMarginLeft,
    &_JanWidget_SetMarginRight,
    &_JanWidget_SetMarginBottom,
    &_JanWidget_GetBackgroundColor,
    &_JanWidget_SetBackgroundColor,
    &_JanWidget_GetVisible,
    &_JanWidget_SetVisible,
    &_JanContainer_GetChildren,
    &_JanContainer_ChildrenGet,
    &_JanContainer_ChildrenSet,
    &_JanContainer_ChildrenAdd,
    &_JanContainer_ChildrenInsert,
    &_JanContainer_ChildrenRemove,
    &_JanContainer_ChildrenGetCapacity,
    &_JanContainer_ChildrenGetSize,
    &_JanBox_GetOrientation,
    &_JanBox_SetOrientation
};

JanBox *JanBox_New(JanContext *context, JanOrientation orientation) {
    JanBox *this = calloc(1, sizeof(JanBox));
    this->vtbl = &_JanBoxVtbl;
    JanBox_Init(this, context, orientation);
    return this;
}

void _JanBox_Init(JanBox *this, JanContext *context, JanOrientation orientation) {
    _JanContainer_Init((JanContainer*)this, context);
    this->orientation = (orientation);
}

JanOrientation _JanBox_GetOrientation(JanBox *this) {
    return this->orientation;
}

void _JanBox_SetOrientation(JanBox *this, JanOrientation orientation) {
    this->orientation = orientation;
};

void _JanBox_Measure(JanBox *this, float parentWidth, float parentHeight) {
    JanWidget_ConvertOffsets(this, parentWidth, parentHeight);

    this->contentRect.width = JanContext_ConvertUnit(this->context, this->width, parentWidth - this->convertedPadding.left - this->convertedPadding.right - this->convertedMargin.left - this->convertedMargin.right);
    this->contentRect.height = JanContext_ConvertUnit(this->context, this->height, parentHeight - this->convertedPadding.top - this->convertedPadding.bottom - this->convertedMargin.top - this->convertedMargin.bottom);

    float maxWidth = 0, sumWidth = 0, maxHeight = 0, sumHeight = 0;
    for (uint32_t i = 0; i < this->children->size; i++) {
        JanWidget *child = JAN_WIDGET(this->children->items[i]);
        if (child->width.type == JAN_UNIT_TYPE_UNDEFINED) child->width = this->orientation == JAN_ORIENTATION_HORIZONTAL ? JAN_UNIT_WRAP : JAN_UNIT_MATCH;
        if (child->height.type == JAN_UNIT_TYPE_UNDEFINED) child->height = JAN_UNIT_WRAP;

        JanWidget_Measure(child, this->contentRect.width, this->contentRect.height);
        maxWidth = MAX(maxWidth, child->marginRect.width);
        sumWidth += child->marginRect.width;
        maxHeight = MAX(maxHeight, child->marginRect.height);
        sumHeight += child->marginRect.height;
    }

    if (this->width.type == JAN_UNIT_TYPE_WRAP) {
        this->contentRect.width = this->orientation == JAN_ORIENTATION_HORIZONTAL ? sumWidth : maxWidth;
    }
    if (this->height.type == JAN_UNIT_TYPE_WRAP) {
        this->contentRect.height = this->orientation == JAN_ORIENTATION_HORIZONTAL ? maxHeight : sumHeight;
    }

    this->paddingRect.width = this->convertedPadding.left + this->contentRect.width + this->convertedPadding.right;
    this->marginRect.width = this->convertedMargin.left + this->paddingRect.width + this->convertedMargin.right;

    this->paddingRect.height = this->convertedPadding.top + this->contentRect.height + this->convertedPadding.bottom;
    this->marginRect.height = this->convertedMargin.top + this->paddingRect.height + this->convertedMargin.bottom;
}

void _JanBox_Place(JanBox *this, float x, float y) {
    _JanWidget_Place((JanWidget*)this, x, y);
    float childX = this->contentRect.x;
    float childY = this->contentRect.y;
    for (uint32_t i = 0; i < this->children->size; i++) {
        JanWidget *child = JAN_WIDGET(this->children->items[i]);
        JanWidget_Place(child, childX, childY);
        if (this->orientation == JAN_ORIENTATION_HORIZONTAL) {
            childX += child->marginRect.width;
        }
        if (this->orientation == JAN_ORIENTATION_VERTICAL) {
            childY += child->marginRect.height;
        }
    }
}

void _JanBox_Draw(JanBox *this) {
    if (!this->visible) return;
    _JanWidget_Draw((JanWidget*)this);

    Canvas_Clip(this->context->canvas, (CanvasRect *)&this->contentRect);
    for (uint32_t i = 0; i < List_GetSize(this->children); i++) {
        JanWidget *child = JAN_WIDGET(List_Get(this->children, i));
        JanWidget_Draw(child);
    }
    Canvas_Clip(this->context->canvas, NULL);
}

void _JanLabel_Init(JanLabel *this, JanContext *context, wchar_t *text);
void _JanLabel_Free(JanLabel *this);
void _JanLabel_Measure(JanLabel *this, float parentWidth, float parentHeight);
void _JanLabel_Draw(JanLabel *this);
wchar_t *_JanLabel_GetText(JanLabel *this);
void _JanLabel_SetText(JanLabel *this, wchar_t *text);
JanFont *_JanLabel_GetFont(JanLabel *this);
void _JanLabel_SetFont(JanLabel *this, JanFont *font);
JanColor _JanLabel_GetTextColor(JanLabel *this);
void _JanLabel_SetTextColor(JanLabel *this, JanColor textColor);
bool _JanLabel_GetSingleLine(JanLabel *this);
void _JanLabel_SetSingleLine(JanLabel *this, bool singleLine);

JanLabelVtbl _JanLabelVtbl = {
    &_JanLabel_Init,
    &_JanLabel_Free,
    &_JanLabel_Measure,
    &_JanWidget_ConvertOffsets,
    &_JanWidget_Place,
    &_JanLabel_Draw,
    &_JanWidget_GetContext,
    &_JanWidget_GetWidth,
    &_JanWidget_SetWidth,
    &_JanWidget_GetHeight,
    &_JanWidget_SetHeight,
    &_JanWidget_GetPadding,
    &_JanWidget_GetPaddingTop,
    &_JanWidget_GetPaddingLeft,
    &_JanWidget_GetPaddingRight,
    &_JanWidget_GetPaddingBottom,
    &_JanWidget_SetPadding,
    &_JanWidget_SetPaddingTop,
    &_JanWidget_SetPaddingLeft,
    &_JanWidget_SetPaddingRight,
    &_JanWidget_SetPaddingBottom,
    &_JanWidget_GetMargin,
    &_JanWidget_GetMarginTop,
    &_JanWidget_GetMarginLeft,
    &_JanWidget_GetMarginRight,
    &_JanWidget_GetMarginBottom,
    &_JanWidget_SetMargin,
    &_JanWidget_SetMarginTop,
    &_JanWidget_SetMarginLeft,
    &_JanWidget_SetMarginRight,
    &_JanWidget_SetMarginBottom,
    &_JanWidget_GetBackgroundColor,
    &_JanWidget_SetBackgroundColor,
    &_JanWidget_GetVisible,
    &_JanWidget_SetVisible,
    &_JanLabel_GetText,
    &_JanLabel_SetText,
    &_JanLabel_GetFont,
    &_JanLabel_SetFont,
    &_JanLabel_GetTextColor,
    &_JanLabel_SetTextColor,
    &_JanLabel_GetSingleLine,
    &_JanLabel_SetSingleLine
};

JanLabel *JanLabel_New(JanContext *context, wchar_t *text) {
    JanLabel *this = calloc(1, sizeof(JanLabel));
    this->vtbl = &_JanLabelVtbl;
    JanLabel_Init(this, context, text);
    return this;
}

void _JanLabel_Init(JanLabel *this, JanContext *context, wchar_t *text) {
    _JanWidget_Init((JanWidget*)this, context);
    this->text = wcsdup(text);
    this->font = context->defaultFont;
    this->textColor = JAN_COLOR_HEX(0xffffff);
    this->singleLine = false;
}

void _JanLabel_Free(JanLabel *this) {
    if (this->text != NULL) free(this->text);
    _Object_Free((Object*)this);
}

wchar_t *_JanLabel_GetText(JanLabel *this) {
    return this->text;
}

void _JanLabel_SetText(JanLabel *this, wchar_t *text) {
    if (this->text != NULL) free(this->text);
    this->text = wcsdup(text);
}

JanFont *_JanLabel_GetFont(JanLabel *this) {
    return this->font;
}

void _JanLabel_SetFont(JanLabel *this, JanFont *font) {
    this->font = font;
}

JanColor _JanLabel_GetTextColor(JanLabel *this) {
    return this->textColor;
}

void _JanLabel_SetTextColor(JanLabel *this, JanColor textColor) {
    this->textColor = textColor;
}

bool _JanLabel_GetSingleLine(JanLabel *this) {
    return this->singleLine;
}

void _JanLabel_SetSingleLine(JanLabel *this, bool singleLine) {
    this->singleLine = singleLine;
};

void _JanLabel_Measure(JanLabel *this, float parentWidth, float parentHeight) {
    JanWidget_ConvertOffsets(this, parentWidth, parentHeight);

    this->contentRect.width = JanContext_ConvertUnit(this->context, this->width, parentWidth - this->convertedPadding.left - this->convertedPadding.right - this->convertedMargin.left - this->convertedMargin.right);
    CanvasRect measureRect = { 0, 0, this->contentRect.width, 0 };
    if (this->width.type == JAN_UNIT_TYPE_WRAP || this->height.type == JAN_UNIT_TYPE_WRAP) {
        CanvasFont font = { this->font->name, JanContext_ConvertUnit(this->context, this->font->size, 0), this->font->weight, this->font->italic, this->font->underline, this->font->lineThrough };
        Canvas_MeasureText(this->context->canvas, this->text, -1, &measureRect, &font, this->singleLine ? CANVAS_TEXT_FORMAT_DEFAULT : (CANVAS_TEXT_FORMAT_DEFAULT | CANVAS_TEXT_FORMAT_WRAP));
    }

    if (this->width.type == JAN_UNIT_TYPE_WRAP) this->contentRect.width = measureRect.width;
    this->paddingRect.width = this->convertedPadding.left + this->contentRect.width + this->convertedPadding.right;
    this->marginRect.width = this->convertedMargin.left + this->paddingRect.width + this->convertedMargin.right;

    this->contentRect.height = this->height.type == JAN_UNIT_TYPE_WRAP ? measureRect.height : JanContext_ConvertUnit(this->context, this->height, parentHeight - this->convertedPadding.top - this->convertedPadding.bottom - this->convertedMargin.top - this->convertedMargin.bottom);
    this->paddingRect.height = this->convertedPadding.top + this->contentRect.height + this->convertedPadding.bottom;
    this->marginRect.height = this->convertedMargin.top + this->paddingRect.height + this->convertedMargin.bottom;
}

void _JanLabel_Draw(JanLabel *this) {
    if (!this->visible) return;
    _JanWidget_Draw((JanWidget*)this);
    CanvasFont font = { this->font->name, JanContext_ConvertUnit(this->context, this->font->size, 0), this->font->weight, this->font->italic, this->font->underline, this->font->lineThrough };
    Canvas_DrawText(this->context->canvas, this->text, -1, (CanvasRect *)&this->contentRect, &font, this->singleLine ? CANVAS_TEXT_FORMAT_DEFAULT : (CANVAS_TEXT_FORMAT_DEFAULT | CANVAS_TEXT_FORMAT_WRAP), this->textColor);
}

void _JanButton_Init(JanButton *this, JanContext *context, wchar_t *text);

JanButtonVtbl _JanButtonVtbl = {
    &_JanButton_Init,
    &_JanLabel_Free,
    &_JanLabel_Measure,
    &_JanWidget_ConvertOffsets,
    &_JanWidget_Place,
    &_JanLabel_Draw,
    &_JanWidget_GetContext,
    &_JanWidget_GetWidth,
    &_JanWidget_SetWidth,
    &_JanWidget_GetHeight,
    &_JanWidget_SetHeight,
    &_JanWidget_GetPadding,
    &_JanWidget_GetPaddingTop,
    &_JanWidget_GetPaddingLeft,
    &_JanWidget_GetPaddingRight,
    &_JanWidget_GetPaddingBottom,
    &_JanWidget_SetPadding,
    &_JanWidget_SetPaddingTop,
    &_JanWidget_SetPaddingLeft,
    &_JanWidget_SetPaddingRight,
    &_JanWidget_SetPaddingBottom,
    &_JanWidget_GetMargin,
    &_JanWidget_GetMarginTop,
    &_JanWidget_GetMarginLeft,
    &_JanWidget_GetMarginRight,
    &_JanWidget_GetMarginBottom,
    &_JanWidget_SetMargin,
    &_JanWidget_SetMarginTop,
    &_JanWidget_SetMarginLeft,
    &_JanWidget_SetMarginRight,
    &_JanWidget_SetMarginBottom,
    &_JanWidget_GetBackgroundColor,
    &_JanWidget_SetBackgroundColor,
    &_JanWidget_GetVisible,
    &_JanWidget_SetVisible,
    &_JanLabel_GetText,
    &_JanLabel_SetText,
    &_JanLabel_GetFont,
    &_JanLabel_SetFont,
    &_JanLabel_GetTextColor,
    &_JanLabel_SetTextColor,
    &_JanLabel_GetSingleLine,
    &_JanLabel_SetSingleLine
};

JanButton *JanButton_New(JanContext *context, wchar_t *text) {
    JanButton *this = calloc(1, sizeof(JanButton));
    this->vtbl = &_JanButtonVtbl;
    JanButton_Init(this, context, text);
    return this;
};

void _JanButton_Init(JanButton *this, JanContext *context, wchar_t *text) {
    _JanLabel_Init((JanLabel*)this, context, text);
    this->padding.top = JAN_UNIT(16, JAN_UNIT_TYPE_DP);
    this->padding.left = JAN_UNIT(16, JAN_UNIT_TYPE_DP);
    this->padding.right = JAN_UNIT(16, JAN_UNIT_TYPE_DP);
    this->padding.bottom = JAN_UNIT(16, JAN_UNIT_TYPE_DP);
    this->backgroundColor = JAN_COLOR_HEX(0x222222);
    this->singleLine = true;
}

