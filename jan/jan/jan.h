// This file is generated via the BassieC Transpiler v0.1.0
// So editing has probably no use, edit the source file

#ifndef JAN_H
#define JAN_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define JAN_COLOR_RGB(r, g, b) CANVAS_RGB(r, g, b)
#define JAN_COLOR_RGBA(r, g, b, a) CANVAS_RGBA(r, g, b, a)
#define JAN_COLOR_HEX(x) CANVAS_HEX(x)
#define JAN_COLOR_HEXA(x) CANVAS_HEXA(x)


#define JAN_RECT(x, y, width, height) ((JanRect){ x, y, width, height })


#define JAN_UNIT_UNDEFINED ((JanUnit){ 0, JAN_UNIT_TYPE_UNDEFINED })
#define JAN_UNIT_WRAP ((JanUnit){ 0, JAN_UNIT_TYPE_WRAP })
#define JAN_UNIT_MATCH ((JanUnit){ 0, JAN_UNIT_TYPE_MATCH })
#define JAN_UNIT_ZERO ((JanUnit){ 0, JAN_UNIT_TYPE_PX })
#define JAN_UNIT(value, type) ((JanUnit){ value, type })


#define JAN_OFFSET(top, left, right, bottom) ((JanOffset){ top, left, right, bottom })

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "../canvas.h"


typedef uint32_t JanColor;

typedef struct JanRect {
    float x;
    float y;
    float width;
    float height;
} JanRect;

typedef enum JanUnitType {
    JAN_UNIT_TYPE_UNDEFINED,
    JAN_UNIT_TYPE_WRAP,
    JAN_UNIT_TYPE_MATCH,
    JAN_UNIT_TYPE_PX,
    JAN_UNIT_TYPE_PT,
    JAN_UNIT_TYPE_DP,
    JAN_UNIT_TYPE_SP,
    JAN_UNIT_TYPE_VW,
    JAN_UNIT_TYPE_VH,
    JAN_UNIT_TYPE_VMIN,
    JAN_UNIT_TYPE_VMAX,
    JAN_UNIT_TYPE_PERCENT
} JanUnitType;

typedef struct JanUnit {
    float value;
    JanUnitType type;
} JanUnit;

typedef struct JanOffset {
    JanUnit top;
    JanUnit left;
    JanUnit right;
    JanUnit bottom;
} JanOffset;

typedef struct JanConvertedOffset {
    float top;
    float left;
    float right;
    float bottom;
} JanConvertedOffset;


typedef enum JanOrientation {
    JAN_ORIENTATION_HORIZONTAL,
    JAN_ORIENTATION_VERTICAL
} JanOrientation;


typedef enum JanFontWeight {
    JAN_FONT_WEIGHT_NORMAL,
    JAN_FONT_WEIGHT_BOLD
} JanFontWeight;

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

typedef struct JanFont JanFont;

typedef struct JanFontVtbl {
    void (*Init)(JanFont *this, wchar_t *name, JanUnit size);
    void (*Free)(JanFont *this);
    wchar_t *(*GetName)(JanFont *this);
    void (*SetName)(JanFont *this, wchar_t *name);
    JanUnit (*GetSize)(JanFont *this);
    void (*SetSize)(JanFont *this, JanUnit size);
    JanFontWeight (*GetWeight)(JanFont *this);
    void (*SetWeight)(JanFont *this, JanFontWeight weight);
    bool (*GetItalic)(JanFont *this);
    void (*SetItalic)(JanFont *this, bool italic);
    bool (*GetUnderline)(JanFont *this);
    void (*SetUnderline)(JanFont *this, bool underline);
    bool (*GetLineThrough)(JanFont *this);
    void (*SetLineThrough)(JanFont *this, bool lineThrough);
} JanFontVtbl;

extern JanFontVtbl _JanFontVtbl;

struct JanFont {
    const JanFontVtbl *vtbl;
    wchar_t *name;
    JanUnit size;
    JanFontWeight weight;
    bool italic;
    bool underline;
    bool lineThrough;
};

extern JanFont *JanFont_New(wchar_t *name, JanUnit size);

#define JAN_FONT(janFont) ((JanFont *)janFont)
#define JanFont_Init(this, name, size) ((JanFont *)this)->vtbl->Init((JanFont *)this, name, size)
#define JanFont_Free(this) ((JanFont *)this)->vtbl->Free((JanFont *)this)
#define JanFont_GetName(this) ((JanFont *)this)->vtbl->GetName((JanFont *)this)
#define JanFont_SetName(this, name) ((JanFont *)this)->vtbl->SetName((JanFont *)this, name)
#define JanFont_GetSize(this) ((JanFont *)this)->vtbl->GetSize((JanFont *)this)
#define JanFont_SetSize(this, size) ((JanFont *)this)->vtbl->SetSize((JanFont *)this, size)
#define JanFont_GetWeight(this) ((JanFont *)this)->vtbl->GetWeight((JanFont *)this)
#define JanFont_SetWeight(this, weight) ((JanFont *)this)->vtbl->SetWeight((JanFont *)this, weight)
#define JanFont_GetItalic(this) ((JanFont *)this)->vtbl->GetItalic((JanFont *)this)
#define JanFont_SetItalic(this, italic) ((JanFont *)this)->vtbl->SetItalic((JanFont *)this, italic)
#define JanFont_GetUnderline(this) ((JanFont *)this)->vtbl->GetUnderline((JanFont *)this)
#define JanFont_SetUnderline(this, underline) ((JanFont *)this)->vtbl->SetUnderline((JanFont *)this, underline)
#define JanFont_GetLineThrough(this) ((JanFont *)this)->vtbl->GetLineThrough((JanFont *)this)
#define JanFont_SetLineThrough(this, lineThrough) ((JanFont *)this)->vtbl->SetLineThrough((JanFont *)this, lineThrough)

typedef struct JanContext JanContext;

typedef struct JanContextVtbl {
    void (*Init)(JanContext *this, Canvas *canvas);
    void (*Free)(JanContext *this);
    void (*Resize)(JanContext *this, int32_t width, int32_t height, int32_t dpi);
    float (*ConvertUnit)(JanContext *this, JanUnit unit, float parentSize);
    Canvas *(*GetCanvas)(JanContext *this);
    int32_t (*GetWidth)(JanContext *this);
    int32_t (*GetHeight)(JanContext *this);
    int32_t (*GetDpi)(JanContext *this);
    bool (*GetDebug)(JanContext *this);
    void (*SetDebug)(JanContext *this, bool debug);
    JanFont *(*GetDefaultFont)(JanContext *this);
    void (*SetDefaultFont)(JanContext *this, JanFont *defaultFont);
} JanContextVtbl;

extern JanContextVtbl _JanContextVtbl;

struct JanContext {
    const JanContextVtbl *vtbl;
    Canvas *canvas;
    int32_t width;
    int32_t height;
    int32_t dpi;
    bool debug;
    JanFont *defaultFont;
};

extern JanContext *JanContext_New(Canvas *canvas);

#define JAN_CONTEXT(janContext) ((JanContext *)janContext)
#define JanContext_Init(this, canvas) ((JanContext *)this)->vtbl->Init((JanContext *)this, canvas)
#define JanContext_Free(this) ((JanContext *)this)->vtbl->Free((JanContext *)this)
#define JanContext_Resize(this, width, height, dpi) ((JanContext *)this)->vtbl->Resize((JanContext *)this, width, height, dpi)
#define JanContext_ConvertUnit(this, unit, parentSize) ((JanContext *)this)->vtbl->ConvertUnit((JanContext *)this, unit, parentSize)
#define JanContext_GetCanvas(this) ((JanContext *)this)->vtbl->GetCanvas((JanContext *)this)
#define JanContext_GetWidth(this) ((JanContext *)this)->vtbl->GetWidth((JanContext *)this)
#define JanContext_GetHeight(this) ((JanContext *)this)->vtbl->GetHeight((JanContext *)this)
#define JanContext_GetDpi(this) ((JanContext *)this)->vtbl->GetDpi((JanContext *)this)
#define JanContext_GetDebug(this) ((JanContext *)this)->vtbl->GetDebug((JanContext *)this)
#define JanContext_SetDebug(this, debug) ((JanContext *)this)->vtbl->SetDebug((JanContext *)this, debug)
#define JanContext_GetDefaultFont(this) ((JanContext *)this)->vtbl->GetDefaultFont((JanContext *)this)
#define JanContext_SetDefaultFont(this, defaultFont) ((JanContext *)this)->vtbl->SetDefaultFont((JanContext *)this, defaultFont)

typedef struct JanWidget JanWidget;

typedef struct JanWidgetVtbl {
    void (*Init)(JanWidget *this, JanContext *context);
    void (*Free)(Object *this);
    void (*Measure)(JanWidget *this, float parentWidth, float parentHeight);
    void (*ConvertOffsets)(JanWidget *this, float parentWidth, float parentHeight);
    void (*Place)(JanWidget *this, float x, float y);
    void (*Draw)(JanWidget *this);
    JanContext *(*GetContext)(JanWidget *this);
    JanUnit (*GetWidth)(JanWidget *this);
    void (*SetWidth)(JanWidget *this, JanUnit width);
    JanUnit (*GetHeight)(JanWidget *this);
    void (*SetHeight)(JanWidget *this, JanUnit height);
    JanOffset *(*GetPadding)(JanWidget *this);
    JanUnit (*GetPaddingTop)(JanWidget *this);
    JanUnit (*GetPaddingLeft)(JanWidget *this);
    JanUnit (*GetPaddingRight)(JanWidget *this);
    JanUnit (*GetPaddingBottom)(JanWidget *this);
    void (*SetPadding)(JanWidget *this, JanOffset *padding);
    void (*SetPaddingTop)(JanWidget *this, JanUnit paddingTop);
    void (*SetPaddingLeft)(JanWidget *this, JanUnit paddingLeft);
    void (*SetPaddingRight)(JanWidget *this, JanUnit paddingRight);
    void (*SetPaddingBottom)(JanWidget *this, JanUnit paddingBottom);
    JanOffset *(*GetMargin)(JanWidget *this);
    JanUnit (*GetMarginTop)(JanWidget *this);
    JanUnit (*GetMarginLeft)(JanWidget *this);
    JanUnit (*GetMarginRight)(JanWidget *this);
    JanUnit (*GetMarginBottom)(JanWidget *this);
    void (*SetMargin)(JanWidget *this, JanOffset *margin);
    void (*SetMarginTop)(JanWidget *this, JanUnit marginTop);
    void (*SetMarginLeft)(JanWidget *this, JanUnit marginLeft);
    void (*SetMarginRight)(JanWidget *this, JanUnit marginRight);
    void (*SetMarginBottom)(JanWidget *this, JanUnit marginBottom);
    JanColor (*GetBackgroundColor)(JanWidget *this);
    void (*SetBackgroundColor)(JanWidget *this, JanColor backgroundColor);
    bool (*GetVisible)(JanWidget *this);
    void (*SetVisible)(JanWidget *this, bool visible);
} JanWidgetVtbl;

extern JanWidgetVtbl _JanWidgetVtbl;

struct JanWidget {
    const JanWidgetVtbl *vtbl;
    JanContext *context;
    JanUnit width;
    JanUnit height;
    JanOffset padding;
    JanOffset margin;
    JanColor backgroundColor;
    bool visible;
    JanConvertedOffset convertedMargin;
    JanConvertedOffset convertedPadding;
    JanRect contentRect;
    JanRect paddingRect;
    JanRect marginRect;
};

extern JanWidget *JanWidget_New(JanContext *context);

#define JAN_WIDGET(janWidget) ((JanWidget *)janWidget)
#define JanWidget_Init(this, context) ((JanWidget *)this)->vtbl->Init((JanWidget *)this, context)
#define JanWidget_Free(this) ((Object *)this)->vtbl->Free((Object *)this)
#define JanWidget_Measure(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->Measure((JanWidget *)this, parentWidth, parentHeight)
#define JanWidget_ConvertOffsets(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->ConvertOffsets((JanWidget *)this, parentWidth, parentHeight)
#define JanWidget_Place(this, x, y) ((JanWidget *)this)->vtbl->Place((JanWidget *)this, x, y)
#define JanWidget_Draw(this) ((JanWidget *)this)->vtbl->Draw((JanWidget *)this)
#define JanWidget_GetContext(this) ((JanWidget *)this)->vtbl->GetContext((JanWidget *)this)
#define JanWidget_GetWidth(this) ((JanWidget *)this)->vtbl->GetWidth((JanWidget *)this)
#define JanWidget_SetWidth(this, width) ((JanWidget *)this)->vtbl->SetWidth((JanWidget *)this, width)
#define JanWidget_GetHeight(this) ((JanWidget *)this)->vtbl->GetHeight((JanWidget *)this)
#define JanWidget_SetHeight(this, height) ((JanWidget *)this)->vtbl->SetHeight((JanWidget *)this, height)
#define JanWidget_GetPadding(this) ((JanWidget *)this)->vtbl->GetPadding((JanWidget *)this)
#define JanWidget_GetPaddingTop(this) ((JanWidget *)this)->vtbl->GetPaddingTop((JanWidget *)this)
#define JanWidget_GetPaddingLeft(this) ((JanWidget *)this)->vtbl->GetPaddingLeft((JanWidget *)this)
#define JanWidget_GetPaddingRight(this) ((JanWidget *)this)->vtbl->GetPaddingRight((JanWidget *)this)
#define JanWidget_GetPaddingBottom(this) ((JanWidget *)this)->vtbl->GetPaddingBottom((JanWidget *)this)
#define JanWidget_SetPadding(this, padding) ((JanWidget *)this)->vtbl->SetPadding((JanWidget *)this, padding)
#define JanWidget_SetPaddingTop(this, paddingTop) ((JanWidget *)this)->vtbl->SetPaddingTop((JanWidget *)this, paddingTop)
#define JanWidget_SetPaddingLeft(this, paddingLeft) ((JanWidget *)this)->vtbl->SetPaddingLeft((JanWidget *)this, paddingLeft)
#define JanWidget_SetPaddingRight(this, paddingRight) ((JanWidget *)this)->vtbl->SetPaddingRight((JanWidget *)this, paddingRight)
#define JanWidget_SetPaddingBottom(this, paddingBottom) ((JanWidget *)this)->vtbl->SetPaddingBottom((JanWidget *)this, paddingBottom)
#define JanWidget_GetMargin(this) ((JanWidget *)this)->vtbl->GetMargin((JanWidget *)this)
#define JanWidget_GetMarginTop(this) ((JanWidget *)this)->vtbl->GetMarginTop((JanWidget *)this)
#define JanWidget_GetMarginLeft(this) ((JanWidget *)this)->vtbl->GetMarginLeft((JanWidget *)this)
#define JanWidget_GetMarginRight(this) ((JanWidget *)this)->vtbl->GetMarginRight((JanWidget *)this)
#define JanWidget_GetMarginBottom(this) ((JanWidget *)this)->vtbl->GetMarginBottom((JanWidget *)this)
#define JanWidget_SetMargin(this, margin) ((JanWidget *)this)->vtbl->SetMargin((JanWidget *)this, margin)
#define JanWidget_SetMarginTop(this, marginTop) ((JanWidget *)this)->vtbl->SetMarginTop((JanWidget *)this, marginTop)
#define JanWidget_SetMarginLeft(this, marginLeft) ((JanWidget *)this)->vtbl->SetMarginLeft((JanWidget *)this, marginLeft)
#define JanWidget_SetMarginRight(this, marginRight) ((JanWidget *)this)->vtbl->SetMarginRight((JanWidget *)this, marginRight)
#define JanWidget_SetMarginBottom(this, marginBottom) ((JanWidget *)this)->vtbl->SetMarginBottom((JanWidget *)this, marginBottom)
#define JanWidget_GetBackgroundColor(this) ((JanWidget *)this)->vtbl->GetBackgroundColor((JanWidget *)this)
#define JanWidget_SetBackgroundColor(this, backgroundColor) ((JanWidget *)this)->vtbl->SetBackgroundColor((JanWidget *)this, backgroundColor)
#define JanWidget_GetVisible(this) ((JanWidget *)this)->vtbl->GetVisible((JanWidget *)this)
#define JanWidget_SetVisible(this, visible) ((JanWidget *)this)->vtbl->SetVisible((JanWidget *)this, visible)

typedef struct JanBin JanBin;

typedef struct JanBinVtbl {
    void (*Init)(JanWidget *this, JanContext *context);
    void (*Free)(JanBin *this);
    void (*Measure)(JanWidget *this, float parentWidth, float parentHeight);
    void (*ConvertOffsets)(JanWidget *this, float parentWidth, float parentHeight);
    void (*Place)(JanWidget *this, float x, float y);
    void (*Draw)(JanWidget *this);
    JanContext *(*GetContext)(JanWidget *this);
    JanUnit (*GetWidth)(JanWidget *this);
    void (*SetWidth)(JanWidget *this, JanUnit width);
    JanUnit (*GetHeight)(JanWidget *this);
    void (*SetHeight)(JanWidget *this, JanUnit height);
    JanOffset *(*GetPadding)(JanWidget *this);
    JanUnit (*GetPaddingTop)(JanWidget *this);
    JanUnit (*GetPaddingLeft)(JanWidget *this);
    JanUnit (*GetPaddingRight)(JanWidget *this);
    JanUnit (*GetPaddingBottom)(JanWidget *this);
    void (*SetPadding)(JanWidget *this, JanOffset *padding);
    void (*SetPaddingTop)(JanWidget *this, JanUnit paddingTop);
    void (*SetPaddingLeft)(JanWidget *this, JanUnit paddingLeft);
    void (*SetPaddingRight)(JanWidget *this, JanUnit paddingRight);
    void (*SetPaddingBottom)(JanWidget *this, JanUnit paddingBottom);
    JanOffset *(*GetMargin)(JanWidget *this);
    JanUnit (*GetMarginTop)(JanWidget *this);
    JanUnit (*GetMarginLeft)(JanWidget *this);
    JanUnit (*GetMarginRight)(JanWidget *this);
    JanUnit (*GetMarginBottom)(JanWidget *this);
    void (*SetMargin)(JanWidget *this, JanOffset *margin);
    void (*SetMarginTop)(JanWidget *this, JanUnit marginTop);
    void (*SetMarginLeft)(JanWidget *this, JanUnit marginLeft);
    void (*SetMarginRight)(JanWidget *this, JanUnit marginRight);
    void (*SetMarginBottom)(JanWidget *this, JanUnit marginBottom);
    JanColor (*GetBackgroundColor)(JanWidget *this);
    void (*SetBackgroundColor)(JanWidget *this, JanColor backgroundColor);
    bool (*GetVisible)(JanWidget *this);
    void (*SetVisible)(JanWidget *this, bool visible);
    JanWidget *(*GetChild)(JanBin *this);
    void (*SetChild)(JanBin *this, JanWidget *child);
} JanBinVtbl;

struct JanBin {
    const JanBinVtbl *vtbl;
    JanContext *context;
    JanUnit width;
    JanUnit height;
    JanOffset padding;
    JanOffset margin;
    JanColor backgroundColor;
    bool visible;
    JanConvertedOffset convertedMargin;
    JanConvertedOffset convertedPadding;
    JanRect contentRect;
    JanRect paddingRect;
    JanRect marginRect;
    JanWidget *child;
};

#define JAN_BIN(janBin) ((JanBin *)janBin)
#define JanBin_Init(this, context) ((JanWidget *)this)->vtbl->Init((JanWidget *)this, context)
#define JanBin_Free(this) ((JanBin *)this)->vtbl->Free((JanBin *)this)
#define JanBin_Measure(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->Measure((JanWidget *)this, parentWidth, parentHeight)
#define JanBin_ConvertOffsets(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->ConvertOffsets((JanWidget *)this, parentWidth, parentHeight)
#define JanBin_Place(this, x, y) ((JanWidget *)this)->vtbl->Place((JanWidget *)this, x, y)
#define JanBin_Draw(this) ((JanWidget *)this)->vtbl->Draw((JanWidget *)this)
#define JanBin_GetContext(this) ((JanWidget *)this)->vtbl->GetContext((JanWidget *)this)
#define JanBin_GetWidth(this) ((JanWidget *)this)->vtbl->GetWidth((JanWidget *)this)
#define JanBin_SetWidth(this, width) ((JanWidget *)this)->vtbl->SetWidth((JanWidget *)this, width)
#define JanBin_GetHeight(this) ((JanWidget *)this)->vtbl->GetHeight((JanWidget *)this)
#define JanBin_SetHeight(this, height) ((JanWidget *)this)->vtbl->SetHeight((JanWidget *)this, height)
#define JanBin_GetPadding(this) ((JanWidget *)this)->vtbl->GetPadding((JanWidget *)this)
#define JanBin_GetPaddingTop(this) ((JanWidget *)this)->vtbl->GetPaddingTop((JanWidget *)this)
#define JanBin_GetPaddingLeft(this) ((JanWidget *)this)->vtbl->GetPaddingLeft((JanWidget *)this)
#define JanBin_GetPaddingRight(this) ((JanWidget *)this)->vtbl->GetPaddingRight((JanWidget *)this)
#define JanBin_GetPaddingBottom(this) ((JanWidget *)this)->vtbl->GetPaddingBottom((JanWidget *)this)
#define JanBin_SetPadding(this, padding) ((JanWidget *)this)->vtbl->SetPadding((JanWidget *)this, padding)
#define JanBin_SetPaddingTop(this, paddingTop) ((JanWidget *)this)->vtbl->SetPaddingTop((JanWidget *)this, paddingTop)
#define JanBin_SetPaddingLeft(this, paddingLeft) ((JanWidget *)this)->vtbl->SetPaddingLeft((JanWidget *)this, paddingLeft)
#define JanBin_SetPaddingRight(this, paddingRight) ((JanWidget *)this)->vtbl->SetPaddingRight((JanWidget *)this, paddingRight)
#define JanBin_SetPaddingBottom(this, paddingBottom) ((JanWidget *)this)->vtbl->SetPaddingBottom((JanWidget *)this, paddingBottom)
#define JanBin_GetMargin(this) ((JanWidget *)this)->vtbl->GetMargin((JanWidget *)this)
#define JanBin_GetMarginTop(this) ((JanWidget *)this)->vtbl->GetMarginTop((JanWidget *)this)
#define JanBin_GetMarginLeft(this) ((JanWidget *)this)->vtbl->GetMarginLeft((JanWidget *)this)
#define JanBin_GetMarginRight(this) ((JanWidget *)this)->vtbl->GetMarginRight((JanWidget *)this)
#define JanBin_GetMarginBottom(this) ((JanWidget *)this)->vtbl->GetMarginBottom((JanWidget *)this)
#define JanBin_SetMargin(this, margin) ((JanWidget *)this)->vtbl->SetMargin((JanWidget *)this, margin)
#define JanBin_SetMarginTop(this, marginTop) ((JanWidget *)this)->vtbl->SetMarginTop((JanWidget *)this, marginTop)
#define JanBin_SetMarginLeft(this, marginLeft) ((JanWidget *)this)->vtbl->SetMarginLeft((JanWidget *)this, marginLeft)
#define JanBin_SetMarginRight(this, marginRight) ((JanWidget *)this)->vtbl->SetMarginRight((JanWidget *)this, marginRight)
#define JanBin_SetMarginBottom(this, marginBottom) ((JanWidget *)this)->vtbl->SetMarginBottom((JanWidget *)this, marginBottom)
#define JanBin_GetBackgroundColor(this) ((JanWidget *)this)->vtbl->GetBackgroundColor((JanWidget *)this)
#define JanBin_SetBackgroundColor(this, backgroundColor) ((JanWidget *)this)->vtbl->SetBackgroundColor((JanWidget *)this, backgroundColor)
#define JanBin_GetVisible(this) ((JanWidget *)this)->vtbl->GetVisible((JanWidget *)this)
#define JanBin_SetVisible(this, visible) ((JanWidget *)this)->vtbl->SetVisible((JanWidget *)this, visible)
#define JanBin_GetChild(this) ((JanBin *)this)->vtbl->GetChild((JanBin *)this)
#define JanBin_SetChild(this, child) ((JanBin *)this)->vtbl->SetChild((JanBin *)this, child)

typedef struct JanScroll JanScroll;

typedef struct JanScrollVtbl {
    void (*Init)(JanWidget *this, JanContext *context);
    void (*Free)(JanBin *this);
    void (*Measure)(JanWidget *this, float parentWidth, float parentHeight);
    void (*ConvertOffsets)(JanWidget *this, float parentWidth, float parentHeight);
    void (*Place)(JanWidget *this, float x, float y);
    void (*Draw)(JanWidget *this);
    JanContext *(*GetContext)(JanWidget *this);
    JanUnit (*GetWidth)(JanWidget *this);
    void (*SetWidth)(JanWidget *this, JanUnit width);
    JanUnit (*GetHeight)(JanWidget *this);
    void (*SetHeight)(JanWidget *this, JanUnit height);
    JanOffset *(*GetPadding)(JanWidget *this);
    JanUnit (*GetPaddingTop)(JanWidget *this);
    JanUnit (*GetPaddingLeft)(JanWidget *this);
    JanUnit (*GetPaddingRight)(JanWidget *this);
    JanUnit (*GetPaddingBottom)(JanWidget *this);
    void (*SetPadding)(JanWidget *this, JanOffset *padding);
    void (*SetPaddingTop)(JanWidget *this, JanUnit paddingTop);
    void (*SetPaddingLeft)(JanWidget *this, JanUnit paddingLeft);
    void (*SetPaddingRight)(JanWidget *this, JanUnit paddingRight);
    void (*SetPaddingBottom)(JanWidget *this, JanUnit paddingBottom);
    JanOffset *(*GetMargin)(JanWidget *this);
    JanUnit (*GetMarginTop)(JanWidget *this);
    JanUnit (*GetMarginLeft)(JanWidget *this);
    JanUnit (*GetMarginRight)(JanWidget *this);
    JanUnit (*GetMarginBottom)(JanWidget *this);
    void (*SetMargin)(JanWidget *this, JanOffset *margin);
    void (*SetMarginTop)(JanWidget *this, JanUnit marginTop);
    void (*SetMarginLeft)(JanWidget *this, JanUnit marginLeft);
    void (*SetMarginRight)(JanWidget *this, JanUnit marginRight);
    void (*SetMarginBottom)(JanWidget *this, JanUnit marginBottom);
    JanColor (*GetBackgroundColor)(JanWidget *this);
    void (*SetBackgroundColor)(JanWidget *this, JanColor backgroundColor);
    bool (*GetVisible)(JanWidget *this);
    void (*SetVisible)(JanWidget *this, bool visible);
    JanWidget *(*GetChild)(JanBin *this);
    void (*SetChild)(JanBin *this, JanWidget *child);
} JanScrollVtbl;

extern JanScrollVtbl _JanScrollVtbl;

struct JanScroll {
    const JanScrollVtbl *vtbl;
    JanContext *context;
    JanUnit width;
    JanUnit height;
    JanOffset padding;
    JanOffset margin;
    JanColor backgroundColor;
    bool visible;
    JanConvertedOffset convertedMargin;
    JanConvertedOffset convertedPadding;
    JanRect contentRect;
    JanRect paddingRect;
    JanRect marginRect;
    JanWidget *child;
};

extern JanScroll *JanScroll_New(JanContext *context);

#define JAN_SCROLL(janScroll) ((JanScroll *)janScroll)
#define JanScroll_Init(this, context) ((JanWidget *)this)->vtbl->Init((JanWidget *)this, context)
#define JanScroll_Free(this) ((JanBin *)this)->vtbl->Free((JanBin *)this)
#define JanScroll_Measure(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->Measure((JanWidget *)this, parentWidth, parentHeight)
#define JanScroll_ConvertOffsets(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->ConvertOffsets((JanWidget *)this, parentWidth, parentHeight)
#define JanScroll_Place(this, x, y) ((JanWidget *)this)->vtbl->Place((JanWidget *)this, x, y)
#define JanScroll_Draw(this) ((JanWidget *)this)->vtbl->Draw((JanWidget *)this)
#define JanScroll_GetContext(this) ((JanWidget *)this)->vtbl->GetContext((JanWidget *)this)
#define JanScroll_GetWidth(this) ((JanWidget *)this)->vtbl->GetWidth((JanWidget *)this)
#define JanScroll_SetWidth(this, width) ((JanWidget *)this)->vtbl->SetWidth((JanWidget *)this, width)
#define JanScroll_GetHeight(this) ((JanWidget *)this)->vtbl->GetHeight((JanWidget *)this)
#define JanScroll_SetHeight(this, height) ((JanWidget *)this)->vtbl->SetHeight((JanWidget *)this, height)
#define JanScroll_GetPadding(this) ((JanWidget *)this)->vtbl->GetPadding((JanWidget *)this)
#define JanScroll_GetPaddingTop(this) ((JanWidget *)this)->vtbl->GetPaddingTop((JanWidget *)this)
#define JanScroll_GetPaddingLeft(this) ((JanWidget *)this)->vtbl->GetPaddingLeft((JanWidget *)this)
#define JanScroll_GetPaddingRight(this) ((JanWidget *)this)->vtbl->GetPaddingRight((JanWidget *)this)
#define JanScroll_GetPaddingBottom(this) ((JanWidget *)this)->vtbl->GetPaddingBottom((JanWidget *)this)
#define JanScroll_SetPadding(this, padding) ((JanWidget *)this)->vtbl->SetPadding((JanWidget *)this, padding)
#define JanScroll_SetPaddingTop(this, paddingTop) ((JanWidget *)this)->vtbl->SetPaddingTop((JanWidget *)this, paddingTop)
#define JanScroll_SetPaddingLeft(this, paddingLeft) ((JanWidget *)this)->vtbl->SetPaddingLeft((JanWidget *)this, paddingLeft)
#define JanScroll_SetPaddingRight(this, paddingRight) ((JanWidget *)this)->vtbl->SetPaddingRight((JanWidget *)this, paddingRight)
#define JanScroll_SetPaddingBottom(this, paddingBottom) ((JanWidget *)this)->vtbl->SetPaddingBottom((JanWidget *)this, paddingBottom)
#define JanScroll_GetMargin(this) ((JanWidget *)this)->vtbl->GetMargin((JanWidget *)this)
#define JanScroll_GetMarginTop(this) ((JanWidget *)this)->vtbl->GetMarginTop((JanWidget *)this)
#define JanScroll_GetMarginLeft(this) ((JanWidget *)this)->vtbl->GetMarginLeft((JanWidget *)this)
#define JanScroll_GetMarginRight(this) ((JanWidget *)this)->vtbl->GetMarginRight((JanWidget *)this)
#define JanScroll_GetMarginBottom(this) ((JanWidget *)this)->vtbl->GetMarginBottom((JanWidget *)this)
#define JanScroll_SetMargin(this, margin) ((JanWidget *)this)->vtbl->SetMargin((JanWidget *)this, margin)
#define JanScroll_SetMarginTop(this, marginTop) ((JanWidget *)this)->vtbl->SetMarginTop((JanWidget *)this, marginTop)
#define JanScroll_SetMarginLeft(this, marginLeft) ((JanWidget *)this)->vtbl->SetMarginLeft((JanWidget *)this, marginLeft)
#define JanScroll_SetMarginRight(this, marginRight) ((JanWidget *)this)->vtbl->SetMarginRight((JanWidget *)this, marginRight)
#define JanScroll_SetMarginBottom(this, marginBottom) ((JanWidget *)this)->vtbl->SetMarginBottom((JanWidget *)this, marginBottom)
#define JanScroll_GetBackgroundColor(this) ((JanWidget *)this)->vtbl->GetBackgroundColor((JanWidget *)this)
#define JanScroll_SetBackgroundColor(this, backgroundColor) ((JanWidget *)this)->vtbl->SetBackgroundColor((JanWidget *)this, backgroundColor)
#define JanScroll_GetVisible(this) ((JanWidget *)this)->vtbl->GetVisible((JanWidget *)this)
#define JanScroll_SetVisible(this, visible) ((JanWidget *)this)->vtbl->SetVisible((JanWidget *)this, visible)
#define JanScroll_GetChild(this) ((JanBin *)this)->vtbl->GetChild((JanBin *)this)
#define JanScroll_SetChild(this, child) ((JanBin *)this)->vtbl->SetChild((JanBin *)this, child)

typedef struct JanContainer JanContainer;

typedef struct JanContainerVtbl {
    void (*Init)(JanContainer *this, JanContext *context);
    void (*Free)(JanContainer *this);
    void (*Measure)(JanWidget *this, float parentWidth, float parentHeight);
    void (*ConvertOffsets)(JanWidget *this, float parentWidth, float parentHeight);
    void (*Place)(JanWidget *this, float x, float y);
    void (*Draw)(JanWidget *this);
    JanContext *(*GetContext)(JanWidget *this);
    JanUnit (*GetWidth)(JanWidget *this);
    void (*SetWidth)(JanWidget *this, JanUnit width);
    JanUnit (*GetHeight)(JanWidget *this);
    void (*SetHeight)(JanWidget *this, JanUnit height);
    JanOffset *(*GetPadding)(JanWidget *this);
    JanUnit (*GetPaddingTop)(JanWidget *this);
    JanUnit (*GetPaddingLeft)(JanWidget *this);
    JanUnit (*GetPaddingRight)(JanWidget *this);
    JanUnit (*GetPaddingBottom)(JanWidget *this);
    void (*SetPadding)(JanWidget *this, JanOffset *padding);
    void (*SetPaddingTop)(JanWidget *this, JanUnit paddingTop);
    void (*SetPaddingLeft)(JanWidget *this, JanUnit paddingLeft);
    void (*SetPaddingRight)(JanWidget *this, JanUnit paddingRight);
    void (*SetPaddingBottom)(JanWidget *this, JanUnit paddingBottom);
    JanOffset *(*GetMargin)(JanWidget *this);
    JanUnit (*GetMarginTop)(JanWidget *this);
    JanUnit (*GetMarginLeft)(JanWidget *this);
    JanUnit (*GetMarginRight)(JanWidget *this);
    JanUnit (*GetMarginBottom)(JanWidget *this);
    void (*SetMargin)(JanWidget *this, JanOffset *margin);
    void (*SetMarginTop)(JanWidget *this, JanUnit marginTop);
    void (*SetMarginLeft)(JanWidget *this, JanUnit marginLeft);
    void (*SetMarginRight)(JanWidget *this, JanUnit marginRight);
    void (*SetMarginBottom)(JanWidget *this, JanUnit marginBottom);
    JanColor (*GetBackgroundColor)(JanWidget *this);
    void (*SetBackgroundColor)(JanWidget *this, JanColor backgroundColor);
    bool (*GetVisible)(JanWidget *this);
    void (*SetVisible)(JanWidget *this, bool visible);
    List *(*GetChildren)(JanContainer *this);
    Object *(*ChildrenGet)(JanContainer *this, uint32_t index);
    void (*ChildrenSet)(JanContainer *this, uint32_t index, Object *item);
    void (*ChildrenAdd)(JanContainer *this, Object *item);
    void (*ChildrenInsert)(JanContainer *this, uint32_t index, Object *item);
    void (*ChildrenRemove)(JanContainer *this, uint32_t index);
    uint32_t (*ChildrenGetCapacity)(JanContainer *this);
    uint32_t (*ChildrenGetSize)(JanContainer *this);
} JanContainerVtbl;

struct JanContainer {
    const JanContainerVtbl *vtbl;
    JanContext *context;
    JanUnit width;
    JanUnit height;
    JanOffset padding;
    JanOffset margin;
    JanColor backgroundColor;
    bool visible;
    JanConvertedOffset convertedMargin;
    JanConvertedOffset convertedPadding;
    JanRect contentRect;
    JanRect paddingRect;
    JanRect marginRect;
    List *children;
};

#define JAN_CONTAINER(janContainer) ((JanContainer *)janContainer)
#define JanContainer_Init(this, context) ((JanContainer *)this)->vtbl->Init((JanContainer *)this, context)
#define JanContainer_Free(this) ((JanContainer *)this)->vtbl->Free((JanContainer *)this)
#define JanContainer_Measure(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->Measure((JanWidget *)this, parentWidth, parentHeight)
#define JanContainer_ConvertOffsets(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->ConvertOffsets((JanWidget *)this, parentWidth, parentHeight)
#define JanContainer_Place(this, x, y) ((JanWidget *)this)->vtbl->Place((JanWidget *)this, x, y)
#define JanContainer_Draw(this) ((JanWidget *)this)->vtbl->Draw((JanWidget *)this)
#define JanContainer_GetContext(this) ((JanWidget *)this)->vtbl->GetContext((JanWidget *)this)
#define JanContainer_GetWidth(this) ((JanWidget *)this)->vtbl->GetWidth((JanWidget *)this)
#define JanContainer_SetWidth(this, width) ((JanWidget *)this)->vtbl->SetWidth((JanWidget *)this, width)
#define JanContainer_GetHeight(this) ((JanWidget *)this)->vtbl->GetHeight((JanWidget *)this)
#define JanContainer_SetHeight(this, height) ((JanWidget *)this)->vtbl->SetHeight((JanWidget *)this, height)
#define JanContainer_GetPadding(this) ((JanWidget *)this)->vtbl->GetPadding((JanWidget *)this)
#define JanContainer_GetPaddingTop(this) ((JanWidget *)this)->vtbl->GetPaddingTop((JanWidget *)this)
#define JanContainer_GetPaddingLeft(this) ((JanWidget *)this)->vtbl->GetPaddingLeft((JanWidget *)this)
#define JanContainer_GetPaddingRight(this) ((JanWidget *)this)->vtbl->GetPaddingRight((JanWidget *)this)
#define JanContainer_GetPaddingBottom(this) ((JanWidget *)this)->vtbl->GetPaddingBottom((JanWidget *)this)
#define JanContainer_SetPadding(this, padding) ((JanWidget *)this)->vtbl->SetPadding((JanWidget *)this, padding)
#define JanContainer_SetPaddingTop(this, paddingTop) ((JanWidget *)this)->vtbl->SetPaddingTop((JanWidget *)this, paddingTop)
#define JanContainer_SetPaddingLeft(this, paddingLeft) ((JanWidget *)this)->vtbl->SetPaddingLeft((JanWidget *)this, paddingLeft)
#define JanContainer_SetPaddingRight(this, paddingRight) ((JanWidget *)this)->vtbl->SetPaddingRight((JanWidget *)this, paddingRight)
#define JanContainer_SetPaddingBottom(this, paddingBottom) ((JanWidget *)this)->vtbl->SetPaddingBottom((JanWidget *)this, paddingBottom)
#define JanContainer_GetMargin(this) ((JanWidget *)this)->vtbl->GetMargin((JanWidget *)this)
#define JanContainer_GetMarginTop(this) ((JanWidget *)this)->vtbl->GetMarginTop((JanWidget *)this)
#define JanContainer_GetMarginLeft(this) ((JanWidget *)this)->vtbl->GetMarginLeft((JanWidget *)this)
#define JanContainer_GetMarginRight(this) ((JanWidget *)this)->vtbl->GetMarginRight((JanWidget *)this)
#define JanContainer_GetMarginBottom(this) ((JanWidget *)this)->vtbl->GetMarginBottom((JanWidget *)this)
#define JanContainer_SetMargin(this, margin) ((JanWidget *)this)->vtbl->SetMargin((JanWidget *)this, margin)
#define JanContainer_SetMarginTop(this, marginTop) ((JanWidget *)this)->vtbl->SetMarginTop((JanWidget *)this, marginTop)
#define JanContainer_SetMarginLeft(this, marginLeft) ((JanWidget *)this)->vtbl->SetMarginLeft((JanWidget *)this, marginLeft)
#define JanContainer_SetMarginRight(this, marginRight) ((JanWidget *)this)->vtbl->SetMarginRight((JanWidget *)this, marginRight)
#define JanContainer_SetMarginBottom(this, marginBottom) ((JanWidget *)this)->vtbl->SetMarginBottom((JanWidget *)this, marginBottom)
#define JanContainer_GetBackgroundColor(this) ((JanWidget *)this)->vtbl->GetBackgroundColor((JanWidget *)this)
#define JanContainer_SetBackgroundColor(this, backgroundColor) ((JanWidget *)this)->vtbl->SetBackgroundColor((JanWidget *)this, backgroundColor)
#define JanContainer_GetVisible(this) ((JanWidget *)this)->vtbl->GetVisible((JanWidget *)this)
#define JanContainer_SetVisible(this, visible) ((JanWidget *)this)->vtbl->SetVisible((JanWidget *)this, visible)
#define JanContainer_GetChildren(this) ((JanContainer *)this)->vtbl->GetChildren((JanContainer *)this)
#define JanContainer_ChildrenGet(this, index) ((JanContainer *)this)->vtbl->ChildrenGet((JanContainer *)this, index)
#define JanContainer_ChildrenSet(this, index, item) ((JanContainer *)this)->vtbl->ChildrenSet((JanContainer *)this, index, item)
#define JanContainer_ChildrenAdd(this, item) ((JanContainer *)this)->vtbl->ChildrenAdd((JanContainer *)this, item)
#define JanContainer_ChildrenInsert(this, index, item) ((JanContainer *)this)->vtbl->ChildrenInsert((JanContainer *)this, index, item)
#define JanContainer_ChildrenRemove(this, index) ((JanContainer *)this)->vtbl->ChildrenRemove((JanContainer *)this, index)
#define JanContainer_ChildrenGetCapacity(this) ((JanContainer *)this)->vtbl->ChildrenGetCapacity((JanContainer *)this)
#define JanContainer_ChildrenGetSize(this) ((JanContainer *)this)->vtbl->ChildrenGetSize((JanContainer *)this)

typedef struct JanStack JanStack;

typedef struct JanStackVtbl {
    void (*Init)(JanContainer *this, JanContext *context);
    void (*Free)(JanContainer *this);
    void (*Measure)(JanWidget *this, float parentWidth, float parentHeight);
    void (*ConvertOffsets)(JanWidget *this, float parentWidth, float parentHeight);
    void (*Place)(JanWidget *this, float x, float y);
    void (*Draw)(JanWidget *this);
    JanContext *(*GetContext)(JanWidget *this);
    JanUnit (*GetWidth)(JanWidget *this);
    void (*SetWidth)(JanWidget *this, JanUnit width);
    JanUnit (*GetHeight)(JanWidget *this);
    void (*SetHeight)(JanWidget *this, JanUnit height);
    JanOffset *(*GetPadding)(JanWidget *this);
    JanUnit (*GetPaddingTop)(JanWidget *this);
    JanUnit (*GetPaddingLeft)(JanWidget *this);
    JanUnit (*GetPaddingRight)(JanWidget *this);
    JanUnit (*GetPaddingBottom)(JanWidget *this);
    void (*SetPadding)(JanWidget *this, JanOffset *padding);
    void (*SetPaddingTop)(JanWidget *this, JanUnit paddingTop);
    void (*SetPaddingLeft)(JanWidget *this, JanUnit paddingLeft);
    void (*SetPaddingRight)(JanWidget *this, JanUnit paddingRight);
    void (*SetPaddingBottom)(JanWidget *this, JanUnit paddingBottom);
    JanOffset *(*GetMargin)(JanWidget *this);
    JanUnit (*GetMarginTop)(JanWidget *this);
    JanUnit (*GetMarginLeft)(JanWidget *this);
    JanUnit (*GetMarginRight)(JanWidget *this);
    JanUnit (*GetMarginBottom)(JanWidget *this);
    void (*SetMargin)(JanWidget *this, JanOffset *margin);
    void (*SetMarginTop)(JanWidget *this, JanUnit marginTop);
    void (*SetMarginLeft)(JanWidget *this, JanUnit marginLeft);
    void (*SetMarginRight)(JanWidget *this, JanUnit marginRight);
    void (*SetMarginBottom)(JanWidget *this, JanUnit marginBottom);
    JanColor (*GetBackgroundColor)(JanWidget *this);
    void (*SetBackgroundColor)(JanWidget *this, JanColor backgroundColor);
    bool (*GetVisible)(JanWidget *this);
    void (*SetVisible)(JanWidget *this, bool visible);
    List *(*GetChildren)(JanContainer *this);
    Object *(*ChildrenGet)(JanContainer *this, uint32_t index);
    void (*ChildrenSet)(JanContainer *this, uint32_t index, Object *item);
    void (*ChildrenAdd)(JanContainer *this, Object *item);
    void (*ChildrenInsert)(JanContainer *this, uint32_t index, Object *item);
    void (*ChildrenRemove)(JanContainer *this, uint32_t index);
    uint32_t (*ChildrenGetCapacity)(JanContainer *this);
    uint32_t (*ChildrenGetSize)(JanContainer *this);
} JanStackVtbl;

extern JanStackVtbl _JanStackVtbl;

struct JanStack {
    const JanStackVtbl *vtbl;
    JanContext *context;
    JanUnit width;
    JanUnit height;
    JanOffset padding;
    JanOffset margin;
    JanColor backgroundColor;
    bool visible;
    JanConvertedOffset convertedMargin;
    JanConvertedOffset convertedPadding;
    JanRect contentRect;
    JanRect paddingRect;
    JanRect marginRect;
    List *children;
};

extern JanStack *JanStack_New(JanContext *context);

#define JAN_STACK(janStack) ((JanStack *)janStack)
#define JanStack_Init(this, context) ((JanContainer *)this)->vtbl->Init((JanContainer *)this, context)
#define JanStack_Free(this) ((JanContainer *)this)->vtbl->Free((JanContainer *)this)
#define JanStack_Measure(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->Measure((JanWidget *)this, parentWidth, parentHeight)
#define JanStack_ConvertOffsets(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->ConvertOffsets((JanWidget *)this, parentWidth, parentHeight)
#define JanStack_Place(this, x, y) ((JanWidget *)this)->vtbl->Place((JanWidget *)this, x, y)
#define JanStack_Draw(this) ((JanWidget *)this)->vtbl->Draw((JanWidget *)this)
#define JanStack_GetContext(this) ((JanWidget *)this)->vtbl->GetContext((JanWidget *)this)
#define JanStack_GetWidth(this) ((JanWidget *)this)->vtbl->GetWidth((JanWidget *)this)
#define JanStack_SetWidth(this, width) ((JanWidget *)this)->vtbl->SetWidth((JanWidget *)this, width)
#define JanStack_GetHeight(this) ((JanWidget *)this)->vtbl->GetHeight((JanWidget *)this)
#define JanStack_SetHeight(this, height) ((JanWidget *)this)->vtbl->SetHeight((JanWidget *)this, height)
#define JanStack_GetPadding(this) ((JanWidget *)this)->vtbl->GetPadding((JanWidget *)this)
#define JanStack_GetPaddingTop(this) ((JanWidget *)this)->vtbl->GetPaddingTop((JanWidget *)this)
#define JanStack_GetPaddingLeft(this) ((JanWidget *)this)->vtbl->GetPaddingLeft((JanWidget *)this)
#define JanStack_GetPaddingRight(this) ((JanWidget *)this)->vtbl->GetPaddingRight((JanWidget *)this)
#define JanStack_GetPaddingBottom(this) ((JanWidget *)this)->vtbl->GetPaddingBottom((JanWidget *)this)
#define JanStack_SetPadding(this, padding) ((JanWidget *)this)->vtbl->SetPadding((JanWidget *)this, padding)
#define JanStack_SetPaddingTop(this, paddingTop) ((JanWidget *)this)->vtbl->SetPaddingTop((JanWidget *)this, paddingTop)
#define JanStack_SetPaddingLeft(this, paddingLeft) ((JanWidget *)this)->vtbl->SetPaddingLeft((JanWidget *)this, paddingLeft)
#define JanStack_SetPaddingRight(this, paddingRight) ((JanWidget *)this)->vtbl->SetPaddingRight((JanWidget *)this, paddingRight)
#define JanStack_SetPaddingBottom(this, paddingBottom) ((JanWidget *)this)->vtbl->SetPaddingBottom((JanWidget *)this, paddingBottom)
#define JanStack_GetMargin(this) ((JanWidget *)this)->vtbl->GetMargin((JanWidget *)this)
#define JanStack_GetMarginTop(this) ((JanWidget *)this)->vtbl->GetMarginTop((JanWidget *)this)
#define JanStack_GetMarginLeft(this) ((JanWidget *)this)->vtbl->GetMarginLeft((JanWidget *)this)
#define JanStack_GetMarginRight(this) ((JanWidget *)this)->vtbl->GetMarginRight((JanWidget *)this)
#define JanStack_GetMarginBottom(this) ((JanWidget *)this)->vtbl->GetMarginBottom((JanWidget *)this)
#define JanStack_SetMargin(this, margin) ((JanWidget *)this)->vtbl->SetMargin((JanWidget *)this, margin)
#define JanStack_SetMarginTop(this, marginTop) ((JanWidget *)this)->vtbl->SetMarginTop((JanWidget *)this, marginTop)
#define JanStack_SetMarginLeft(this, marginLeft) ((JanWidget *)this)->vtbl->SetMarginLeft((JanWidget *)this, marginLeft)
#define JanStack_SetMarginRight(this, marginRight) ((JanWidget *)this)->vtbl->SetMarginRight((JanWidget *)this, marginRight)
#define JanStack_SetMarginBottom(this, marginBottom) ((JanWidget *)this)->vtbl->SetMarginBottom((JanWidget *)this, marginBottom)
#define JanStack_GetBackgroundColor(this) ((JanWidget *)this)->vtbl->GetBackgroundColor((JanWidget *)this)
#define JanStack_SetBackgroundColor(this, backgroundColor) ((JanWidget *)this)->vtbl->SetBackgroundColor((JanWidget *)this, backgroundColor)
#define JanStack_GetVisible(this) ((JanWidget *)this)->vtbl->GetVisible((JanWidget *)this)
#define JanStack_SetVisible(this, visible) ((JanWidget *)this)->vtbl->SetVisible((JanWidget *)this, visible)
#define JanStack_GetChildren(this) ((JanContainer *)this)->vtbl->GetChildren((JanContainer *)this)
#define JanStack_ChildrenGet(this, index) ((JanContainer *)this)->vtbl->ChildrenGet((JanContainer *)this, index)
#define JanStack_ChildrenSet(this, index, item) ((JanContainer *)this)->vtbl->ChildrenSet((JanContainer *)this, index, item)
#define JanStack_ChildrenAdd(this, item) ((JanContainer *)this)->vtbl->ChildrenAdd((JanContainer *)this, item)
#define JanStack_ChildrenInsert(this, index, item) ((JanContainer *)this)->vtbl->ChildrenInsert((JanContainer *)this, index, item)
#define JanStack_ChildrenRemove(this, index) ((JanContainer *)this)->vtbl->ChildrenRemove((JanContainer *)this, index)
#define JanStack_ChildrenGetCapacity(this) ((JanContainer *)this)->vtbl->ChildrenGetCapacity((JanContainer *)this)
#define JanStack_ChildrenGetSize(this) ((JanContainer *)this)->vtbl->ChildrenGetSize((JanContainer *)this)

typedef struct JanBox JanBox;

typedef struct JanBoxVtbl {
    void (*Init)(JanBox *this, JanContext *context, JanOrientation orientation);
    void (*Free)(JanContainer *this);
    void (*Measure)(JanBox *this, float parentWidth, float parentHeight);
    void (*ConvertOffsets)(JanWidget *this, float parentWidth, float parentHeight);
    void (*Place)(JanBox *this, float x, float y);
    void (*Draw)(JanBox *this);
    JanContext *(*GetContext)(JanWidget *this);
    JanUnit (*GetWidth)(JanWidget *this);
    void (*SetWidth)(JanWidget *this, JanUnit width);
    JanUnit (*GetHeight)(JanWidget *this);
    void (*SetHeight)(JanWidget *this, JanUnit height);
    JanOffset *(*GetPadding)(JanWidget *this);
    JanUnit (*GetPaddingTop)(JanWidget *this);
    JanUnit (*GetPaddingLeft)(JanWidget *this);
    JanUnit (*GetPaddingRight)(JanWidget *this);
    JanUnit (*GetPaddingBottom)(JanWidget *this);
    void (*SetPadding)(JanWidget *this, JanOffset *padding);
    void (*SetPaddingTop)(JanWidget *this, JanUnit paddingTop);
    void (*SetPaddingLeft)(JanWidget *this, JanUnit paddingLeft);
    void (*SetPaddingRight)(JanWidget *this, JanUnit paddingRight);
    void (*SetPaddingBottom)(JanWidget *this, JanUnit paddingBottom);
    JanOffset *(*GetMargin)(JanWidget *this);
    JanUnit (*GetMarginTop)(JanWidget *this);
    JanUnit (*GetMarginLeft)(JanWidget *this);
    JanUnit (*GetMarginRight)(JanWidget *this);
    JanUnit (*GetMarginBottom)(JanWidget *this);
    void (*SetMargin)(JanWidget *this, JanOffset *margin);
    void (*SetMarginTop)(JanWidget *this, JanUnit marginTop);
    void (*SetMarginLeft)(JanWidget *this, JanUnit marginLeft);
    void (*SetMarginRight)(JanWidget *this, JanUnit marginRight);
    void (*SetMarginBottom)(JanWidget *this, JanUnit marginBottom);
    JanColor (*GetBackgroundColor)(JanWidget *this);
    void (*SetBackgroundColor)(JanWidget *this, JanColor backgroundColor);
    bool (*GetVisible)(JanWidget *this);
    void (*SetVisible)(JanWidget *this, bool visible);
    List *(*GetChildren)(JanContainer *this);
    Object *(*ChildrenGet)(JanContainer *this, uint32_t index);
    void (*ChildrenSet)(JanContainer *this, uint32_t index, Object *item);
    void (*ChildrenAdd)(JanContainer *this, Object *item);
    void (*ChildrenInsert)(JanContainer *this, uint32_t index, Object *item);
    void (*ChildrenRemove)(JanContainer *this, uint32_t index);
    uint32_t (*ChildrenGetCapacity)(JanContainer *this);
    uint32_t (*ChildrenGetSize)(JanContainer *this);
    JanOrientation (*GetOrientation)(JanBox *this);
    void (*SetOrientation)(JanBox *this, JanOrientation orientation);
} JanBoxVtbl;

extern JanBoxVtbl _JanBoxVtbl;

struct JanBox {
    const JanBoxVtbl *vtbl;
    JanContext *context;
    JanUnit width;
    JanUnit height;
    JanOffset padding;
    JanOffset margin;
    JanColor backgroundColor;
    bool visible;
    JanConvertedOffset convertedMargin;
    JanConvertedOffset convertedPadding;
    JanRect contentRect;
    JanRect paddingRect;
    JanRect marginRect;
    List *children;
    JanOrientation orientation;
};

extern JanBox *JanBox_New(JanContext *context, JanOrientation orientation);

#define JAN_BOX(janBox) ((JanBox *)janBox)
#define JanBox_Init(this, context, orientation) ((JanBox *)this)->vtbl->Init((JanBox *)this, context, orientation)
#define JanBox_Free(this) ((JanContainer *)this)->vtbl->Free((JanContainer *)this)
#define JanBox_Measure(this, parentWidth, parentHeight) ((JanBox *)this)->vtbl->Measure((JanBox *)this, parentWidth, parentHeight)
#define JanBox_ConvertOffsets(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->ConvertOffsets((JanWidget *)this, parentWidth, parentHeight)
#define JanBox_Place(this, x, y) ((JanBox *)this)->vtbl->Place((JanBox *)this, x, y)
#define JanBox_Draw(this) ((JanBox *)this)->vtbl->Draw((JanBox *)this)
#define JanBox_GetContext(this) ((JanWidget *)this)->vtbl->GetContext((JanWidget *)this)
#define JanBox_GetWidth(this) ((JanWidget *)this)->vtbl->GetWidth((JanWidget *)this)
#define JanBox_SetWidth(this, width) ((JanWidget *)this)->vtbl->SetWidth((JanWidget *)this, width)
#define JanBox_GetHeight(this) ((JanWidget *)this)->vtbl->GetHeight((JanWidget *)this)
#define JanBox_SetHeight(this, height) ((JanWidget *)this)->vtbl->SetHeight((JanWidget *)this, height)
#define JanBox_GetPadding(this) ((JanWidget *)this)->vtbl->GetPadding((JanWidget *)this)
#define JanBox_GetPaddingTop(this) ((JanWidget *)this)->vtbl->GetPaddingTop((JanWidget *)this)
#define JanBox_GetPaddingLeft(this) ((JanWidget *)this)->vtbl->GetPaddingLeft((JanWidget *)this)
#define JanBox_GetPaddingRight(this) ((JanWidget *)this)->vtbl->GetPaddingRight((JanWidget *)this)
#define JanBox_GetPaddingBottom(this) ((JanWidget *)this)->vtbl->GetPaddingBottom((JanWidget *)this)
#define JanBox_SetPadding(this, padding) ((JanWidget *)this)->vtbl->SetPadding((JanWidget *)this, padding)
#define JanBox_SetPaddingTop(this, paddingTop) ((JanWidget *)this)->vtbl->SetPaddingTop((JanWidget *)this, paddingTop)
#define JanBox_SetPaddingLeft(this, paddingLeft) ((JanWidget *)this)->vtbl->SetPaddingLeft((JanWidget *)this, paddingLeft)
#define JanBox_SetPaddingRight(this, paddingRight) ((JanWidget *)this)->vtbl->SetPaddingRight((JanWidget *)this, paddingRight)
#define JanBox_SetPaddingBottom(this, paddingBottom) ((JanWidget *)this)->vtbl->SetPaddingBottom((JanWidget *)this, paddingBottom)
#define JanBox_GetMargin(this) ((JanWidget *)this)->vtbl->GetMargin((JanWidget *)this)
#define JanBox_GetMarginTop(this) ((JanWidget *)this)->vtbl->GetMarginTop((JanWidget *)this)
#define JanBox_GetMarginLeft(this) ((JanWidget *)this)->vtbl->GetMarginLeft((JanWidget *)this)
#define JanBox_GetMarginRight(this) ((JanWidget *)this)->vtbl->GetMarginRight((JanWidget *)this)
#define JanBox_GetMarginBottom(this) ((JanWidget *)this)->vtbl->GetMarginBottom((JanWidget *)this)
#define JanBox_SetMargin(this, margin) ((JanWidget *)this)->vtbl->SetMargin((JanWidget *)this, margin)
#define JanBox_SetMarginTop(this, marginTop) ((JanWidget *)this)->vtbl->SetMarginTop((JanWidget *)this, marginTop)
#define JanBox_SetMarginLeft(this, marginLeft) ((JanWidget *)this)->vtbl->SetMarginLeft((JanWidget *)this, marginLeft)
#define JanBox_SetMarginRight(this, marginRight) ((JanWidget *)this)->vtbl->SetMarginRight((JanWidget *)this, marginRight)
#define JanBox_SetMarginBottom(this, marginBottom) ((JanWidget *)this)->vtbl->SetMarginBottom((JanWidget *)this, marginBottom)
#define JanBox_GetBackgroundColor(this) ((JanWidget *)this)->vtbl->GetBackgroundColor((JanWidget *)this)
#define JanBox_SetBackgroundColor(this, backgroundColor) ((JanWidget *)this)->vtbl->SetBackgroundColor((JanWidget *)this, backgroundColor)
#define JanBox_GetVisible(this) ((JanWidget *)this)->vtbl->GetVisible((JanWidget *)this)
#define JanBox_SetVisible(this, visible) ((JanWidget *)this)->vtbl->SetVisible((JanWidget *)this, visible)
#define JanBox_GetChildren(this) ((JanContainer *)this)->vtbl->GetChildren((JanContainer *)this)
#define JanBox_ChildrenGet(this, index) ((JanContainer *)this)->vtbl->ChildrenGet((JanContainer *)this, index)
#define JanBox_ChildrenSet(this, index, item) ((JanContainer *)this)->vtbl->ChildrenSet((JanContainer *)this, index, item)
#define JanBox_ChildrenAdd(this, item) ((JanContainer *)this)->vtbl->ChildrenAdd((JanContainer *)this, item)
#define JanBox_ChildrenInsert(this, index, item) ((JanContainer *)this)->vtbl->ChildrenInsert((JanContainer *)this, index, item)
#define JanBox_ChildrenRemove(this, index) ((JanContainer *)this)->vtbl->ChildrenRemove((JanContainer *)this, index)
#define JanBox_ChildrenGetCapacity(this) ((JanContainer *)this)->vtbl->ChildrenGetCapacity((JanContainer *)this)
#define JanBox_ChildrenGetSize(this) ((JanContainer *)this)->vtbl->ChildrenGetSize((JanContainer *)this)
#define JanBox_GetOrientation(this) ((JanBox *)this)->vtbl->GetOrientation((JanBox *)this)
#define JanBox_SetOrientation(this, orientation) ((JanBox *)this)->vtbl->SetOrientation((JanBox *)this, orientation)

typedef struct JanLabel JanLabel;

typedef struct JanLabelVtbl {
    void (*Init)(JanLabel *this, JanContext *context, wchar_t *text);
    void (*Free)(JanLabel *this);
    void (*Measure)(JanLabel *this, float parentWidth, float parentHeight);
    void (*ConvertOffsets)(JanWidget *this, float parentWidth, float parentHeight);
    void (*Place)(JanWidget *this, float x, float y);
    void (*Draw)(JanLabel *this);
    JanContext *(*GetContext)(JanWidget *this);
    JanUnit (*GetWidth)(JanWidget *this);
    void (*SetWidth)(JanWidget *this, JanUnit width);
    JanUnit (*GetHeight)(JanWidget *this);
    void (*SetHeight)(JanWidget *this, JanUnit height);
    JanOffset *(*GetPadding)(JanWidget *this);
    JanUnit (*GetPaddingTop)(JanWidget *this);
    JanUnit (*GetPaddingLeft)(JanWidget *this);
    JanUnit (*GetPaddingRight)(JanWidget *this);
    JanUnit (*GetPaddingBottom)(JanWidget *this);
    void (*SetPadding)(JanWidget *this, JanOffset *padding);
    void (*SetPaddingTop)(JanWidget *this, JanUnit paddingTop);
    void (*SetPaddingLeft)(JanWidget *this, JanUnit paddingLeft);
    void (*SetPaddingRight)(JanWidget *this, JanUnit paddingRight);
    void (*SetPaddingBottom)(JanWidget *this, JanUnit paddingBottom);
    JanOffset *(*GetMargin)(JanWidget *this);
    JanUnit (*GetMarginTop)(JanWidget *this);
    JanUnit (*GetMarginLeft)(JanWidget *this);
    JanUnit (*GetMarginRight)(JanWidget *this);
    JanUnit (*GetMarginBottom)(JanWidget *this);
    void (*SetMargin)(JanWidget *this, JanOffset *margin);
    void (*SetMarginTop)(JanWidget *this, JanUnit marginTop);
    void (*SetMarginLeft)(JanWidget *this, JanUnit marginLeft);
    void (*SetMarginRight)(JanWidget *this, JanUnit marginRight);
    void (*SetMarginBottom)(JanWidget *this, JanUnit marginBottom);
    JanColor (*GetBackgroundColor)(JanWidget *this);
    void (*SetBackgroundColor)(JanWidget *this, JanColor backgroundColor);
    bool (*GetVisible)(JanWidget *this);
    void (*SetVisible)(JanWidget *this, bool visible);
    wchar_t *(*GetText)(JanLabel *this);
    void (*SetText)(JanLabel *this, wchar_t *text);
    JanFont *(*GetFont)(JanLabel *this);
    void (*SetFont)(JanLabel *this, JanFont *font);
    JanColor (*GetTextColor)(JanLabel *this);
    void (*SetTextColor)(JanLabel *this, JanColor textColor);
    bool (*GetSingleLine)(JanLabel *this);
    void (*SetSingleLine)(JanLabel *this, bool singleLine);
} JanLabelVtbl;

extern JanLabelVtbl _JanLabelVtbl;

struct JanLabel {
    const JanLabelVtbl *vtbl;
    JanContext *context;
    JanUnit width;
    JanUnit height;
    JanOffset padding;
    JanOffset margin;
    JanColor backgroundColor;
    bool visible;
    JanConvertedOffset convertedMargin;
    JanConvertedOffset convertedPadding;
    JanRect contentRect;
    JanRect paddingRect;
    JanRect marginRect;
    wchar_t *text;
    JanFont *font;
    JanColor textColor;
    bool singleLine;
};

extern JanLabel *JanLabel_New(JanContext *context, wchar_t *text);

#define JAN_LABEL(janLabel) ((JanLabel *)janLabel)
#define JanLabel_Init(this, context, text) ((JanLabel *)this)->vtbl->Init((JanLabel *)this, context, text)
#define JanLabel_Free(this) ((JanLabel *)this)->vtbl->Free((JanLabel *)this)
#define JanLabel_Measure(this, parentWidth, parentHeight) ((JanLabel *)this)->vtbl->Measure((JanLabel *)this, parentWidth, parentHeight)
#define JanLabel_ConvertOffsets(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->ConvertOffsets((JanWidget *)this, parentWidth, parentHeight)
#define JanLabel_Place(this, x, y) ((JanWidget *)this)->vtbl->Place((JanWidget *)this, x, y)
#define JanLabel_Draw(this) ((JanLabel *)this)->vtbl->Draw((JanLabel *)this)
#define JanLabel_GetContext(this) ((JanWidget *)this)->vtbl->GetContext((JanWidget *)this)
#define JanLabel_GetWidth(this) ((JanWidget *)this)->vtbl->GetWidth((JanWidget *)this)
#define JanLabel_SetWidth(this, width) ((JanWidget *)this)->vtbl->SetWidth((JanWidget *)this, width)
#define JanLabel_GetHeight(this) ((JanWidget *)this)->vtbl->GetHeight((JanWidget *)this)
#define JanLabel_SetHeight(this, height) ((JanWidget *)this)->vtbl->SetHeight((JanWidget *)this, height)
#define JanLabel_GetPadding(this) ((JanWidget *)this)->vtbl->GetPadding((JanWidget *)this)
#define JanLabel_GetPaddingTop(this) ((JanWidget *)this)->vtbl->GetPaddingTop((JanWidget *)this)
#define JanLabel_GetPaddingLeft(this) ((JanWidget *)this)->vtbl->GetPaddingLeft((JanWidget *)this)
#define JanLabel_GetPaddingRight(this) ((JanWidget *)this)->vtbl->GetPaddingRight((JanWidget *)this)
#define JanLabel_GetPaddingBottom(this) ((JanWidget *)this)->vtbl->GetPaddingBottom((JanWidget *)this)
#define JanLabel_SetPadding(this, padding) ((JanWidget *)this)->vtbl->SetPadding((JanWidget *)this, padding)
#define JanLabel_SetPaddingTop(this, paddingTop) ((JanWidget *)this)->vtbl->SetPaddingTop((JanWidget *)this, paddingTop)
#define JanLabel_SetPaddingLeft(this, paddingLeft) ((JanWidget *)this)->vtbl->SetPaddingLeft((JanWidget *)this, paddingLeft)
#define JanLabel_SetPaddingRight(this, paddingRight) ((JanWidget *)this)->vtbl->SetPaddingRight((JanWidget *)this, paddingRight)
#define JanLabel_SetPaddingBottom(this, paddingBottom) ((JanWidget *)this)->vtbl->SetPaddingBottom((JanWidget *)this, paddingBottom)
#define JanLabel_GetMargin(this) ((JanWidget *)this)->vtbl->GetMargin((JanWidget *)this)
#define JanLabel_GetMarginTop(this) ((JanWidget *)this)->vtbl->GetMarginTop((JanWidget *)this)
#define JanLabel_GetMarginLeft(this) ((JanWidget *)this)->vtbl->GetMarginLeft((JanWidget *)this)
#define JanLabel_GetMarginRight(this) ((JanWidget *)this)->vtbl->GetMarginRight((JanWidget *)this)
#define JanLabel_GetMarginBottom(this) ((JanWidget *)this)->vtbl->GetMarginBottom((JanWidget *)this)
#define JanLabel_SetMargin(this, margin) ((JanWidget *)this)->vtbl->SetMargin((JanWidget *)this, margin)
#define JanLabel_SetMarginTop(this, marginTop) ((JanWidget *)this)->vtbl->SetMarginTop((JanWidget *)this, marginTop)
#define JanLabel_SetMarginLeft(this, marginLeft) ((JanWidget *)this)->vtbl->SetMarginLeft((JanWidget *)this, marginLeft)
#define JanLabel_SetMarginRight(this, marginRight) ((JanWidget *)this)->vtbl->SetMarginRight((JanWidget *)this, marginRight)
#define JanLabel_SetMarginBottom(this, marginBottom) ((JanWidget *)this)->vtbl->SetMarginBottom((JanWidget *)this, marginBottom)
#define JanLabel_GetBackgroundColor(this) ((JanWidget *)this)->vtbl->GetBackgroundColor((JanWidget *)this)
#define JanLabel_SetBackgroundColor(this, backgroundColor) ((JanWidget *)this)->vtbl->SetBackgroundColor((JanWidget *)this, backgroundColor)
#define JanLabel_GetVisible(this) ((JanWidget *)this)->vtbl->GetVisible((JanWidget *)this)
#define JanLabel_SetVisible(this, visible) ((JanWidget *)this)->vtbl->SetVisible((JanWidget *)this, visible)
#define JanLabel_GetText(this) ((JanLabel *)this)->vtbl->GetText((JanLabel *)this)
#define JanLabel_SetText(this, text) ((JanLabel *)this)->vtbl->SetText((JanLabel *)this, text)
#define JanLabel_GetFont(this) ((JanLabel *)this)->vtbl->GetFont((JanLabel *)this)
#define JanLabel_SetFont(this, font) ((JanLabel *)this)->vtbl->SetFont((JanLabel *)this, font)
#define JanLabel_GetTextColor(this) ((JanLabel *)this)->vtbl->GetTextColor((JanLabel *)this)
#define JanLabel_SetTextColor(this, textColor) ((JanLabel *)this)->vtbl->SetTextColor((JanLabel *)this, textColor)
#define JanLabel_GetSingleLine(this) ((JanLabel *)this)->vtbl->GetSingleLine((JanLabel *)this)
#define JanLabel_SetSingleLine(this, singleLine) ((JanLabel *)this)->vtbl->SetSingleLine((JanLabel *)this, singleLine)

typedef struct JanButton JanButton;

typedef struct JanButtonVtbl {
    void (*Init)(JanButton *this, JanContext *context, wchar_t *text);
    void (*Free)(JanLabel *this);
    void (*Measure)(JanLabel *this, float parentWidth, float parentHeight);
    void (*ConvertOffsets)(JanWidget *this, float parentWidth, float parentHeight);
    void (*Place)(JanWidget *this, float x, float y);
    void (*Draw)(JanLabel *this);
    JanContext *(*GetContext)(JanWidget *this);
    JanUnit (*GetWidth)(JanWidget *this);
    void (*SetWidth)(JanWidget *this, JanUnit width);
    JanUnit (*GetHeight)(JanWidget *this);
    void (*SetHeight)(JanWidget *this, JanUnit height);
    JanOffset *(*GetPadding)(JanWidget *this);
    JanUnit (*GetPaddingTop)(JanWidget *this);
    JanUnit (*GetPaddingLeft)(JanWidget *this);
    JanUnit (*GetPaddingRight)(JanWidget *this);
    JanUnit (*GetPaddingBottom)(JanWidget *this);
    void (*SetPadding)(JanWidget *this, JanOffset *padding);
    void (*SetPaddingTop)(JanWidget *this, JanUnit paddingTop);
    void (*SetPaddingLeft)(JanWidget *this, JanUnit paddingLeft);
    void (*SetPaddingRight)(JanWidget *this, JanUnit paddingRight);
    void (*SetPaddingBottom)(JanWidget *this, JanUnit paddingBottom);
    JanOffset *(*GetMargin)(JanWidget *this);
    JanUnit (*GetMarginTop)(JanWidget *this);
    JanUnit (*GetMarginLeft)(JanWidget *this);
    JanUnit (*GetMarginRight)(JanWidget *this);
    JanUnit (*GetMarginBottom)(JanWidget *this);
    void (*SetMargin)(JanWidget *this, JanOffset *margin);
    void (*SetMarginTop)(JanWidget *this, JanUnit marginTop);
    void (*SetMarginLeft)(JanWidget *this, JanUnit marginLeft);
    void (*SetMarginRight)(JanWidget *this, JanUnit marginRight);
    void (*SetMarginBottom)(JanWidget *this, JanUnit marginBottom);
    JanColor (*GetBackgroundColor)(JanWidget *this);
    void (*SetBackgroundColor)(JanWidget *this, JanColor backgroundColor);
    bool (*GetVisible)(JanWidget *this);
    void (*SetVisible)(JanWidget *this, bool visible);
    wchar_t *(*GetText)(JanLabel *this);
    void (*SetText)(JanLabel *this, wchar_t *text);
    JanFont *(*GetFont)(JanLabel *this);
    void (*SetFont)(JanLabel *this, JanFont *font);
    JanColor (*GetTextColor)(JanLabel *this);
    void (*SetTextColor)(JanLabel *this, JanColor textColor);
    bool (*GetSingleLine)(JanLabel *this);
    void (*SetSingleLine)(JanLabel *this, bool singleLine);
} JanButtonVtbl;

extern JanButtonVtbl _JanButtonVtbl;

struct JanButton {
    const JanButtonVtbl *vtbl;
    JanContext *context;
    JanUnit width;
    JanUnit height;
    JanOffset padding;
    JanOffset margin;
    JanColor backgroundColor;
    bool visible;
    JanConvertedOffset convertedMargin;
    JanConvertedOffset convertedPadding;
    JanRect contentRect;
    JanRect paddingRect;
    JanRect marginRect;
    wchar_t *text;
    JanFont *font;
    JanColor textColor;
    bool singleLine;
};

extern JanButton *JanButton_New(JanContext *context, wchar_t *text);

#define JAN_BUTTON(janButton) ((JanButton *)janButton)
#define JanButton_Init(this, context, text) ((JanButton *)this)->vtbl->Init((JanButton *)this, context, text)
#define JanButton_Free(this) ((JanLabel *)this)->vtbl->Free((JanLabel *)this)
#define JanButton_Measure(this, parentWidth, parentHeight) ((JanLabel *)this)->vtbl->Measure((JanLabel *)this, parentWidth, parentHeight)
#define JanButton_ConvertOffsets(this, parentWidth, parentHeight) ((JanWidget *)this)->vtbl->ConvertOffsets((JanWidget *)this, parentWidth, parentHeight)
#define JanButton_Place(this, x, y) ((JanWidget *)this)->vtbl->Place((JanWidget *)this, x, y)
#define JanButton_Draw(this) ((JanLabel *)this)->vtbl->Draw((JanLabel *)this)
#define JanButton_GetContext(this) ((JanWidget *)this)->vtbl->GetContext((JanWidget *)this)
#define JanButton_GetWidth(this) ((JanWidget *)this)->vtbl->GetWidth((JanWidget *)this)
#define JanButton_SetWidth(this, width) ((JanWidget *)this)->vtbl->SetWidth((JanWidget *)this, width)
#define JanButton_GetHeight(this) ((JanWidget *)this)->vtbl->GetHeight((JanWidget *)this)
#define JanButton_SetHeight(this, height) ((JanWidget *)this)->vtbl->SetHeight((JanWidget *)this, height)
#define JanButton_GetPadding(this) ((JanWidget *)this)->vtbl->GetPadding((JanWidget *)this)
#define JanButton_GetPaddingTop(this) ((JanWidget *)this)->vtbl->GetPaddingTop((JanWidget *)this)
#define JanButton_GetPaddingLeft(this) ((JanWidget *)this)->vtbl->GetPaddingLeft((JanWidget *)this)
#define JanButton_GetPaddingRight(this) ((JanWidget *)this)->vtbl->GetPaddingRight((JanWidget *)this)
#define JanButton_GetPaddingBottom(this) ((JanWidget *)this)->vtbl->GetPaddingBottom((JanWidget *)this)
#define JanButton_SetPadding(this, padding) ((JanWidget *)this)->vtbl->SetPadding((JanWidget *)this, padding)
#define JanButton_SetPaddingTop(this, paddingTop) ((JanWidget *)this)->vtbl->SetPaddingTop((JanWidget *)this, paddingTop)
#define JanButton_SetPaddingLeft(this, paddingLeft) ((JanWidget *)this)->vtbl->SetPaddingLeft((JanWidget *)this, paddingLeft)
#define JanButton_SetPaddingRight(this, paddingRight) ((JanWidget *)this)->vtbl->SetPaddingRight((JanWidget *)this, paddingRight)
#define JanButton_SetPaddingBottom(this, paddingBottom) ((JanWidget *)this)->vtbl->SetPaddingBottom((JanWidget *)this, paddingBottom)
#define JanButton_GetMargin(this) ((JanWidget *)this)->vtbl->GetMargin((JanWidget *)this)
#define JanButton_GetMarginTop(this) ((JanWidget *)this)->vtbl->GetMarginTop((JanWidget *)this)
#define JanButton_GetMarginLeft(this) ((JanWidget *)this)->vtbl->GetMarginLeft((JanWidget *)this)
#define JanButton_GetMarginRight(this) ((JanWidget *)this)->vtbl->GetMarginRight((JanWidget *)this)
#define JanButton_GetMarginBottom(this) ((JanWidget *)this)->vtbl->GetMarginBottom((JanWidget *)this)
#define JanButton_SetMargin(this, margin) ((JanWidget *)this)->vtbl->SetMargin((JanWidget *)this, margin)
#define JanButton_SetMarginTop(this, marginTop) ((JanWidget *)this)->vtbl->SetMarginTop((JanWidget *)this, marginTop)
#define JanButton_SetMarginLeft(this, marginLeft) ((JanWidget *)this)->vtbl->SetMarginLeft((JanWidget *)this, marginLeft)
#define JanButton_SetMarginRight(this, marginRight) ((JanWidget *)this)->vtbl->SetMarginRight((JanWidget *)this, marginRight)
#define JanButton_SetMarginBottom(this, marginBottom) ((JanWidget *)this)->vtbl->SetMarginBottom((JanWidget *)this, marginBottom)
#define JanButton_GetBackgroundColor(this) ((JanWidget *)this)->vtbl->GetBackgroundColor((JanWidget *)this)
#define JanButton_SetBackgroundColor(this, backgroundColor) ((JanWidget *)this)->vtbl->SetBackgroundColor((JanWidget *)this, backgroundColor)
#define JanButton_GetVisible(this) ((JanWidget *)this)->vtbl->GetVisible((JanWidget *)this)
#define JanButton_SetVisible(this, visible) ((JanWidget *)this)->vtbl->SetVisible((JanWidget *)this, visible)
#define JanButton_GetText(this) ((JanLabel *)this)->vtbl->GetText((JanLabel *)this)
#define JanButton_SetText(this, text) ((JanLabel *)this)->vtbl->SetText((JanLabel *)this, text)
#define JanButton_GetFont(this) ((JanLabel *)this)->vtbl->GetFont((JanLabel *)this)
#define JanButton_SetFont(this, font) ((JanLabel *)this)->vtbl->SetFont((JanLabel *)this, font)
#define JanButton_GetTextColor(this) ((JanLabel *)this)->vtbl->GetTextColor((JanLabel *)this)
#define JanButton_SetTextColor(this, textColor) ((JanLabel *)this)->vtbl->SetTextColor((JanLabel *)this, textColor)
#define JanButton_GetSingleLine(this) ((JanLabel *)this)->vtbl->GetSingleLine((JanLabel *)this)
#define JanButton_SetSingleLine(this, singleLine) ((JanLabel *)this)->vtbl->SetSingleLine((JanLabel *)this, singleLine)

#endif
