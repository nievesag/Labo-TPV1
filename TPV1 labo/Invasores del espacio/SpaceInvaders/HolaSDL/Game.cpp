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
	TextureSpec{"..\\images\\aliens2.png", 2, 3},	  // alien 1 // 32,32
	{ "..\\images\\aliens2.png", 2, 3 },			  // alien 2 // 44,32
	{ "..\\images\\aliens2.png", 2, 3 },			  // alien 3 // 48,32
	{ "..\\images\\spaceship.png", 1, 1},		  // nave	 // 34,21
	{ "..\\images\\bunker.png", 4, 1 }			  // bunker  // 88,57
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

	loadMap();
	
}

// destructora
Game::~Game()
{
	// limpia las texturas
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); // cierra pantalla
}


// ----- LOGICA DE JUEGO -----
// cargar | manejar eventos -> actualizar -> pintar -> manejar eventos etc
// CARGA
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

void Game::loadMap()
{
	ifstream in("..\\mapas\\original.txt");
	int type;
	int x, y;
	int atype;

	// in.eof() devuelve si se ha acabado el fichero
	while (!in.eof()) {
		in >> type;
		in >> x;
		in >> y;
		Point2D<int> coord(x, y);

		// si es la nave
		if (type == 0) {
			Vector2D<int> vel(0, 0);

			cannon = new Cannon(coord, textures[Nave], 1, 10, vel, this);
		}
		// si es un alien
		else if (type == 1) {
			in >> atype;

			Alien* alien = new Alien(coord, textures[atype], 1, this);

			aliens.push_back(alien);
		}
		// si es un bunker
		else if (type == 2) {
			Vector2D<int> vel(0, 0);

			Bunker* bun = new Bunker(coord, textures[Escudo], 1);

			bunkers.push_back(bun);
		}
	}
}

// RUN
void Game::run()
{
	while (!exit) // Falta el control de tiempo
	{
		// !!!!!!!! no estoy segura de si se ejecuta handleEvents o update antes (así está en las diapos).
		handleEvents();
		update();
		render();

		// renderiza el juego
		render();
	}
}

// ACTUALIZAR 
void Game::update()
{
	// update de cada elemneto de juego
	cannon->update();
}

// PINTAR
void Game::render()
{
	// limpia pantalla
	SDL_RenderClear(renderer);

	// render de los aliens
	for (int i = 0; i < aliens.size(); i++)
		aliens[i]->render();

	// render del cannon
	cannon->render();

	// render del bunker
	for (int i = 0; i < bunkers.size(); i++)
		bunkers[i]->render();

	// render de todo
	SDL_RenderPresent(renderer);
}

// MANEJAR EVENTOS
void Game::handleEvents()
{
	SDL_Event event; // crea evento

	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) {

		// si se solicita quit bool exit = true
		if (event.type == SDL_QUIT) exit = true;

		// MANEJO DE EVENTOS DE OBJETOS DE JUEGO
		else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) { cannon->handleEvents(event); }
	}

	// update current frame + render current frame
}
