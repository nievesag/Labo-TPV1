#include "checkML.h"
#include "SceneObject.h"

void SceneObject::render() const {}

void SceneObject::update() {}

void SceneObject::save(ostream& out) const {
	
	//  guarda la posicion (comun para todos)
	out << round(position.getX()) << " " << round(position.getY()) << " ";
}

bool SceneObject::hit(SDL_Rect* ataque, char frenemy) { return false; }

void SceneObject::updateRect() {}

SDL_Rect SceneObject::getRect()
{
	SDL_Rect rect;

	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = width;
	rect.h = height;

	return rect;
}