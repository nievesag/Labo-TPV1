#include "PauseState.h"

#include "checkML.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* game, PlayState* playState) 
	: GameState(game), playState(playState), app(game),
	buttonContinuar(new Button(this, game->getTexture(ContGame), Point2D<double>(PScontinueButtonX, PScontinueButtonY))),
	buttonGuardarPartida(new Button(this, game->getTexture(SaveGame), Point2D<double>(PSsaveButtonX, PSsaveButtonY))),
	buttonCargarPartida(new Button(this, game->getTexture(LoadGame), Point2D<double>(PSloadButtonX, PSloadButtonY))),
	buttonSalir(new Button(this, game->getTexture(ExitGame), Point2D<double>(PSexitButtonX, PSexitButtonY)))
{
	// lo aniede a la lista de objetos para poder renderizarlo
	addObject(buttonCargarPartida);
	addObject(buttonSalir);
	addObject(buttonContinuar);
	addObject(buttonGuardarPartida);

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

void PauseState::render() const
{
	// renderiza la imagen de fondo
	application->getTexture(Fondo)->render();

	for (GameObject& a : gamelist) {
		a.render();
	}
}

bool PauseState::onEnter() const
{
	return true;
}

bool PauseState::onExit() const
{
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
	cout << "Inserte num de ranura de guardado: " << endl;

	// llama al metodo de guardado del play state
	playState->saveThisGame();
}

void PauseState::cargarPartida()
{
	cout << "Inserte num de ranura de carga: " << endl;

	char k;
	string file;

	// lee el numero
	cin >> k;

	// crea un string con el archivo
	file = "..\\saved\\save" + to_string(k - '0');

	// crea un nuevo estado con la direccion indicada
	GameState* ps = new PlayState(app, file);

	app->getgsMachine();

	// crea un nuevo play state y lo remplaza con el anterior
	app->getgsMachine()->replaceState(ps);

	// quita este estado
	app->getgsMachine()->popState();
}

void PauseState::salir()
{
	// settea el exit a true (del sdl application)
	app->setExit(true);
}
