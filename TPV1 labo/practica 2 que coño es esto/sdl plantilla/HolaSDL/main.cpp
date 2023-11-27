// MEMORY LEAKS
#include "checkML.h"

// SDL
#include "SDL.h"
#include "SDL_image.h"

// AUX
#include <iostream>
#include <Windows.h>
#include <vector>

// GAME
#include "Game.h"

using namespace std;
using uint = unsigned int;

int main(int argc, char* argv[])
{
    try {
        // no hace falta borrarlo porque es estatico, se borra solo al salir de ambito (si fuese puntero: delete ay;)
        Game game;
        game.run();
    }
    catch (exception& e) {

        cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

	return 69;
}