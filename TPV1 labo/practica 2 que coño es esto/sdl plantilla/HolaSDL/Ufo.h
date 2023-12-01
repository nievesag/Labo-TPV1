#ifndef UFO_H
#define UFO_H

#include "checkML.h"
#include <SDL.h>
// ----------------------------------
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Laser.h"

// PLACEHOLDERRRRR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Game;

using namespace std;
using uint = unsigned int;

enum estado { visible, oculto, destruido };

class Ufo : public SceneObject
{
	// atributos privados
private:
	int estado;
	int hits;
	int ufoFrame; // frame del ufo (para animaciones)

	// cooldown de aparicion
	double cooldown,	// cooldown de aparicion
		CDcounter,		// contador de cooldown de aparicion
		minCD, maxCD;	// minimo y maximo cooldown

	Vector2D<double> vel;

	// metodos publicos
public:
	// ---- constructora ----
	Ufo(double minCD, double maxCD, int estado, Vector2D<double> velocity, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: minCD(minCD), maxCD(maxCD), estado(estado), vel(velocity), SceneObject(position, width, height, vidas, texture, game)
	{
		// inicializa a oculto al construirse??????????
		//estado = oculto;
		setCD();
	};

	// ---- render ----
	// renderiza
	void render() const override;

	// ---- update ----
	// actualiza
	void update() override;

	void updateState();

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	// el ufo aparece
	void appear();

	// gestiona el cooldown de aparicion
	void manageCooldown();

	// settea cooldown del ufo
	void setShowCD(double newCD) { cooldown = newCD; }

	void setCD();

	// ---- save ----
	// guarda objeto
	void save(ostream&) const override;

protected:
	// ---- move ----
	// mueve el ufo
	void move();

	// actualiza el rect
	void updateRect() override;
};
#endif