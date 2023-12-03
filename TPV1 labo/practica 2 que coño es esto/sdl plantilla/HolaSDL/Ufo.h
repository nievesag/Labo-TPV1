#ifndef UFO_H
#define UFO_H

#include "checkML.h"

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Laser.h"

class Game;

using namespace std;
using uint = unsigned int;


class Ufo : public SceneObject
{
	// atributos privados
private:
	enum estado { visible, oculto, destruido };
	int hits;
	int ufoFrame; // frame del ufo (para animaciones)
	estado state;

	// cooldown de aparicion
	double cooldown,	// cooldown de aparicion
		CDcounter,		// contador de cooldown de aparicion
		minCD, maxCD;	// minimo y maximo cooldown

	// gestion de animacion de la explosion
	int animTimer = 10;
	int frame = 0;

	int vel = 1;

	Point2D<double> spawn;

	int UfoScore = 100;

	// metodos publicos
public:
	// ---- constructora ----
	Ufo( Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: spawn(position), SceneObject(position, width, height, vidas, texture, game)
	{
		state = oculto;

		setCD();
	};

	// ---- render ----
	// renderiza
	void render() const override;

	// ---- update ----
	// actualiza
	void update() override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	// el ufo aparece
	void appear();

	// el ufo desapaece
	void disappear();

	// el ufo muere
	void die();

	// gestiona el cooldown de aparicion
	void manageCooldown();

	// settea cooldown del ufo
	void setShowCD(double newCD) { cooldown = newCD; }

	void setCD();

	void setInitialCD();

	// ---- save ----
	// guarda objeto
	void save(ostream& out) const override;

	// devuelve si esta fuera del marco de juego 
	bool isOut();

protected:
	// ---- move ----
	// mueve el ufo
	void move();

	// actualiza el rect
	void updateRect() override;

	// animacion del ufo
	void anima();
};
#endif