#include "PlayState.h"
#include "checkML.h"
#include "SDLApplication.h"

void PlayState::update()
{
	//
	cout << "update" << endl;

	for (int i = 0; i < gamelist.size(); i++)
	{
		// gestionar con iterator
		//gamelist[i]->update();
	}

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

string PlayState::getID() const
{
	return s_playID;
}
