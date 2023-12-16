#include "EndState.h"

EndState::EndState(SDLApplication* game) : GameState(game),
	buttonVolverMenu(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonSalir(new Button(this, game->getTexture(11), Point2D<double>(1, 1)))
{
	// emmmmmmmmmmm q
	//addObject(buttonVolverMenu);
	//addObject(buttonSalir);

	// para que los botones puedan reaccionar a eventos
	addEventListener(buttonVolverMenu);
	addEventListener(buttonSalir);

	// uso de la expresion lambda
	buttonVolverMenu->connectButton([this]() { volverMenu(); });
	buttonSalir->connectButton([this]() { salir(); });
}


void EndState::render()
{
	//application->getTexture(GameIsOver)->render();
}

bool EndState::onEnter()
{
	cout << "entering EndState\n";
	return true;
}

bool EndState::onExit()
{
	cout << "exiting EndState\n";
	return true;
}

string EndState::getID() const
{
	return s_endID;
}


// ---- FUNCIONES A REALIZAR POR LOS BOTONES ----

void EndState::volverMenu()
{

}

void EndState::salir()
{

}