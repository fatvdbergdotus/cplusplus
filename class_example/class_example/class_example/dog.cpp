#include "dog.h"
#include <iostream>

void dog::make_sound() {
	animal::make_sound();
	std::cout << "Dog makes sound\n";
}

void dog::make_sound_non_override() {
	std::cout << "Dog makes sound (non-override)\n";
}