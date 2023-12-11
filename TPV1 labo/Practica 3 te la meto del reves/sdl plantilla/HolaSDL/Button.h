#ifndef BUTTON_H
#define BUTTON_H

#include "EventHandler.h"
#include "GameObject.h"
#include <functional>

using namespace std;
using uint = unsigned int;
// utiliza callbacks funcionales de tipo <void(const SDL_Event&)>
using SDLEventCallback = function<void(const SDL_Event&)>;

class Button : public EventHandler, public GameObject
{
private:
	Texture* buttonTexture;
	// PLACEHOLDER!!!!!
	SDL_Event event;
	vector<SDLEventCallback> eventCallbacks;

public:
	Button::Button() {}
	void clicked(Button* btn) {  }

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// registra callbacks
	void connect(SDLEventCallback buttonCallback);
};
#endif