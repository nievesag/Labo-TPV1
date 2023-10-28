#include "Game.h"

using namespace std;

struct TextureSpec
{
	const char* url;

	// width height
	int nw, nh;
};

// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo TextureSpec 
// !!!! usar texture root (LEER ENUNCIADO)
array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"..\\images\\aliens.png", 32, 32},	  // alien 1
	{ "..\\images\\aliens.png", 44, 32 },			  // alien 2
	{ "..\\images\\aliens.png", 48, 32 },			  // alien 3
	{ "..\\images\\spaceship.png", 34, 21 },		  // nave
	{ "..\\images\\bunker.png", 88, 57 }			  // bunker
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

	loadTextures();

	// placeholder para hacer la nave
	Point2D<int> coord(400,500);
	Vector2D<int> vel(1,0);

	cannon = new Cannon(coord, textures[Nave], 1, 10, vel);

	

}

// destructora
Game::~Game()
{
	// memoria dinamica que borrar creo
	// SDL_DestroyRenderer(renderer);
	// da error por razones que desconzco
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	SDL_Quit(); // cierra pantalla
}

void Game::run()
{
	render();


}

void Game::render()
{

	cannon->render();

	SDL_RenderPresent(renderer);
}

void Game::loadTextures()
{
	// bucle para rellenar el array de texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {

		// crea la textura con el url, width y height
		Texture* tex = new Texture(renderer, textureSpec[i].url, textureSpec[i].nh, textureSpec[i].nw);

		// la mete en el array
		textures[i] = tex;
	}
}

