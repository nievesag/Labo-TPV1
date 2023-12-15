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
	//constructora
	MainMenuState(SDLApplication* game);
	 
	// buttonNuevaPartida(new Button(this, game->getTexture(11), Point2D<double>(1,1))) 
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