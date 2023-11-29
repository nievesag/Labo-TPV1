#ifndef UFO_H
#define UFO_H

#include "SceneObject.h"

using namespace std;
using uint = unsigned int;

enum estado { visible, oculto, destruido };

class Ufo : public SceneObject
{
	// atributos privados
private:
	int estado;
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
	virtual void update() override;

	// ---- save ----
	// guarda objeto
	void save(ostream&) const override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

};
#endif