#pragma once
#include <list>
#include <queue>

class InputListener;

class InputHandler
{
private:
	static std::list<InputListener*> Listeners;

public:
	static bool Exit;

	static void Add(InputListener* listener);
	static bool Remove(InputListener* listener);
	static void Update();
};