#include "Game.h"

struct TextureSpec
{
	const char* url;
	// width height
	int nw, nh;
};



// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"",0,0},
	{}

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

void Game::textureArray()
{
	// ----------- ALIEN 1 ------------
	textureSpec[Alien1].url = "";
	textureSpec[Alien1].nw = 0;
	textureSpec[Alien1].nh = 0;



}

void Game::loadTextures()
{


}
