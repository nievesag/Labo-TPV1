#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "SDLApplication.h"

class Button;

using namespace std;
using uint = unsigned int;

class PauseState : public GameState{

private:
	const string s_pauseID = "PAUSE";

	PlayState* playState;

	// punteros a los botones del PAUSE MENU
	// botones en este estado: CONTINUAR / GUARDAR PARTIDA / CARGAR PARTIDA / SALIR
	Button* buttonContinuar;
	Button* buttonGuardarPartida;
	Button* buttonCargarPartida;
	Button* buttonSalir;

public:
	// constructora
	PauseState::PauseState(SDLApplication* game, PlayState* playState);

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
	void continuarPartida();
	void guardarPartida();
	void cargarPartida();
	void salir();

};

#endif