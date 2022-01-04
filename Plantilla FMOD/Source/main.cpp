#include <iostream>
#include <ctime>
#include <chrono>

#ifndef MACROS
#define MACROS

bool keyboardhit();
char getinput();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string slash = "\\";

#include <conio.h>
bool keyboardhit() { return _kbhit(); }
char getinput() { return _getch(); }

#elif defined(unix) || defined(__unix) || defined(__unix__)
static const std::string slash = "/";

/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>

int _kbhit() {
	static const int STDIN = 0;
	static bool initialized = false;

	if (!initialized) {
		// Use termios to turn off line buffering
		termios term;
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, NULL);
		initialized = true;
	}

	int bytesWaiting;
	ioctl(STDIN, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}
/**
 End of implementation from Morgan McGuire
**/

#include <unistd.h>

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

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_ESC 27

static const std::string assetsPath = "." + slash + "Assets" + slash;

#define PATH(filename) (assetsPath + filename).c_str()

#include <fmod_errors.h>

// para salidas de error
void ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		// printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

#endif // !MACROS

#include "fmod.hpp"

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

	battle(system);

	bool exit = false;

	auto lastUpdate = std::chrono::system_clock::now();
	while (!exit)
	{
		// calculate deltaTime
		auto newUpdate = std::chrono::system_clock::now();
		std::chrono::duration<float, std::milli> diff = newUpdate - lastUpdate;
		lastUpdate = newUpdate;
		float deltaTime = diff.count();

		// process input
		if (keyboardhit())
		{
			char key = tolower(getinput());

			if (key == 0 || key == 224)		// https://stackoverflow.com/a/54581468/12927977
			{
				// extended ascii format, read again
				key = getinput();
			}

			switch (key)
			{
			case KEY_UP:
				break;
			case KEY_DOWN:
				break;
			case KEY_LEFT:
				break;
			case KEY_RIGHT:
				break;

			default:
				break;
			}

			exit = (key == 'q' || key == KEY_ESC);
		}


		ERRCHECK(system->update());
	}

	free(system);
}