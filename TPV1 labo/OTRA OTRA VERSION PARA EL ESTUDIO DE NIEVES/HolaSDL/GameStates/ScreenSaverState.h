#pragma once
#include "GameState.h"
#include "../GameObjects/ScreenSaverObject.h"

class ScreenSaverState : public GameState
{
	const std::string s_saverID = "SAVER";

	ScreenSaverObject* screenSaver;
	Texture* tex;

public:
	// constructora
	ScreenSaverState(SDLApplication* game);

	// renderizado del estado
	void render() const override;

	void update() override;

	// al entrar al estado
	bool onEnter() const override;

	// al salir del estado
	bool onExit() const override;

	void HandleEvent(const SDL_Event& event) override;

	void goToMenu();

	// getID
	std::string getID() const override;
};