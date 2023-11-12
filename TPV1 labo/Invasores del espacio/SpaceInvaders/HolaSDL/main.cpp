#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Game.h"

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	// no hace borrarlo porque es estatico, se borra solo al salir de ambito (si fuese puntero: delete ay;)
	Game game;

	game.run();

	return 69;
}
