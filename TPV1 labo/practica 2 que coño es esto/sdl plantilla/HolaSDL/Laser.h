#ifndef LASER_H
#define LASER_H

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"

using namespace std;
using uint = unsigned int;

class Laser : SceneObject
{
	// atributos privados
private:
	// rojo si viene de la nave
	// azul si viene de los aliens
	// antiguo frenemy -> mejor char????
	enum { rojo, azul };

	Vector2D<double> vel;

	bool alive;

	// metodos publicos 
public:
	// ---- constructora ----
	Laser(Vector2D<double> velocity, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: vel(velocity), SceneObject(position, width, height, vidas, texture, game)
	{ 
		// inicializa alive a true al construirse
		alive = true;
	};

	// ---- render ----
	void render() const override;

	// ---- update ----
	bool update() override;

	// ---- hit ----
	// recibir daño
	//void hit() override;

	// devuelve si esta fuera del marco de juego 
	bool isOut();

	// devuelve si esta vivo el laser
	bool IsAlive() { return alive; }

protected:
	// mueve el laser segun el vector velocidad
	void move();

};

#endif