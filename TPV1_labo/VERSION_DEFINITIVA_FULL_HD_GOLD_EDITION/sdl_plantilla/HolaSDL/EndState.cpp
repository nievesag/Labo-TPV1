#include "EndState.h"

EndState::EndState(SDLApplication* game, bool victory) : GameState(game), victory(victory),
	buttonVolverMenu(new Button(this, game->getTexture(GoBack), Point2D<double>(goBackButtonX, goBackButtonY))),
	buttonSalir(new Button(this, game->getTexture(ExitGame), Point2D<double>(exitButton2X, exitButton2Y)))
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

bool EndState::onEnter() const { return true; }

bool EndState::onExit() const { return true; }

string EndState::getID() const { return s_endID; }


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