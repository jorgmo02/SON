#include <iostream>
#include <ctime>
#include <chrono>
#include "fmod.hpp"
#include "macros.h"
#include "InputHandler.h"
#include "Motor.h"
#include "Battle.h"

#pragma region ENGINE
int init(FMOD::System** system) {

	FMOD_RESULT result;
	result = System_Create(system); // Creamos el objeto system
	ERRCHECK(result);

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	result = (*system)->init(128, FMOD_INIT_NORMAL, 0); // Inicializacion de FMOD
	ERRCHECK(result);

	return 0;
}

int free(FMOD::System* system) {
	FMOD_RESULT result;
	result = system->release();
	ERRCHECK(result);

	return 0;
}
#pragma endregion ENGINE

// AMBIENT SOUND
void battle(FMOD::System* system)
{
	FMOD_RESULT result;

	FMOD::Sound* sound1;
	result = system->createSound(
		PATH("Battle.wav"), // path al archivo de sonido
		FMOD_LOOP_NORMAL | FMOD_2D, // valores (loop, 2D)
		0,			// informacion adicional (nada en este caso)
		&sound1);	// handle al buffer de sonido
	ERRCHECK(result);

	FMOD::Channel* channel;
	result = system->playSound(
		sound1,		// buffer que se "engancha" a ese canal
		0,			// grupo de canales, 0 sin agrupar (agrupado en el master)
		false,		// arranca sin "pause" (se reproduce directamente)
		&channel);	// devuelve el canal que asigna
	// el sonido ya se esta reproduciendo
	ERRCHECK(result);

	result = channel->setVolume(0.7f);
	ERRCHECK(result);

	result = system->update();
	ERRCHECK(result);
}

int main()
{
	srand(time(NULL));

	FMOD::System* system = nullptr;
	init(&system);

	std::vector<SoundEntity*> entities;

	Motor motor(system);
	motor.play();
	entities.push_back(&motor);
	
	Battle battle(system);
	battle.play();
	entities.push_back(&battle);

	auto lastUpdate = std::chrono::system_clock::now();

	while (!InputHandler::Exit)
	{
		auto newUpdate = std::chrono::system_clock::now();
		std::chrono::duration<float, std::milli> diff = newUpdate - lastUpdate;
		lastUpdate = newUpdate;

		float deltaTime = diff.count();
		for (SoundEntity* entity : entities) {
			entity->update(deltaTime);
		}
		InputHandler::Update();
		ERRCHECK(system->update());
	}

	free(system);
}