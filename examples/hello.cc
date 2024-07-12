class Person {
    @get @init(strdup) @free(free) char* name;
    @prop @init int32_t age;

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

    for (size_t i = 0; i < list_get_size(persons); i++) {
        Person* person = (Person*)list_get(persons, i);
        person_greet(person);
    }

    list_free(persons);
    return EXIT_SUCCESS;
}
