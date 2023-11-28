#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>
// ----------------------------------
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Laser.h"
#include "Mothership.h"

// PLACEHOLDERRRRR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



class Mothership;
class Game;

using namespace std;
using uint = unsigned int;

class Alien : public SceneObject
{
	// atributos privados
private:
	Mothership* mothership;	  // puntero a mothership
	int type; // tipo de alien
	int alienFrame; // frame del alien (para animaciones)
	double alienSpeed; // velocidad del alien

	// metodos publicos 
public:
	// ---- constructora ----
	Alien(Mothership* mothership, int alienFrame, int type, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: mothership(mothership), alienFrame(alienFrame), type(type), SceneObject(position, width, height, vidas, texture, game) 
	{ 
		alienSpeed = 0.1;
	}

	// ---- render ----
	// renderiza
	void render() const override;

	// ---- update ----
	// actualiza
	virtual void update() override;

	// ---- save ----
	// guarda objeto
	void save(ostream&) const override;

	// ---- lowerAlien ----
	// baja al alien
	void lowerAlien();

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	void writeName() override {
		cout << &it << endl;
	}

	// metodos privados (auxiliares)
protected:
	// ---- move ----
	// mueve al alien
	void move();

	// ---- animate ----
	// anima al alien
	void animate();

	//
	void updateRect() override;
};
#endif