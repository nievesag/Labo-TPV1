#include "PauseState.h"

PauseState::PauseState(SDLApplication* game) : GameState(game),
	buttonContinuar(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonGuardarPartida(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonCargarPartida(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonSalir(new Button(this, game->getTexture(11), Point2D<double>(1, 1)))
{
	// kiminotoriko :(
	//addObject(buttonNuevaPartida);
	//addObject(buttonCargarPartida);
	//addObject(buttonSalir);

	// para que los botones puedan reaccionar a eventos
	addEventListener(buttonContinuar);
	addEventListener(buttonGuardarPartida);
	addEventListener(buttonCargarPartida);
	addEventListener(buttonSalir);

	// uso de la expresion lambda
	buttonContinuar->connectButton([this]() { continuarPartida(); });
	buttonGuardarPartida->connectButton([this]() { guardarPartida(); });
	buttonCargarPartida->connectButton([this]() { cargarPartida(); });
	buttonSalir->connectButton([this]() { salir(); });
}

void PauseState::render()
{
	//application->getTexture(SaveGame)->render();
}

bool PauseState::onEnter()
{
	cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	cout << "exiting PauseState\n";
	return true;
}

string PauseState::getID() const
{
	return s_pauseID;
}

// ---- FUNCIONES A REALIZAR POR LOS BOTONES ----

void PauseState::continuarPartida()
{

}

void PauseState::guardarPartida()
{

}

void PauseState::cargarPartida()
{

}

void PauseState::salir()
{
}
