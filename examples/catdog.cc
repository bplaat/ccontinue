// Run: ../ccc.py catdog.cc && gcc --std=c11 -Wall -Wextra -Wpedantic -Werror catdog.c -o catdog.exe && ./catdog.exe

// Animal
abstract class Animal {
    @init(strdup) @free @get char *name;
    virtual void jump();
}

// Cat
class Cat extends Animal {
    @init int32_t lives;
    virtual void jump();
}

void Cat::jump() { printf("Cat %s jumps, it has %d lives left!\n", this->name, this->lives); }

// Dog
class Dog extends Animal {
    virtual void jump();
}

void Dog::jump() { printf("Dog %s jumps!\n", this->name); }

// Main
int main(void) {
    List *animals = list_new();
    list_add(animals, cat_new("Mew", 6));
    list_add(animals, dog_new("Woof"));
    list_add(animals, cat_new("Mew 2.0", 9));
    list_add(animals, dog_new("Doggie"));

    for (size_t i = 0; i < list_get_size(animals); i++) {
        Animal *animal = (Animal *)list_get(animals, i);
        animal_jump(animal);
    }

    list_free(animals);
    return EXIT_SUCCESS;
}
