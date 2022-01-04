#pragma once
#include "SoundEntity.h"

class Motor : public SoundEntity
{
private:
	FMOD::Sound* sound = nullptr;
	FMOD::Channel* channel = nullptr;
	float pitchIncreaseRate = 100.0f;

public:
	Motor(FMOD::System* system) :
		SoundEntity(system)
	{
		ERRCHECK(
			system->createSound(
				PATH("motor.wav"),
				FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound)
			);
	}

	void play()
	{
		ERRCHECK(system->playSound(sound, 0, false, &channel));
		ERRCHECK(channel->setVolume(0.7f));
		ERRCHECK(system->update());
	}

	void process(char key)
	{
		int dir = 0;

		switch (key)
		{
		case KEY_UP:
			dir = 1;
			break;
		case KEY_DOWN:
			dir = -1;
			break;
		case KEY_LEFT:
			break;
		case KEY_RIGHT:
			break;

		default:
			break;
		}

		float currpitch;
		ERRCHECK(channel->getPitch(&currpitch));
		currpitch += pitchIncreaseRate * dir;
		ERRCHECK(channel->setPitch(currpitch));
	}
};