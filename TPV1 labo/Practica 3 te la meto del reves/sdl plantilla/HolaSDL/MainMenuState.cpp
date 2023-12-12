#include "MainMenuState.h"

void MainMenuState::update()
{
	//
	cout << "update" << endl;
}

void MainMenuState::render()
{
	//
	cout << "render" << endl;
}

bool MainMenuState::onEnter()
{
	cout << "entering MenuState\n";
	return false;
}

bool MainMenuState::onExit()
{
	cout << "exiting MenuState\n";
	return false;
}

string MainMenuState::getID() const
{
	return s_menuID;
}

