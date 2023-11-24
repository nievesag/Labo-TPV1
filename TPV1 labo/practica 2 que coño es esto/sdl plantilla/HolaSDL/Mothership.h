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
	enum state RIGHT, dRIGHT, LEFT, dLEFT;

	// estado actual del movimiento de los aliens
	state currentState = RIGHT;

	// offset del descenso
	int level;

	// metodos publicos
public:
	Mothership::Mothership(int offset, Game* game) 
		: level(level), GameObject(game) { }
		
	//
	bool update() override;

	// ajusta la direccion de los aliens
	Vector2D<int> getDirection();

	// devuelve si se sigue moviendo o no (?????????)
	bool shouldMove();

	// INFORMAN A ALIEN
	// devuelve si se puede seguir moviendo o no
	bool cannotMove();

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