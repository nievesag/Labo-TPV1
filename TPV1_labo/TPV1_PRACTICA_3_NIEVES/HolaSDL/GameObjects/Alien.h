#ifndef ALIEN_H
#define ALIEN_H

#include "../checkML.h"
#include <SDL.h>

#include "../Vector2D.h"
#include "../texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Laser.h"
#include "Mothership.h"

class Mothership;
class SDLApplication;
class PlayState;

class Alien : public SceneObject
{
private:
	int score1 = 10, score2 = 20, score3 = 30;

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
	Alien(Mothership* mothership, int alienFrame, int type, Point2D<double> position, int width, 
		int height, int vidas, Texture* texture, PlayState* game);

	// ---- render ----
	// renderiza
	void render() const override;

	// ---- update ----
	// actualiza
	virtual void update() override;

	// ---- save ----
	// guarda objeto
	virtual void save(std::ostream& out) const override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, Weapon* frenemy) override;

	// anyade el mothership al alien
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