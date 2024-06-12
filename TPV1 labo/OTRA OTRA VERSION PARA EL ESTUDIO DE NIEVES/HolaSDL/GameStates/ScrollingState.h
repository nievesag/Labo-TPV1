#pragma once

#include "GameState.h"
#include "../SDLApplication.h"
#include "../GameObjects/ScrollImage.h"

class ScrollingState : public GameState
{
private:
	const std::string s_scrollID = "SCROLL";

	ScrollImage* scrollImg;

	GameState* next_;

	Texture* tex;

public:
	// constructora
	ScrollingState(SDLApplication* game, Texture* texture, GameState* next);

	// renderizado del estado
	void render() const override;

	void update() override;

	// al entrar al estado
	bool onEnter() const override;

	// al salir del estado
	bool onExit() const override;

	void HandleEvent(const SDL_Event& event) override;

	void NextState();

	// getID
	std::string getID() const override;
};