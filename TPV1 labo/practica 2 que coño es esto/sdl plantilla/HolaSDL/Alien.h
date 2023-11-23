#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>
//#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"


class Mothership;
class Game;

using namespace std;
using uint = unsigned int;

class Alien : public SceneObject
{
	// atributos privados
private:
	Mothership* mothership;	  // puntero a mothership

	// tipo de alien
	int type;

	// frame del alien (para animaciones)
	int alienFrame;

	// metodos publicos 
public:
	// ---- constructora ----
	Alien(Mothership* mothership, int alienFrame, int type, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		:mothership(mothership), alienFrame(alienFrame), type(type), SceneObject(position, width, height, vidas, texture, game) { }

	//Alien() {} // constructora vacia

	// aqui si van los overrides porque aqui se especifican las cositas
	//
	void render() const override;

	//
	void update() override;

	//
	void save(ostream&) const override;

};
#endif