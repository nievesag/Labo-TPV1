#include "Button.h"

void Button::update()
{
	SDL_GetMouseState(&x, &y);

	if (x < (x + width) && y < (y + height)) {
		currentFrame = MOUSEOVER;

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				mouseClick(e.button);
				click = true;
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				click = false;
			}
		}
	}
}

void mouseClick(SDL_MouseButtonEvent& b) {
	if (b.button == SDL_BUTTON_LEFT) {
		//clickedAction(this);
	}
}

void Button::render() const {
	buttonTexture->renderFrame(destRect, 3, 1);
}

void Button::connect(SDLEventCallback buttonCallback)
{
	while (SDL_PollEvent(&event)) {
		for (const SDLEventCallback& buttonCallback : eventCallbacks)
			buttonCallback(event);
	}
}

void clickedAction(Button* btn) {

}
