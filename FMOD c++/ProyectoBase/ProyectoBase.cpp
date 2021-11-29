#include <iostream>
#include "fmod.hpp"
#include "fmod_errors.h"

using namespace FMOD;

// para salidas de error
void ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		// printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

int init(System* system) {

	FMOD_RESULT result;

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	result = system->init(128, FMOD_INIT_NORMAL, 0); // Inicializacion de FMOD
	ERRCHECK(result);

	return 0;
}

int exit(System* system) {
	FMOD_RESULT result;
	result = system->release();
	ERRCHECK(result);

	return 0;
}

int main()
{
	System* system;
	FMOD_RESULT result;
	result = System_Create(&system); // Creamos el objeto system
	ERRCHECK(result);
	init(system);

	FMOD::Sound* sound1;
	result = system->createSound(
		"muestras\\Battle.wav", // path al archivo de sonido
		FMOD_DEFAULT | FMOD_LOOP_NORMAL | FMOD_3D, // valores (por defecto en este caso: sin loop, 2D)
		0, // informacion adicional (nada en este caso)
		&sound1); // handle al buffer de sonido
	ERRCHECK(result);

	Channel* channel;
	result = system->playSound(
		sound1, // buffer que se "engancha" a ese canal
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		false, // arranca sin "pause" (se reproduce directamente)
		&channel); // devuelve el canal que asigna
	// el sonido ya se esta reproduciendo
	ERRCHECK(result);



	result = system->update();
	ERRCHECK(result);
	
	result = channel->setVolume(0.7f);
	ERRCHECK(result);
	
	while (true);

	exit(system);
}