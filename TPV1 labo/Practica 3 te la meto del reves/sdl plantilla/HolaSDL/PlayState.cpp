#include "PlayState.h"
#include "checkML.h"
#include "SDLApplication.h"

void PlayState::update()
{
	//
	cout << "update" << endl;
}

void PlayState::render()
{
	//
	cout << "render" << endl;
}

bool PlayState::onEnter()
{
	cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	cout << "exiting PlayState\n";
	return true;
}
