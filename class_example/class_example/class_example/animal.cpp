#include "animal.h"
#include <iostream>

void animal::make_sound() {
	super_animal::make_sound();
	std::cout << "Animal makes sound\n";
}
