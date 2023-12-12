#include "PauseState.h"

void PauseState::update()
{
	// 
	cout << "update" << endl;
}

void PauseState::render()
{
	// 
	cout << "update" << endl;
}

bool PauseState::onEnter()
{
	cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	cout << "exiting PauseState\n";
	return true;
}

string PauseState::getID() const
{
	return s_pauseID;
}
