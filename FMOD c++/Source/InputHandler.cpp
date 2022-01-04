#include "InputHandler.h"
#include "InputListener.h"
#include "macros.h"
#include <algorithm>

std::list<InputListener*> InputHandler::Listeners;
bool InputHandler::Exit = false;

void InputHandler::Add(InputListener* listener)
{
	auto it = std::find(Listeners.begin(), Listeners.end(), listener);

	if (it == Listeners.end()) {
		Listeners.push_back(listener);
	}
}

bool InputHandler::Remove(InputListener* listener)
{
	auto it = std::find(Listeners.begin(), Listeners.end(), listener);

	if (it != Listeners.end()) {
		Listeners.erase(it);
		return true;
	}

	return false;
}

void InputHandler::Update()
{
	if (keyboardhit())
	{
		char key = tolower(getinput());

		if (key == 0 || key == 224)		// https://stackoverflow.com/a/54581468/12927977
		{
			// extended ascii format, read again
			key = getinput();
		}

		for (InputListener* il : Listeners) {
			il->process(key);
		}

		Exit = (key == 'q' || key == KEY_ESC);
	}
}