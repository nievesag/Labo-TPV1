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

	// offset del descenso
	int offset;

	// metodos publicos
public:
	Mothership::Mothership(int offset, Game* game) 
		: offset(offset), GameObject(game) { }
		
	// ajusta la direccion de los aliens
	void getDirection();

	// devuelve si se sigue moviendo o no (?????????)
	bool shouldMove();

	// devuelve si se puede seguir moviendo o no
	bool cannotMove();

	// devuelve si el alien ha muerto
	bool alienDead();

	// devuelve si han llegado al suelo o no (se acaba partida))
	bool alienLanded();

	// guatafac
	bool haveLlanded();

	// devuelve la cantidad de aliens que quedan
	int getAlienCount();
};
#endif