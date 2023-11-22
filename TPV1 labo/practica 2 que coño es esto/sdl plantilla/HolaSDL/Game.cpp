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

	cout << "AAAAAAAAAA" << endl;

}

Game::~Game()
{
	// limpia elementos de juego
	//
	cout << "aaaaaa" << endl;

	// limpia las texturas
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); // cierra pantalla


}

void Game::run()
{

	while (!exit) {

		
		render(); // actualiza todos los objetos de juego
	}
		


}

void Game::update()
{


}

void Game::render()
{
	// limpia pantalla
	SDL_RenderClear(renderer);

	// render del fondo
	renderBackground();

	// iterador para renderizar los objetos
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		(*it)->render();
	}

	// render de todo
	SDL_RenderPresent(renderer);
}


void Game::EndGame()
{
	exit = true;
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
		Point2D<double> coord(x, y);

		// si es la nave
		if (type == 0) {

			// nave
		}
		// si es un alien
		else if (type == 1) {
			in >> atype;

			// crea un alien
			//Alien* alien = new Alien(milfship, 0, 0, coord, 1, 1, 2, textures[atype], this);

			// simplificado asi, si da problemas lo ponemos por separado el SceneObject* obj = alien;
			//                     mothership  frame type position             width                            height            lifes    texture        game
			SceneObject* obj = new Alien(milfship, 0, atype, coord, textures[atype]->getFrameWidth(), textures[atype]->getFrameHeight(), 2, textures[atype], this);

			sceneObjectsList.push_back(obj);

		}
		// si es un bunker
		else if (type == 2) {
			Vector2D<int> vel(0, 0);

			//bunker
		}
	}

}

void Game::renderBackground()
{
	// renderiza el fondo
	textures[Fondo]->render();
}
