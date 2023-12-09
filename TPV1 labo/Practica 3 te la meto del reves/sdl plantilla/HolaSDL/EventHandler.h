#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

// includes
#include <SDL.h>

using namespace std;
using uint = unsigned int;

class EventHandler {

public: 

	// gestiona un evento
	void handleEvent(const SDL_Event& event);

};

#endif