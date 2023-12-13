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
	// PLACEHOLDER!!!!!
	vector<SDLEventCallback> eventCallbacks;

	// posicion del cursor
	int x, y;
	SDL_Point point;

	Texture* buttonTexture;

	Point2D<int> mousePos;

	// posicion del boton
	Point2D<double> position;

	// dimension del boton (height & width)   
	int width, height;

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

public:
	Button(Point2D<double> position, int width, int height, Texture* texture, SDLApplication* application) :
		destRect{ 50, 50, 200, 100 }, buttonTexture(texture), GameObject(application)
	{
		// para animacion
		currentFrame = MOUSEOUT; // frame inicial a 0

		// si hay textura entonces no es un laser y tiene dimensiones
		if (texture != nullptr) {
			// setea las dimensiones
			destRect.w = texture->getFrameWidth();
			destRect.h = texture->getFrameHeight();
		}
		destRect.x = position.getX();
		destRect.y = position.getY();
	}

	// METODOS
	void clickedAction();

	void mouseClick(const SDL_Event& event);

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	void handleEvent(const SDL_Event& event) override;

	void emit(const SDL_Event& event) const;

	// devuelve rect (posicion) de cada objeto
	SDL_Rect* getRect() { SDL_Rect* rect = &destRect; return rect; };

	Point2D<double> getPosition() const { return position; };

	Texture* getTexture() const { return buttonTexture; };

	// registra callbacks
	void connect(SDLEventCallback buttonCallback);
};
#endif