#include "Game.h"

struct TextureSpec
{
	const char* url;
	// width height
	int nw, nh;
};

// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"..\Invasores del espacio\SpaceInvaders\images\aliens.png", 32, 32},  // alien 1
	{ "..\Invasores del espacio\SpaceInvaders\images\aliens.png", 44, 32 },			  // alien 2
	{ "..\Invasores del espacio\SpaceInvaders\images\aliens.png", 48, 32 },			  // alien 3
	{ "..\Invasores del espacio\SpaceInvaders\images\spaceship.png", 34, 21 },		  // nave
	{ "..\Invasores del espacio\SpaceInvaders\images\bunker.png", 88, 57 }			  // bunker
		// !!!! usar texture root (LEER ENUNCIADO)
};

// constructora

Game::Game()
{
	int winX, winY; // Posición de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("boo", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game()
{
	// memoria dinamica que borrar creo
	// SDL_DestroyRenderer(renderer);
	// da error por razones que desconzco
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	SDL_Quit(); // cierra pantalla
}


void Game::loadTextures()
{
	SDL_Texture* tex = nullptr;
	SDL_Surface* surface = nullptr; // leer
	for (int i = 0; i < NUM_TEXTURES; i++) {

		// pasar url load etc noscuantitos como diaria ines
		// surface = 

		//
		tex = SDL_CreateTextureFromSurface(renderer, surface);


	}

}
