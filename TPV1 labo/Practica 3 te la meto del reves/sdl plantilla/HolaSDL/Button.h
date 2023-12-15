#ifndef BUTTON_H
#define BUTTON_H

#include "checkML.h"
#include "EventHandler.h"
#include "GameObject.h"
#include <functional>
#include <SDL.h>
#include "texture.h"
#include "SDLApplication.h"

using namespace std;
using uint = unsigned int;

// utiliza callbacks funcionales de tipo <void(const SDL_Event&)>
using SDLEventCallback = function<void(const SDL_Event&)>;

class Button : public EventHandler, public GameObject
{
private:
	
	int x, y;			// posicion del cursor
	SDL_Point point;	// guarda posicion del cursor en click
	SDL_Rect destRect;	// rectangulo del render
	Texture* buttonTexture;	// textura del boton
	Point2D<double> buttonPos;	// posicion del boton en pantalla

	// estados del bot�n para render y animacion
	int currentFrame;
	enum buttonState {
		MOUSEOUT = 0,
		MOUSEOVER = 1,
		CLICKED = 2
	};

	// CALLBACKS: funcion ejecutable �A� que se usa como argumento de funci�n �B�. 
	// -> al llamar a �B� la funcion ejecuta �A�
	// lista de funciones a llamar cuando sucede un evento
	list<SDLEventCallback> callbacks;

	// METODOS PRIVADOS
	void emit(const SDL_Event& event) const;

public:
	Button(SDLApplication* application, Texture* texture, Point2D<double> pos)
		: buttonTexture(texture), buttonPos(pos), GameObject(application), destRect{ 50, 50, 200, 100 }
	{
		// para animacion
		currentFrame = MOUSEOUT; // frame inicial a 0

		/*
		// si hay textura entonces no es un laser y tiene dimensiones
		if (texture != nullptr) {
			// setea las dimensiones
			destRect.w = texture->getFrameWidth();
			destRect.h = texture->getFrameHeight();
		}
		destRect.x = buttonPos.getX();
		destRect.y = buttonPos.getY();
		*/
	}

	// METODOS PUBLICOS
	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// ---- update ----
	void handleEvent(const SDL_Event& event) override;

	// ---- update ----
	void connectButton(SDLEventCallback buttonCallback);

	// ---- save ----
	// no se si hace falta???? creo q si pero no se usarlo :P
	// void save(std::ostream& out) const override = 0;
};
#endif