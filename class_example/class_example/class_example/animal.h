#pragma once
#include "super_animal.h"
class animal :
    public super_animal
{
public:
    virtual void make_sound() override;
    void make_sound_non_override();
};

