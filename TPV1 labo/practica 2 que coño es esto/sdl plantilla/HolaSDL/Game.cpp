#include "checkML.h"
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

void Game::run()
{


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

void Game::loadMap()
{
	// lee el mapa
	ifstream in("..\\mapas\\original.txt");
	if (in.fail()) throw ("No se ha podido leer mapa");

	// variables auxiliares
	int type;
	int x, y;
	int atype;

	// in.eof() devuelve si se ha acabado el fichero
	while (!in.eof()) {
		in >> type;
		in >> x;
		in >> y;
		Point2D<int> coord(x, y);

		// crea el mothership
		milfship = new Mothership(10, this);

		if (type == 0) {
			Vector2D<double> vel(0, 0);

			// crea un alien
			SceneObject* obj = new Alien(milfship, 0, 0, coord, 1, 1, 2, textures[0], this);

		}

		



		/*
		// si es la nave
		if (type == 0) {
			Vector2D<double> vel(0, 0);

			cannon = new Cannon(coord, textures[Nave], 1, laserCoolDown, vel, this);
		}
		// si es un alien
		else if (type == 1) {
			in >> atype;

			double min = getRandomRange(100, 150);
			double max = getRandomRange(290, 330);

			Alien* alien = new Alien(coord, textures[atype], atype, this, min, max);

			aliens.push_back(alien);
		}
		// si es un bunker
		else if (type == 2) {
			Vector2D<int> vel(0, 0);

			Bunker* bun = new Bunker(coord, textures[Escudo], textures[Escudo]->getNumColumns());

			bunkers.push_back(bun);
		}
		*/
		
}
