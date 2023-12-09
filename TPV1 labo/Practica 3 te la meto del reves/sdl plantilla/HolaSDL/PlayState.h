#ifndef PLAYSTATEQ_H
#define PLAYSTATE_H

// includes
#include <SDL.h>

// 
#include "GameState.h"

using namespace std;
using uint = unsigned int;

class PlayState : public GameState{

protected:

	// ??????????????????

public:

	// collisiones
	void damage(SDL_Rect rect, char frenemy);

	// genera un int aleatorio con un minimo y un maximo
	int getRandomRange(int min, int max);

	// guatafac
	//void hasDied(GameList<SceneObject>::anchor);




};

#endif