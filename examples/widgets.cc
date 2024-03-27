// Run: ../ccc.py widgets.cc && gcc --std=c11 -Wall -Wextra -Wpedantic -Werror widgets.c -o widgets.exe && ./widgets.exe

// Context
class Context {}

// Widget
class Widget {
    @get @init Context *context;
    @prop bool visible = true;

    virtual void draw();
}

void Widget::draw() { (void)this; }

// Container
class Container extends Widget {
    @get @free(list_free) List *children = list_new();

    void add(Widget *widget);
}

void Container::add(Widget *widget) { list_add(this->children, widget); }

// Orientation
typedef enum Orientation { ORIENTATION_HORIZONTAL, ORIENTATION_VERTICAL } Orientation;

// Box
class Box extends Container {
    @prop @init Orientation orientation;
}

// Label
class Label extends Widget {
    @prop @init(strdup) @free char *text;
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
