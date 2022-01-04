#pragma once
#include "fmod.hpp"
#include "macros.h"
#include "InputListener.h"

class SoundEntity : public InputListener
{
protected:
	FMOD::System* system;

	SoundEntity(FMOD::System* system) : system(system)
	{
	}

public:

	virtual void update(float deltaTime) {};
};