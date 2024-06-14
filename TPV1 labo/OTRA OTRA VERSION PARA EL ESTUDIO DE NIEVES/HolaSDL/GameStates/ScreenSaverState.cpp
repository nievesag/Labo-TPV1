#include "ScreenSaverState.h"
#include "../SDLApplication.h"
#include "../checkML.h"

ScreenSaverState::ScreenSaverState(SDLApplication* game) :
	GameState(game)
{
	screenSaver = new ScreenSaverObject(Point2D<double>(winWidth, 300), 50, 50, application->getTexture(UfoT), this);
	addObject(screenSaver);
}

void ScreenSaverState::render() const
{
	// renderiza el fondo
	getApplication()->getTexture(24)->render();
	screenSaver->render();
}

void ScreenSaverState::update()
{
	screenSaver->update();
}

bool ScreenSaverState::onEnter() const { return true; }

bool ScreenSaverState::onExit() const { return true; }

void ScreenSaverState::HandleEvent(const SDL_Event& event)
{
	GameState::HandleEvent(event);

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		goToMenu();
	}
}

void ScreenSaverState::goToMenu()
{
	application->getgsMachine()->popState();
}

std::string ScreenSaverState::getID() const
{
	return s_saverID;
}
