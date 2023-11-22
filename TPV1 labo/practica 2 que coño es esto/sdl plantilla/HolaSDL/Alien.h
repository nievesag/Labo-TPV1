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


	// metodos publicos 
public:
	// ---- constructora ----

	Alien(Mothership* mothership, int type, SDL_Rect destRect, Point2D<int> position, int width, int height, int vidas, Texture* texture, Game* game)
		:mothership(mothership), type(type), SceneObject(destRect, position, width, height, vidas, texture, game) { }


	// aqui si van los overrides porque aqui se especifican las cositas
	//
	virtual void render(SDL_Rect destRect) const override;

	//
	virtual void update() override;

	//
	virtual void save(ostream&) const override;

};
#endif