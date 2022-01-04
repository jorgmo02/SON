#pragma once
class InputListener
{
public:
	InputListener();
	virtual ~InputListener();
	virtual void process(char key);
};