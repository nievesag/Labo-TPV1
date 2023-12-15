#include "MainMenuState.h"

void MainMenuState::update()
{
	//
	cout << "update" << endl;
}

void MainMenuState::render() const
{
	//
	cout << "render" << endl;
}

bool MainMenuState::onEnter()
{
	cout << "entering MenuState\n";
	return true;
}

bool MainMenuState::onExit()
{
	cout << "exiting MenuState\n";
	return true;
}

string MainMenuState::getID() const
{
	return s_menuID;
}