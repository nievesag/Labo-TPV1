#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

// includes
#include <SDL.h>

class EventHandler {
public: 
	// gestiona un evento
	virtual void handleEvent(const SDL_Event& event) = 0; // igualar a 0 para no crear cpp
};
#endif