#include "Button.h"

Button::Button(GameState* gameState, Texture* texture, Point2D<double> pos)
	: GameObject(gameState), buttonTexture(texture), buttonPos(pos)
{
	// para animacion
	currentFrame = MOUSEOUT; // frame inicial a 0

	// setea posiciones y dimensiones en el destRect
	destRect = SDL_Rect{ (int)pos.getX(), (int)pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
}


void Button::update()
{
	SDL_GetMouseState(&point.x, &point.y);

	// comprueba si el cursor esta sobre el rectangulo
	if (SDL_PointInRect(&point, &destRect)) {
		currentFrame = MOUSEOVER;
	}
	else currentFrame = MOUSEOUT;
}

void Button::emit() const
{
	// llama a todas las funciones registradas
	for (SDLEventCallback buttonCallback : callbacks)
		buttonCallback();
}

void Button::render() const {

	buttonTexture->render(destRect);

	/*
	// el color del rect depende de si el raton esta sobre el
	int r = 0, b = 255;    

	if (currentFrame == MOUSEOVER) swap(r, b);

	SDL_SetRenderDrawColor(application->getRenderer(), r, 0, b, 225);

	// Rellena el rect�ngulo con el color fijado
	SDL_RenderFillRect(application->getRenderer(), &destRect);

	// Restablece el color de fondo (para el SDL_RenderClear)
	SDL_SetRenderDrawColor(application->getRenderer(), 0, 0, 0, 225);
	*/
}

void Button::handleEvent(const SDL_Event& event) {
	
	// si se pulsa el boton izq del raton
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

		// guarda pos del cursor al pulsar
		SDL_Point point{ event.button.x, event.button.y };

		// comprueba si el punto est� en el rect del boton
		if (SDL_PointInRect(&point, &destRect)) {
			currentFrame = CLICKED;
			emit();
		}
	}
}

void Button::connectButton(SDLEventCallback buttonCallback)
{
	callbacks.push_back(buttonCallback);
}