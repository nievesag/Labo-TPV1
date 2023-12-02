#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#include "GameObject.h"
#include "Alien.h"

using namespace std;
using uint = unsigned int;

class Alien;

class Mothership : public GameObject
{
	// atributos privados
private:
	
	// enum ciclico de estados
	enum state : int { RIGHT, dRIGHT, LEFT, dLEFT };

	// estado actual del movimiento de los aliens
	state currentState;

	int dir;

	// offset del descenso
	int level;

	// tiempo para los updates
	int alienTimer;

	int alienCount;

	// metodos publicos
public:
	Mothership::Mothership(int level, Game* game, int alienTimer, int n) 
		: level(level), GameObject(game), alienTimer(alienTimer) {

		dir = 1;

		/*
		* if (n == 1) currentState = dRIGHT;
		else if (n == 2) currentState = LEFT;
		else if (n == 3) currentState = dLEFT;
		else currentState = RIGHT;
		*/
		
	}
		
	//
	void update() override;

	void save(ostream& out) const override;

	// ajusta la direccion de los aliens
	Vector2D<int> getDirection();

	int getLevel() { return level; }

	// añade alien al contador
	void addAlien() { alienCount++; }

	// 'mata' al alien (resta al contador)
	void alienDied() { alienCount--; };

	// devuelve la cantidad de aliens que quedan
	int getAlienCount() { return alienCount; };

	// devuelve el estado del mvimiento
	int getCurrentState() { return currentState; };

	// devuelve si se sigue moviendo o no
	bool shouldMove();
	
	// cambia la direccion actual de los aliens
	void cannotMove();

	// devuelve si han llegado al suelo o no (se acaba partida))
	void alienLanded(const Alien* alien);

	// INFORMAN AL JUEGO
	// consecuencias de haber aterrizado
	void haveLanded();

	

};
#endif