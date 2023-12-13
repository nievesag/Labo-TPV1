#ifndef BUTTON_H
#define BUTTON_H

#include "EventHandler.h"
#include "GameObject.h"
#include <functional>
#include <SDL.h>
#include "texture.h"

using namespace std;
using uint = unsigned int;

class SDLApplication;

// utiliza callbacks funcionales de tipo <void(const SDL_Event&)>
using SDLEventCallback = function<void(const SDL_Event&)>;

class Button : public EventHandler, public GameObject
{
private:
	// posicion del cursor
	int x, y;
	SDL_Point point;

	Texture* buttonTexture;
	//SDLApplication* application;

	// rectangulo del render
	SDL_Rect destRect;

	// estados del botón para render y animacion (?)
	int currentFrame;
	enum buttonState {
		MOUSEOUT = 0,
		MOUSEOVER = 1,
		CLICKED = 2
	};

	// CALLBACKS: funcion ejecutable «A» que se usa como argumento de función «B». 
	// -> al llamar a «B» la funcion ejecuta «A»
	// lista de funciones a llamar cuando sucede un evento
	list<SDLEventCallback> callbacks;

	// lista de oyentes de eventos del botón -> reacciona al click
	list<EventHandler*> clickListeners;

	//
	SDLApplication* app;

public:
	Button(SDLApplication* application) 
		: GameObject(application), destRect{ 50, 50, 200, 100 }
	{
		// para animacion
		currentFrame = MOUSEOUT; // frame inicial a 0

		app = application;

		connectButton();

		/*
		// si hay textura entonces no es un laser y tiene dimensiones
		if (texture != nullptr) {
			// setea las dimensiones
			destRect.w = texture->getFrameWidth();
			destRect.h = texture->getFrameHeight();
		}
		destRect.x = position.getX();
		destRect.y = position.getY();
		*/
	}

	// METODOS
	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	void emit(const SDL_Event& event) const;

	void handleEvent(const SDL_Event& event) override;

	void connectButton();

	/*
	// devuelve rect (posicion) de cada objeto
	SDL_Rect* getRect() { SDL_Rect* rect = &destRect; return rect; };

	Texture* getTexture() const { return buttonTexture; };
	*/
};
#endif