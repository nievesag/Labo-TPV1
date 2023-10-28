#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Game.h"

using namespace std;

using uint = unsigned int;

void xd()
{
	
}

int main(int argc, char* argv[])
{
	// no hace borrarlo porque es estatico, se borra solo al salir de ambito (si fuese puntero: delete ay;)
	Game ay;

	ay.run();

	SDL_Delay(3000);

	return 69;
}
