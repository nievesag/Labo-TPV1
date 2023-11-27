#include "SceneObject.h"


void SceneObject::render() const
{
}

bool SceneObject::update()
{
	return false;
}

void SceneObject::save(ostream&) const
{
}

bool SceneObject::hit(SDL_Rect* ataque, char frenemy)
{
	return false;
}

