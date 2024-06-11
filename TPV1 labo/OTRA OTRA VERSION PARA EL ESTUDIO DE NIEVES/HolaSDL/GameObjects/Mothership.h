#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#include "GameObject.h"
#include "Alien.h"

class Alien;
class PlayState;
class GameState;

class Mothership : public GameObject
{
	// atributos privados
private:
	// enum ciclico de estados
	enum state : int { RIGHT, dRIGHT, LEFT, dLEFT };

	// estado actual del movimiento de los aliens
	state currentState;

	// direction 
	int dir;

	// si debe cambiar de direccion
	bool switchDir;

	// offset del descenso
	int level;

	// tiempo para los updates
	int alienTimer;

	// contador de aliens
	int alienCount;

	// 
	PlayState* playState_ = nullptr;

	// ---- kamikaze ----
	double rndPos;
	int rndCooldown;
	int CDcounter;

	Point2D<double> kPos;

	// metodos publicos
public:
	Mothership(int level, PlayState* playState, int alienTimer, int n);
		
	// actualiza mothership
	void update() override;

	// guarda mothership
	void save(std::ostream& out) const override;

	// ajusta la direccion de los aliens
	int getDirection() const;

	// acceso al nivel
	int getLevel() const { return level; }

	// añade alien al contador
	void addAlien() { 
		alienCount++; }

	// 'mata' al alien (resta al contador)
	void alienDied() { alienCount--; }

	// devuelve la cantidad de aliens que quedan
	int getAlienCount() const { return alienCount; }

	// devuelve el estado del mvimiento
	int getCurrentState() const { return currentState; }

	// devuelve si se sigue moviendo o no
	bool shouldMove() const;
	
	// cambia la direccion actual de los aliens
	void cannotMove();

	// devuelve si han llegado al suelo o no (se acaba partida)
	void alienLanded(const Alien* alien);

	// INFORMA AL JUEGO
	// consecuencias de haber aterrizado
	void haveLanded();

	void setTimeCD();
	void setPosCD();

	void generateKamikaze();
};
#endif