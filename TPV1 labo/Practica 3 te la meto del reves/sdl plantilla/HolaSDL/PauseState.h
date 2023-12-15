#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "SDLApplication.h"

class Button;

using namespace std;
using uint = unsigned int;

class PauseState : public GameState{

private:
	const string s_pauseID = "PAUSE";

public:
	// constructora
	PauseState::PauseState(SDLApplication* game);

	//
	virtual void update();

	//
	virtual void render();

	//
	virtual bool onEnter();

	//
	virtual bool onExit();

	// ---- GETTERS Y SETTERS ----
	virtual string getID() const;
};

#endif