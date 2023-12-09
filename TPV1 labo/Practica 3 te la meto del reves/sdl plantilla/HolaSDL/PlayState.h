#ifndef PLAYSTATEQ_H
#define PLAYSTATE_H

// includes
#include <SDL.h>

// 
#include "GameState.h"
#include "gameList.h"
#include "SceneObject.h"

using namespace std;
using uint = unsigned int;

class PlayState : public GameState{

protected:

	// este es el nuevo game... pero que hace el atiguo ????

	// en Game: punteros a window y render
	//			array de texturas
	//			maquina de estados

public:

	// collisiones
	void damage(SDL_Rect rect, char frenemy);

	// genera un int aleatorio con un minimo y un maximo
	int getRandomRange(int min, int max);

	// guatafac
	void hasDied(GameList<SceneObject>::anchor);




};

#endif