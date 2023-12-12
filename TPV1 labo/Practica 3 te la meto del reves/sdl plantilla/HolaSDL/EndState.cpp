#include "EndState.h"

void EndState::update()
{
	// 
	cout << "update" << endl;
}

void EndState::render()
{
	// 
	cout << "render" << endl;
}

bool EndState::onEnter()
{
	cout << "entering EndState\n";
	return true;
}

bool EndState::onExit()
{
	cout << "exiting EndState\n";
	return true;
}

string EndState::getID() const
{
	return s_endID;
}