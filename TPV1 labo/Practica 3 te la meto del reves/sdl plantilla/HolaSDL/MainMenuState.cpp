#include "MainMenuState.h"

MainMenuState::MainMenuState(SDLApplication* game) : GameState(game), app(game)
{

	buttonNuevaPartida = (new Button(this, game->getTexture(11), Point2D<double>(1, 1)) );

}

void MainMenuState::update()
{


	//
	//cout << "update" << endl;
}

void MainMenuState::render() const
{
	// renderiza la imagen de fondo
	app->getTexture(MainMenu)->render();

	//
	//cout << "render" << endl;
}

bool MainMenuState::onEnter()
{
	cout << "entering MenuState\n";
	return true;
}

bool MainMenuState::onExit()
{
	cout << "exiting MenuState\n";
	return true;
}

string MainMenuState::getID() const
{
	return s_menuID;
}