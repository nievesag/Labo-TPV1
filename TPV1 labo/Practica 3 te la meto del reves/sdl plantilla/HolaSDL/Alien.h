#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Laser.h"
#include "Mothership.h"

class Mothership;
class SDLApplication;

using namespace std;
using uint = unsigned int;

class Alien : public SceneObject
{
	// atributos privados
protected:
	Mothership* mothership;	  // puntero a mothership
	int type;			// tipo de alien
	int alienFrame;		// frame del alien (para animaciones)
	double alienSpeed;  // velocidad del alien

	int alienScore;

	int initialY;

	// metodos publicos 
public:
	// ---- constructora ----
	Alien(Mothership* mothership, int alienFrame, int type, Point2D<double> position, int width, int height, int vidas, Texture* texture, SDLApplication* application)
		: mothership(mothership), alienFrame(alienFrame), type(type), SceneObject(position, width, height, vidas, texture, application) 
	{ 
		setAlienSpeed();

		initialY = position.getY();

		if (type == 0) alienScore = 30;
		else if (type == 1) alienScore = 20;
		else if (type == 2) alienScore = 10;
		else alienScore = 0;
	}

	// ---- render ----
	// renderiza
	void render() const override;

	// ---- update ----
	// actualiza
	virtual void update() override;

	// ---- save ----
	// guarda objeto
	virtual void save(ostream& out) const override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	// añade el mothership al alien
	void setMothership(Mothership* mother) { mothership = mother; };

	// metodos privados (auxiliares)
protected:
	// ---- animate ----
	// anima al alien
	void animate();

	void updateRect() override;

	// devuelve el numero de puntuacion a añadir segun el tipo de alien
	int GetAlienPoints() const { return alienScore; }

	void setAlienSpeed();
};
#endif