#include "PlayState.h"


void PlayState::update()
{
	// actualiza el mothership
	//mother->update();

	// actualiza los objetos de escena
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		(*it)->update();
	}

	// borra los objetos a borrar
	deleteSceneObjects();

}

void PlayState::render()
{
	// limpia pantalla
	SDL_RenderClear(app->getRenderer());

	// render del fondo
	//renderBackground();

	// iterador para renderizar los objetos
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		(*it)->render();
	}

	// render de todo
	SDL_RenderPresent(app->getRenderer());

}

void PlayState::save(const ostream& file)
{
	// da error por razones que desconozco
	/*
	// abre un canal para guardar en un archivo con el nombre deseado
	ofstream out(file + ".txt"); // SAVED_FOLDER + 

	//mother->save(out);

	// bucle para llegar a los save de todos los objetos
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		(*it)->save(out);
	}

	// guarda los puntos
	out << "7 " << SCORE << endl;

	// cierra el hilo
	out.close();
	*/

}

bool PlayState::onEnter()
{
	cout << "entering PlayState\n";
	return true;

	return false;
}

bool PlayState::onExit()
{

	cout << "exiting PlayState\n";
	return true;
	return false;
}

string PlayState::getID() const
{
	return s_playID;
}

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

void PlayState::deleteSceneObjects()
{
	if (objectsToErase.size() > 0) {

		// bucle para borrar los objetos que han de ser borrados
		for (auto a : objectsToErase) {

			// borramos el objeto
			delete (*a);

			// lo borra de la lista
			sceneObjectsList.erase(a);
		}
		objectsToErase.clear();
	}
}
