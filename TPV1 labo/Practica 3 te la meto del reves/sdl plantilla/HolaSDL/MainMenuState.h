#ifndef MAINMENUSTATE_H
#define MIANMENUSTATE_H

// includes
#include "GameState.h"

using namespace std;
using uint = unsigned int;

class MainMenuState : public GameState {

private:

	const string s_menuID = "MENU";

public:

	//constructora
	MainMenuState(SDLApplication* game) : GameState(game) { };
	 
	
	//
	void update() override;
	//
	void render() override;

	//
	bool onEnter() override;
	//
	bool onExit() override;


	// ----------------------------------- GETTERS Y SETTERS -----------------------
	//

	string getID() const override;
};

#endif