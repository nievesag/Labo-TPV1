#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#include "GameObject.h"

using namespace std;
using uint = unsigned int;

class Mothership : public GameObject
{
	// atributos privados
private:
	
	// enum ciclico de estados
	enum state : int { RIGHT, dRIGHT, LEFT, dLEFT };

	// estado actual del movimiento de los aliens
	state currentState;

	// offset del descenso
	int level;

	// metodos publicos
public:
	Mothership::Mothership(int offset, Game* game) 
		: level(level), GameObject(game) {
		currentState = RIGHT;
	}
		
	//
	void update() override;

	// ajusta la direccion de los aliens
	Vector2D<int> getDirection();

	int getLevel() { return level; }

	// devuelve si se sigue moviendo o no (?????????)
	bool shouldMove();
	
	// cambia la direccion actual de los aliens
	void cannotMove();

	// INFORMAN A ALIEN
	// devuelve si el alien ha muerto
	bool alienDied();

	// devuelve si han llegado al suelo o no (se acaba partida))
	bool alienLanded();

	// INFORMAN AL JUEGO
	// guatafac
	bool haveLanded();

	// devuelve la cantidad de aliens que quedan
	int getAlienCount();
};
#endif