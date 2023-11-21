#include "Game.h"


using namespace std;

struct TextureSpec
{
	const char* url;

	// width height
	int nw, nh;
};


// ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ PLACEHOLDERRRRRRRRRRRRRRRRRRR !!!!!!!!!!!!!!!!!!!
// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo TextureSpec 
array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"..\\images\\aliens2.png", 2, 3},	  // alien 1 // 32,32
	{ "..\\images\\aliens2.png", 2, 3 },			  // alien 2 // 44,32
	{ "..\\images\\aliens2.png", 2, 3 },			  // alien 3 // 48,32
	{ "..\\images\\spaceship.png", 1, 1 },			  // nave	 // 34,21
	{ "..\\images\\bunker.png", 4, 1 },				  // bunker  // 88,57
	{ "..\\images\\stars.png", 1, 1 }
};


// constructora del game
Game::Game()
{
	int winX, winY; // Posición de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);

	// ERRORES DE SDL
	try {
		// crea la ventana
		window = SDL_CreateWindow("Space Invaders", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);

		// crea el renderer para la ventana
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (window == nullptr || renderer == nullptr)
			throw "Error cargando ventana de juego o renderer"s;
	}
	catch (...) {
		cout << "Error cargando ventana de juego o renderer";
		EndGame();
	}

	loadTextures();

	loadMap();


	// TODO: papopepo
}

void Game::loadTextures()
{
	// bucle para rellenar el array de texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {

		// crea la textura con el url, width y height
		Texture* tex = new Texture(renderer, textureSpec[i].url, textureSpec[i].nh, textureSpec[i].nw);

		// la mete en el array
		textures[i] = tex;
		if (textures[i] == nullptr) {
			// throwea algo en concreto
			// ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ esto es un throweo generico (es un placeholder) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			throw "uwu";
		}
	}
}
