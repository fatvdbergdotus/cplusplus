#include "animal.h"
#include <iostream>

void animal::make_sound() {
	super_animal::make_sound();
	std::cout << "Animal makes sound\n";
}

void animal::make_sound_non_override() {
	std::cout << "Animal makes sound (non-override)\n";
}
