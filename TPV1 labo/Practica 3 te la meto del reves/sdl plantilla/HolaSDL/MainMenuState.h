#ifndef MAINMENUSTATE_H
#define MIANMENUSTATE_H

// includes
#include "GameState.h"

using namespace std;
using uint = unsigned int;

class MainMenuState : public GameState {

private:

	const string s_menuID;

public:

	//constructora
	MainMenuState(SDLApplication* game) : GameState(game) { };
	 
	
	//
	void update();
	//
	void render();

	//
	bool onEnter();
	//
	bool onExit();


	// ----------------------------------- GETTERS Y SETTERS -----------------------
	//

	string getID() const;
};

#endif