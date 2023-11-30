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

	// metodos publicos
public:
	// ---- constructora ----
	Ufo(int estado, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: estado(estado), SceneObject(position, width, height, vidas, texture, game)
	{
		// inicializa a oculto al construirse??????????
		estado = oculto;
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

	// ---- save ----
	// guarda objeto
	void save(ostream&) const override;

protected:
	// ---- move ----
	// mueve el ufo
	void move();

};
#endif