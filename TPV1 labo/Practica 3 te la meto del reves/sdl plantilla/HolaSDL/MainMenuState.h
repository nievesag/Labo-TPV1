#ifndef MAINMENUSTATE_H
#define MIANMENUSTATE_H

// includes
#include "GameState.h"

using namespace std;
using uint = unsigned int;

class MainMenuState : public GameState {

private:
	static const std::string s_menuID;

public:

	//constructora
	 
	 
	
	//
	virtual void update();
	//
	virtual void render();

	//
	virtual bool onEnter();
	//
	virtual bool onExit();


	// ----------------------------------- GETTERS Y SETTERS -----------------------
	//
	virtual std::string getStateID() const { return s_menuID; }







};

#endif