#include "MainMenuState.h"

#include "ScrollingState.h"

MainMenuState::MainMenuState(SDLApplication* game) : GameState(game), 
	 buttonNuevaPartida(new Button(this, game->getTexture(NewGame), Point2D<double>(newButtonX, newButtonY)) ),
	 buttonCargarPartida(new Button(this, game->getTexture(LoadGame), Point2D<double>(loadButtonX, loadButtonY))),
	 buttonSalir(new Button(this, game->getTexture(ExitGame), Point2D<double>(exitButtonX, exitButtonY)))
{
	// lo aniede a la lista de objetos para poder renderizarlo
	addObject(buttonNuevaPartida);
	addObject(buttonCargarPartida);
	addObject(buttonSalir);

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

	for (GameObject& a : gamelist) {
		a.render();
	}
}

bool MainMenuState::onEnter() const { return true; }

bool MainMenuState::onExit() const { return true; }
       
string MainMenuState::getID() const { return s_menuID; }


// ---- FUNCIONES A REALIZAR POR LOS BOTONES ----

void MainMenuState::nuevaPartida()
{
	GameState* ps = new ScrollingState(application, application->getTexture(22), new PlayState(application, "..\\mapas\\original"));

	// crea un nuevo estado con la direccion indicada
	//GameState* ps = new PlayState(application, "..\\mapas\\original");

	// lo pasa al gsMachine que ya luego hace sus cosas
	application->getgsMachine()->pushState(ps);
}

void MainMenuState::cargarPartida()
{
	cout << "Inserte num de ranura de carga: " << endl;

	char k;
	string file;

	// lee el numero
	cin >> k;

	// crea un string con el archivo
	file = "..\\saved\\save" + to_string(k - '0');

	// crea un nuevo estado con la direccion indicada
	GameState* ps = new PlayState(application, file);

	// lo pasa al gsMachine que ya luego hace sus cosas
	application->getgsMachine()->pushState(ps);
}

void MainMenuState::salir()
{
	// settea el exit a true (del sdl application)
	application->setExit(true);
}