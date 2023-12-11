#include "MainMenuState.h"

void MainMenuState::update()
{
	//

}

void MainMenuState::render()
{
	//

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

