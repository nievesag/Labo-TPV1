#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "../SDLApplication.h"

class Button;

class PauseState : public GameState{

private:
	const std::string s_pauseID = "PAUSE";

	PlayState* playState;

	SDLApplication* app;

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
	void render() const override;

	// al entrar al estado
	bool onEnter() const override;

	// al salir del estado
	bool onExit() const override;

	// getID
	std::string getID() const override;

private:
	// funciones de los botones
	void continuarPartida();
	void guardarPartida();
	void cargarPartida();
	void salir();
};

#endif