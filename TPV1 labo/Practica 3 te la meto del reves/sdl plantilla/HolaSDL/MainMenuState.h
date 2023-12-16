#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

// includes
#include "GameState.h"
//#include "Button.h"
#include "SDLApplication.h"
//class SDLApplication;

class Button;

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

public:
	// constructora
	MainMenuState(SDLApplication* game);
	 
	// renderizado del estado
	void render() const override;

	// al entrar al estado
	bool onEnter() override;

	// al salir del estado
	bool onExit() override;

	// getID
	string getID() const override;

private:
	// funciones de los botones
	void nuevaPartida();
	void cargarPartida();
	void salir();
};
#endif