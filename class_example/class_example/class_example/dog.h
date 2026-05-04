#pragma once
#include "animal.h"
class dog
	: public animal
{
public:
	void make_sound() override;
	void make_sound_non_override();
};

