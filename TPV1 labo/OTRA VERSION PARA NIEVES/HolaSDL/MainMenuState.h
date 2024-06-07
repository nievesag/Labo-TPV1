#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

// includes
#include "GameState.h"
#include "SDLApplication.h"
#include <string>

class Button;

class MainMenuState : public GameState {

private:
	const std::string s_menuID = "MENU";

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
	bool onEnter() const override;

	// al salir del estado
	bool onExit() const override;

	// getID
	std::string getID() const override;

private:
	// funciones de los botones
	void nuevaPartida();
	void cargarPartida();
	void salir();
};
#endif