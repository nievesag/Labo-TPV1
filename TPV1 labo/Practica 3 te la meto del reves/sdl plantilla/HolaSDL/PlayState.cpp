#include "PlayState.h"


int PlayState::getRandomRange(int min, int max)
{
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

bool PlayState::damage(SDL_Rect rect, char frenemy)
{
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		// se ha pegado un hostion (colisiones)
		if ((*it)->hit(&rect, frenemy)) {
			// devuelve si ha hitteado	
			return true;
		}
	}
	return false;

}

void PlayState::hasDied(GameList<SceneObject>::anchor i)
{
	// aniade el objeto a la lista de borradores
	//objectsToErase.push_back(it);

}

void PlayState::fireLaser(Point2D<double> pos, char frenemy)
{

	if (frenemy == 'a') {
		SDL_SetRenderDrawColor(app->getRenderer(), 255, 0, 114, 255);	// cannon
	}
	else {
		SDL_SetRenderDrawColor(app->getRenderer(), 255, 242, 0, 255);	// aliens
	}

	// crea el laser
	SceneObject* newObj = new Laser(frenemy, pos, defaultLaserW, defaultLaserH, defaultLives, nullptr, app);

	// lo mete en la lista
	sceneObjectsList.push_back(newObj);

	//iterador al final de la lista
	list<SceneObject*>::iterator newit = sceneObjectsList.end();

	newit--;

	// le pasa el iterador
	newObj->setListIterator(newit);
}
