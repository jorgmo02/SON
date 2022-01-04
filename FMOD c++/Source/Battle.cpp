#include "Battle.h"

// POSITIONAL 3D RANDOM SOUND
void Battle::shoot()
{
	FMOD_RESULT result;

	std::string shootSound =
		((rand() & 1)
			? "Gun1.wav"
			: "Gun2.wav"
			);

	FMOD::Sound* sound;
	result = system->createSound(
		PATH(shootSound),
		FMOD_LOOP_OFF | FMOD_3D,
		0, &sound);
	ERRCHECK(result);

	FMOD::Channel* channel;
	result = system->playSound(sound, 0, false, &channel);
	ERRCHECK(result);

	int radius = 10;
	FMOD_VECTOR pos{ (rand() % radius) - radius / 2, (rand() % radius) - radius / 2, (rand() % 10) - radius / 2 };
	FMOD_VECTOR vel{ 0,0,0 };
	result = channel->set3DAttributes(&pos, &vel);
	ERRCHECK(result);

	ERRCHECK(system->update());
}