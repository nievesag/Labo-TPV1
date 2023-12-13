#include "Button.h"

void Button::update()
{
	SDL_GetMouseState(&x, &y);

	if (x < (x + width) && y < (y + height)) {
		currentFrame = MOUSEOVER;
	}
}

void mouseClick(const SDL_Event& event) {
	
	// si se pulsa el boton izq del raton
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

		// guarda pos del cursor
		SDL_Point point{ event.button.x, event.button.y };

		// comprueba si el punto está en el rect del boton
		if (SDL_PointInRect(&point, &destRect))
			clickedAction();
	}
}

void Button::render() const {

	// el color del rect depende de si el raton esta sobre el
	int r = 0, b = 255;

	if (MOUSEOVER) swap(r, b);

	SDL_SetRenderDrawColor(application->getRenderer(), r, 0, b, 225);

	// Rellena el rectángulo con el color fijado
	SDL_RenderFillRect(application->getRenderer(), &destRect);

	// Restablece el color de fondo (para el SDL_RenderClear)
	SDL_SetRenderDrawColor(application->getRenderer(), 0, 0, 0, 225);
}

void Button::connect(SDLEventCallback buttonCallback)
{
	while (SDL_PollEvent(&event)) {
		for (const SDLEventCallback& buttonCallback : eventCallbacks)
			buttonCallback(event);
	}
}

void clickedAction() {
	application->handleEvents();
}
