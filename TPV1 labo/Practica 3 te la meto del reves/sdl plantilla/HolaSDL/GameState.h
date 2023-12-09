#ifndef GAMESTATE_H
#define GAMESTATE_H

using namespace std;
using uint = unsigned int;

// includes
#include <SDL.h>		// SDL
#include <fstream>		// stream

// 
#include "gameList.h"
#include "SceneObject.h"

class Game;


class GameState {


protected:
	// referencia al game
	Game* game;

public:

	// render del estado
	void render() const;

	//
	void update();

	// 
	void handleEvent(const SDL_Event& event);

	//
	void save(ostream& file);

	// comento porque esta incompleta
	void hasDied(GameList<GameObject, true>::anchor);

	// getter del juego
	Game getGame() const;






};

#endif