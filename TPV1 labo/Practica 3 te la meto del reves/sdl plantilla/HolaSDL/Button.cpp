#include "Button.h"
#include "SDLApplication.h"

void Button::update()
{
	SDL_GetMouseState(&point.x, &point.y);

	// comprueba si el cursor esta sobre el rectangulo
	if (SDL_PointInRect(&point, &destRect)) {
		currentFrame = MOUSEOVER;
	}
}

void Button::emit(const SDL_Event& event) const
{
	// llama a todas las funciones registradas (callbacks)
	for (const SDLEventCallback& callback : callbacks)
		callback(event);
}

void Button::render() const {

	// el color del rect depende de si el raton esta sobre el
	int r = 0, b = 255;    

	if (currentFrame == MOUSEOVER) swap(r, b);

	SDL_SetRenderDrawColor(application->getRenderer(), r, 0, b, 225);

	// Rellena el rect�ngulo con el color fijado
	SDL_RenderFillRect(application->getRenderer(), &destRect);

	// Restablece el color de fondo (para el SDL_RenderClear)
	SDL_SetRenderDrawColor(application->getRenderer(), 0, 0, 0, 225);
}

void mouseClick(const SDL_Event& event) {
	
	// si se pulsa el boton izq del raton
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

		// guarda pos del cursor al pulsar
		SDL_Point point{ event.button.x, event.button.y };

		// comprueba si el punto est� en el rect del boton
		if (SDL_PointInRect(&point, &destRect)) {
			emit(event);
		}	
	}
}

void Button::connect(SDLEventCallback buttonCallback)
{
	callbacks.push_back(buttonCallback);
}

void clickedAction() {
	application->handleEvents();
}
