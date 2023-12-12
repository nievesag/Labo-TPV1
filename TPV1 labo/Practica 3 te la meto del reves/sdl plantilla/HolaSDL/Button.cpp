#include "Button.h"

void Button::update()
{
	mousePos = SDL_GetMouseState(&x, &y);
	if (mousePos->getX() < (m_position.getX() + width) 
		&& pMousePos->getX() > m_position.getX() 
		&& pMousePos->getY() < (m_position.getY() + height) 
		&& pMousePos->getY() > m_position.getY())
}

void Button::connect(SDLEventCallback buttonCallback)
{
	while (SDL_PollEvent(&event)) {
		for (const SDLEventCallback& buttonCallback : eventCallbacks)
			buttonCallback(event);
	}
}
