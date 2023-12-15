#ifndef MAINMENUSTATE_H
#define MIANMENUSTATE_H

// includes
#include "GameState.h"
#include "Button.h"
#include "SDLApplication.h"
//class Button;

using namespace std;
using uint = unsigned int;

class MainMenuState : public GameState {

private:
	const string s_menuID = "MENU";

	// punteros a los botones del MAIN MENU
	// botones en este estado: NUEVA PARTIDA / CARGAR PARTIDA / SALIR
	Button* buttonNuevaPartida;
	Button* buttonCargarPartida;
	Button* buttonSalir;

	SDLApplication* appilcation;

public:
	//constructora
	MainMenuState(SDLApplication* game)
		: GameState(game), buttonNuevaPartida(new Button(application, application->getTexture(3), ) {};
	 
	// 
	void update() override;

	// 
	void render() const override;

	// 
	bool onEnter() override;

	// 
	bool onExit() override;

	// ---- GETTERS Y SETTERS ----
	// 
	string getID() const override;
};

#endif