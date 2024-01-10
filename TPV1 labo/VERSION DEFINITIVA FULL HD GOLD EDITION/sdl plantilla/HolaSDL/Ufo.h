#ifndef UFO_H
#define UFO_H

#include "checkML.h"

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Laser.h"

class PlayState;

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
		minCD = 1,		// minimo y maximo cooldown
		maxCD = 5;		

	// gestion de animacion de la explosion
	int animTimer = 10;
	int frame = 0;

	int vel = 1;

	Point2D<double> spawn; // punto de spawn

	int UfoScore = 100;

	int rewardProb; // probabilidad de soltar reward

	// metodos publicos
public:
	// ---- constructora ----
	Ufo(Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
		: spawn(position), SceneObject(position, width, height, vidas, texture, game)
	{
		state = oculto;
		hits = 0;

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

	// ---- save ----
	// guarda objeto
	void save(std::ostream& out) const override;

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