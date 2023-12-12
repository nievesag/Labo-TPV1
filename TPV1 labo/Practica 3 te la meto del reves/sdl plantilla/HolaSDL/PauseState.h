#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"

using namespace std;
using uint = unsigned int;

class PauseState : public GameState{

private:
	const string s_pauseID = "PAUSE";

public:
	// constructora
	PauseState::PauseState(SDLApplication * game) : GameState(game) { };


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

	virtual string getID() const;


};

#endif