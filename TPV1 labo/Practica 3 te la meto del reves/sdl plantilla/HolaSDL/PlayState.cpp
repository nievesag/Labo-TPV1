#include "PlayState.h"
#include "checkML.h"
#include "SDLApplication.h"

void PlayState::update()
{
	//
	cout << "update" << endl;

	// actualiza el mothership
	//mother->update();

	//bucle for each para recorrer los objetos de la lista sceneObjectsList:
	//		-> tipo del objeto (& porque CREO que devuelve un puntero CREO) a : lista
	for (SceneObject& a : sceneObjectsList) {
		a.update();
	}

	// tambien se puede hacer con un iterador:
	// AHORA MISMO NO VA CON ITERADORES (SI LO DESCOMENTAS DA ERROR) PEROÇ
	// QUIERO SACARLO CON ITERADORES IGUAL
	// for(GameList<SceneObject, true>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++)

	// borra los objetos a borrar
	//deleteSceneObjects();

}

void PlayState::render()
{
	//
	cout << "render" << endl;

	//bucle for each para recorrer los objetos de la lista sceneObjectsList:
	for (SceneObject& a : sceneObjectsList) {
		a.render();
	}
}

bool PlayState::onEnter()
{
	//
	
	std::cout << "entering PlayState\n";

	return true;
}

bool PlayState::onExit()
{
	cout << "exiting PlayState\n";
	return true;
}

string PlayState::getID() const
{
	return s_playID;
}

bool PlayState::damage(SDL_Rect rect, char frenemy)
{
	for (SceneObject a : sceneObjectsList) {

		// se ha pegado un hostion (colisiones)
		if (a.hit(&rect, frenemy)) {
			// devuelve si ha hitteado	
			return true;
		}
	}
	return false;
}

void PlayState::hasDied(GameList<SceneObject, true>::anchor i)
{
	// que cojones es un anchor ?????
	// aniade el objeto a la lista de borradores
	//objectsToErase.push_back(i);

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

	// lo mete en la lista:
	// cuando se añade a la lista un objeto, le asigna directamente el anchor (entiendo que es un iterador
	// pero estatico ??? tipo no se mueve) para luego poder usarlo en eliminaciones de objetos.
	sceneObjectsList.push_back(newObj);
}

void PlayState::deleteSceneObjects()
{
}
