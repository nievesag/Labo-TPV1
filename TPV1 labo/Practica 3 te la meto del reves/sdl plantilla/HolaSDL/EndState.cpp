#include "EndState.h"

EndState::EndState(SDLApplication* game, bool victory) : GameState(game), victory(victory),
	buttonVolverMenu(new Button(this, game->getTexture(16), Point2D<double>(220, 250))),
	buttonSalir(new Button(this, game->getTexture(13), Point2D<double>(330, 350)))
{
	// lo aniede a la lista de objetos para poder renderizarlos
	addObject(buttonVolverMenu);
	addObject(buttonSalir);

	// para que los botones puedan reaccionar a eventos
	addEventListener(buttonVolverMenu);
	addEventListener(buttonSalir);

	// uso de la expresion lambda
	buttonVolverMenu->connectButton([this]() { volverMenu(); });
	buttonSalir->connectButton([this]() { salir(); });
}


void EndState::render() const
{
	if (victory) {
		application->getTexture(YouWon)->render();
	}
	else {
		application->getTexture(GameIsOver)->render();
	}

	for (GameObject& a : gamelist) {
		a.render();
	}
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
	// quita los dos estados on TOP, porque siempre seran el propio endGame y el paystate
	application->getgsMachine()->popState();
	application->getgsMachine()->popState();
}

void EndState::salir()
{
	// settea el exit a true (del sdl application)
	application->setExit(true);
}