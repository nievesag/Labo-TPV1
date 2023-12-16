#ifndef ENDSTATE_H
#define ENDSTATE_H

// include
//
#include <string>

//
#include "GameState.h"
#include "SDLApplication.h"
//class SDLApplication;

class Button;

using namespace std;
using uint = unsigned int;

class EndState : public GameState{

private:
	const string s_endID = "END";

	// punteros a los botones del GAME OVER MENU
	// botones en este estado: VOLVER AL MENÚ / SALIR
	Button* buttonVolverMenu;
	Button* buttonSalir;

public:
	// constructora
	EndState(SDLApplication* game);

	// renderizado del estado
	virtual void render();

	// al entrar al estado
	virtual bool onEnter();

	// al salir del estado
	virtual bool onExit();

	// getID
	virtual string getID() const;

private:
	// funciones de los botones
	void volverMenu();
	void salir();
};
#endif