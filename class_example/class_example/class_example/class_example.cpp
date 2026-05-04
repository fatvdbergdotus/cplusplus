#include <iostream>
#include "animal.h"
#include "dog.h"


int main()
{
    super_animal sa;
    sa.make_sound();

    std::cout << "\n\n";

    animal a;
    a.make_sound();
    a.make_sound_non_override();

    std::cout << "\n\n";

    dog dog;
    dog.make_sound();
    dog.make_sound_non_override();

}

