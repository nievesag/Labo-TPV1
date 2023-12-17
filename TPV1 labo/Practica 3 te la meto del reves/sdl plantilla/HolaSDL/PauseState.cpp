#include "PauseState.h"

#include "checkML.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* game, PlayState* playState) 
	: GameState(game), playState(playState), app(game),
	buttonContinuar(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonGuardarPartida(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonCargarPartida(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonSalir(new Button(this, game->getTexture(11), Point2D<double>(1, 1)))
{
	// kiminotoriko :(
	//addObject(buttonNuevaPartida);
	addObject(buttonCargarPartida);
	//addObject(buttonSalir);

	// para que los botones puedan reaccionar a eventos
	//addEventListener(buttonContinuar);
	//addEventListener(buttonGuardarPartida);
	addEventListener(buttonCargarPartida);
	//addEventListener(buttonSalir);

	// uso de la expresion lambda
	//buttonContinuar->connectButton([this]() { continuarPartida(); });
	//buttonGuardarPartida->connectButton([this]() { guardarPartida(); });
	buttonCargarPartida->connectButton([this]() { cargarPartida(); });
	//buttonSalir->connectButton([this]() { salir(); });

}

void PauseState::render()
{
	app->getTexture(Fondo)->render();
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
	// quita el estado on TOP
	app->getgsMachine()->popState();
}

void PauseState::guardarPartida()
{
	// llama al metodo de guardado del play state
	playState->saveThisGame();
}

void PauseState::cargarPartida()
{
	
	char k;
	string file;

	// lee el numero
	cin >> k;

	// crea un string con el archivo
	file = "..\\saved\\save" + to_string(k - '0');

	// crea un nuevo estado con la direccion indicada
	GameState* ps = new PlayState(app, file);

	app;

	app->getgsMachine();

	// crea un nuevo play state y lo remplaza con el anterior
	app->getgsMachine()->replaceState(ps);

	// quita este estado
	app->getgsMachine()->popState();

	

}

void PauseState::salir()
{
	// settea el exit a false (del sdl application)
	app->setExit(true);
}
