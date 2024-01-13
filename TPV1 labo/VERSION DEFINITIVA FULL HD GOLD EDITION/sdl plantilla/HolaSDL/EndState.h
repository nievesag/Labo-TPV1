#ifndef ENDSTATE_H
#define ENDSTATE_H

// include
#include <string>

#include "GameState.h"
#include "SDLApplication.h"

class Button;

class EndState : public GameState{

private:
	const std::string s_endID = "END";

	// punteros a los botones del GAME OVER MENU
	// botones en este estado: VOLVER AL MENÚ / SALIR
	Button* buttonVolverMenu;
	Button* buttonSalir;

	// true si se ha ganado la partida -> menu victory
	// false si se ha perdido la partida -> menu game over
	bool victory; 

public:
	// constructora
	EndState(SDLApplication* game, bool victory);

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
	void volverMenu();
	void salir();
};
#endif