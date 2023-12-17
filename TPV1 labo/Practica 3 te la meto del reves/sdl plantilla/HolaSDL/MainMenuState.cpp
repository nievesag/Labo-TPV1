#include "MainMenuState.h"

MainMenuState::MainMenuState(SDLApplication* game) : GameState(game), 
	buttonNuevaPartida(new Button(this, game->getTexture(11), Point2D<double>(1, 1)) ),
	buttonCargarPartida(new Button(this, game->getTexture(11), Point2D<double>(1, 1))),
	buttonSalir(new Button(this, game->getTexture(11), Point2D<double>(1, 1)))
{
	// emmmmmmmmmmm q
	//addObject(buttonNuevaPartida);
	addObject(buttonCargarPartida);
	//addObject(buttonSalir);

	// para que los botones puedan reaccionar a eventos
	//addEventListener(buttonNuevaPartida);
	addEventListener(buttonCargarPartida);
	//addEventListener(buttonSalir);

	// uso de la expresion lambda
	//buttonNuevaPartida->connectButton( [this]() { nuevaPartida(); });
	buttonCargarPartida->connectButton( [this]() { cargarPartida(); });
	//buttonSalir->connectButton( [this]() { salir(); });
}

void MainMenuState::render() const
{
	// renderiza la imagen de fondo
	application->getTexture(MainMenu)->render();

	for (GameObject& a : gamelist) {
		a.render();
	}
	
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
	// crea un nuevo estado con la direccion indicada
	GameState* ps = new PlayState(application, "..\\mapas\\prueba");

	// lo pasa al gsMachine que ya luego hace sus cosas
	application->getgsMachine()->pushState(ps);
}

void MainMenuState::cargarPartida()
{
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
	// exit sera???? pero paso de mriarlo tbh
}