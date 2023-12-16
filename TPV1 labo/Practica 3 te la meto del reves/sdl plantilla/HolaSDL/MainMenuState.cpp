#include "MainMenuState.h"

MainMenuState::MainMenuState(SDLApplication* game) : GameState(game), 
	buttonNuevaPartida(new Button(this, game->getTexture(11), Point2D<double>(1, 1)) ),
	buttonCargarPartida(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonSalir(new Button(this, game->getTexture(11), Point2D<double>(1, 1)))
{
	// emmmmmmmmmmm q
	//addObject(buttonNuevaPartida);
	//addObject(buttonCargarPartida);
	//addObject(buttonSalir);

	// para que los botones puedan reaccionar a eventos
	addEventListener(buttonNuevaPartida);
	addEventListener(buttonCargarPartida);
	addEventListener(buttonSalir);

	// uso de la expresion lambda
	buttonNuevaPartida->connectButton( [this]() { nuevaPartida(); });
	buttonCargarPartida->connectButton( [this]() { cargarPartida(); });
	buttonSalir->connectButton( [this]() { salir(); });
}

void MainMenuState::render() const
{
	// renderiza la imagen de fondo
	application->getTexture(MainMenu)->render();
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


// ---- FUNCIONES A REALIZAR POR LOS BOTONES ----

void MainMenuState::nuevaPartida()
{

}

void MainMenuState::cargarPartida()
{

}

void MainMenuState::salir()
{

}