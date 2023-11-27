#ifndef LASER_H
#define LASER_H

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"

// PLACEHOLDERRRRR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//#include "Game.h"

class Game;

using namespace std;
using uint = unsigned int;

class Laser : public SceneObject
{
	// atributos privados
private:
	// rojo si viene de la nave
	// azul si viene de los aliens
	// antiguo frenemy -> mejor char????
	enum frenemy{ rojo, azul };

	char laserType;

	Vector2D<double> vel;

	bool alive;

	int cooldown;

	// metodos publicos 
public:
	// ---- constructora ----
	Laser(char type, Vector2D<double> velocity, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: laserType(type), vel(velocity), SceneObject(position, width, height, vidas, texture, game)
	{ 
		// inicializa alive a true al construirse
		alive = true;
	};

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	// devuelve si esta fuera del marco de juego 
	bool isOut();

	// devuelve si esta vivo el laser
	bool IsAlive() { return alive; }

	char getColor() { return laserType; };

	void writeName() override {
		//cout << "laser" << endl;
	}

protected:
	// mueve el laser segun el vector velocidad
	void move();

	// actualiza el rect
	virtual void updateRect() override;

	// maneja el cooldown
	void coolDownManagement();
};

#endif