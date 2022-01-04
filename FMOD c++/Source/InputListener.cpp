#include "InputListener.h"
#include "InputHandler.h"

InputListener::InputListener()
{
	InputHandler::Add(this);
}

InputListener::~InputListener()
{
	InputHandler::Remove(this);
}

void InputListener::process(char key)
{
}