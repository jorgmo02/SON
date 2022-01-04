#pragma once
#include "SoundEntity.h"
#include <iostream>

class Battle : public SoundEntity
{
private:
	FMOD::Sound* sound = nullptr;
	FMOD::Channel* channel = nullptr;
	float shootRate = 1000.0f;

	void shoot();

public:
	Battle(FMOD::System* system) :
		SoundEntity(system)
	{
		ERRCHECK(
			system->createSound(
				PATH("Battle.wav"),
				FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound)
			);
	}

	void play()
	{
		ERRCHECK(system->playSound(sound, 0, false, &channel));
		ERRCHECK(channel->setVolume(0.7f));
		ERRCHECK(system->update());
	}

	void update(float deltaTime) override
	{
		int totalRate = shootRate / deltaTime;
		if (rand() % totalRate == 0) {
			shoot();
		}
	}
};