#include "SceneObject.h"

void SceneObject::render() const {}

void SceneObject::update() {}

void SceneObject::save(ostream& out) const {
	
	//  guarda la posicion (comun para todos)
	out << round(position.getX()) << " " << round(position.getY()) << " ";

}

bool SceneObject::hit(SDL_Rect* ataque, char frenemy) { return false; }

void SceneObject::updateRect() {}