// MEMORY LEAKS
#include "checkML.h"

// SDL
#include "SDL.h"
#include "SDL_image.h"

// AUX
#include <iostream>
#include <vector>

// GAME
#include "SDLApplication.h"

// ERRORES
#include "Errors/InvadersError.h"
#include "Errors/FileNotFoundError.h"
#include "Errors/SDLError.h"
#include "Errors/FileFormatError.h" 

using namespace std;

int main(int argc, char* argv[])
{
    try {
        // no hace falta borrarlo porque es estatico, se borra solo al salir de ambito
        SDLApplication application;
        application.run();
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