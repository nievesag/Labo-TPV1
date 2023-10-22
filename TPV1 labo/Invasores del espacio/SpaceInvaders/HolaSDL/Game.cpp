#include "Game.h"


// constructora

Game::Game()
{
	int winX, winY; // Posición de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);

	//
	window = SDL_CreateWindow("boo", winX, winY,
		winWidth, winHeight, SDL_WINDOW_SHOWN);

	//renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	// error
	if (window == nullptr ) {
		cout << "Error cargando SDL" << endl;
	}
		
	// 
	else {
		// rgba (rgb con transparencia
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
	}
	

}

Game::~Game()
{
	
	// memoria dinamica que borrar creo
	//SDL_DestroyRenderer(renderer);
	// da error por razones que desconzco
	SDL_DestroyWindow(window);
	

}
