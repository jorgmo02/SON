#include <iostream>
#include <cctype>
#include "fmod.hpp"
#include "fmod_errors.h"

using namespace FMOD;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string slash = "\\";
#include <conio.h>
char getinput() { return _getch(); }

#elif defined(unix) || defined(__unix) || defined(__unix__)
static const std::string slash = "/";

#include <unistd.h>
#include <termios.h>

char getinput() {
	char buf = 0;
	struct termios old = { 0 };
	if (tcgetattr(0, &old) < 0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
		perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror("tcsetattr ~ICANON");
	return (buf);
}

#endif

static const std::string path = "." + slash + "Assets" + slash;

#define PATH(filename) (path + filename).c_str()

// para salidas de error
void ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		// printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

int init(System** system) {

	FMOD_RESULT result;
	result = System_Create(system); // Creamos el objeto system
	ERRCHECK(result);

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	result = (*system)->init(128, FMOD_INIT_NORMAL, 0); // Inicializacion de FMOD
	ERRCHECK(result);

	return 0;
}

int free(System* system) {
	FMOD_RESULT result;
	result = system->release();
	ERRCHECK(result);

	return 0;
}

void battle(System* system)
{
	FMOD_RESULT result;

	FMOD::Sound* sound1;
	result = system->createSound(
		PATH("Battle.wav"), // path al archivo de sonido
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

	result = channel->setVolume(0.7f);
	ERRCHECK(result);

	result = system->update();
	ERRCHECK(result);
}

int main()
{
	System* system = nullptr;
	init(&system);

	// aquí va lo que quieras que suene desde el principio
	battle(system);

	char key = ' ';
	bool exit = false;
	while (!exit)
	{
		key = getinput();
		key = tolower(key);

		// aquí van los eventos de la simulación
		switch (key) {
		case 'l':
			break;

		case 'q':
			exit = true;
			break;
		default:
			break;
		}
	}

	free(system);
}