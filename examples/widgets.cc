// Context
class Context {
}

// Widget
class Widget {
    @get @init Context *context;
    @prop bool visible = true;

    virtual void draw();
}

void Widget::draw() {
    (void)this;
}

// Container
class Container extends Widget {
    @get @free(list_free) List *children = list_new();

    void add(Widget *widget);
}

void Container::add(Widget *widget) {
    list_add(this->children, widget);
}

// Orientation
typedef enum Orientation { ORIENTATION_HORIZONTAL, ORIENTATION_VERTICAL } Orientation;

// Box
class Box extends Container {
    @prop @init Orientation orientation;
}

// Label
class Label extends Widget {
    @prop @init @free(string_free) String *text;
}

// Main
int main(void) {
    Context *context = context_new();

    Box *box = box_new(context, ORIENTATION_VERTICAL);
    box_add(box, label_new(context, string_new("Line 1")));
    box_add(box, label_new(context, string_new("Line 2")));
    box_add(box, label_new(context, string_new("Line 3")));
    box_free(box);

    context_free(context);
    return EXIT_SUCCESS;
}
