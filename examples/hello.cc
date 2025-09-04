#include <List.hh>

class Person {
    @get @init(strdup) @free char* name;
    @prop @init i32 age;

    void greet();
};

void Person::greet() {
    printf("Hello %s, you are %d years old!\n", this->name, this->age);
}

int main(void) {
    // Simple class instance
    Person* bastiaan = person_new("Bastiaan", 21);
    person_set_age(bastiaan, person_get_age(bastiaan) + 1);
    person_greet(bastiaan);
    person_free(bastiaan);

    // Build in dynamic lists
    List* persons = list_new();
    list_add(persons, person_new("Bastiaan", 21));
    list_add(persons, person_new("Sander", 20));
    list_add(persons, person_new("Leonard", 17));
    list_add(persons, person_new("Jiska", 16));

    for (usize i = 0; i < list_get_size(persons); i++) {
        Person* person = (Person*)list_get(persons, i);
        person_greet(person);
    }

    List* persons_copy = list_ref(persons);
    list_free(persons_copy);

    list_free(persons);
    return EXIT_SUCCESS;
}
