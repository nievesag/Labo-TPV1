#include "PlayState.h"
#include "checkML.h"
#include "SDLApplication.h"

void PlayState::update()
{
	//
	cout << "update" << endl;

	//bucle for each para recorrer los objetos de la lista sceneObjectsList:
	//		-> tipo del objeto (& porque CREO que devuelve un puntero CREO) a : lista
	for (SceneObject& a : sceneObjectsList) {
		a.update();
	}

	// tambien se puede hacer con un iterador:
	// AHORA MISMO NO VA CON ITERADORES (SI LO DESCOMENTAS DA ERROR) PEROÇ
	// QUIERO SACARLO CON ITERADORES IGUAL
	// for(GameList<SceneObject, true>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++)

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
