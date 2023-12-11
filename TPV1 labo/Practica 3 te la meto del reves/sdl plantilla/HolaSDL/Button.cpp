#include "Button.h"

void Button::connect(SDLEventCallback buttonCallback)
{
	while (SDL_PollEvent(&event)) {
		for (const SDLEventCallback& buttonCallback : eventCallbacks)
			buttonCallback(event);
	}
}
