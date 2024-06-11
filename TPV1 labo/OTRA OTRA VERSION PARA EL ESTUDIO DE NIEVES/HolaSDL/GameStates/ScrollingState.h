#pragma once

#include "GameState.h"
#include "../SDLApplication.h"

class ScrollingState : public GameState
{
private:
	const std::string s_scrollID = "SCROLL";

public:
	// constructora
	ScrollingState(SDLApplication* game, Texture* texture, GameState* next);

	// renderizado del estado
	void render() const override;

	// al entrar al estado
	bool onEnter() const override;

	// al salir del estado
	bool onExit() const override;

	// getID
	std::string getID() const override;
};

