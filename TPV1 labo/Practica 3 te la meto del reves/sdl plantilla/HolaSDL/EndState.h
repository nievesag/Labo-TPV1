#ifndef ENDSTATE_H
#define ENDSTATE_H

// include
//
#include <string>

//
#include "GameState.h"

using namespace std;
using uint = unsigned int;

class EndState : public GameState{

private:
	const string s_endID = "END";

public:
	// constructora
	EndState(SDLApplication * game) : GameState(game) { };

	//
	virtual void update();
	//
	virtual void render();

	//
	virtual bool onEnter();
	//
	virtual bool onExit();

	// ----------- GETTERS Y SETTERS -----------
	//
	virtual string getID() const;
};
#endif