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

// ERRORES
#include "InvadersError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"
#include "FileFormatError.h" 

using namespace std;

int main(int argc, char* argv[])
{
    try {
        // no hace falta borrarlo porque es estatico, se borra solo al salir de ambito (si fuese puntero: delete ay;)
        Game game;
        game.run();
    }

    // ERROR DE SDL
    catch (SDLError& SDLError) {

        cout << SDLError.what() << endl;
    }

    // ERROR DE ARCHIVO NO ENCONTRADO
    catch (FileNotFoundError& FileNotFoundError) {
        cout << FileNotFoundError.what() << endl;
    }

    // ERROR DE FORMATO DE ARCHIVO
    catch (FileFormatError& FileFormatError) {
        cout << FileFormatError.what() << endl;
    }

    // ERROR GENERICO
    catch (...)
    {
        cout << "An error occurred, you can't play Space Invaders :(" << endl;
    }

	return 69;
}