#include "Game.h"

using namespace std;

struct TextureSpec
{
	const char* url;

	// width height
	int nw, nh;
};

// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo TextureSpec 
array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"..\\images\\aliens2.png", 2, 3},	  // alien 1 // 32,32
	{ "..\\images\\aliens2.png", 2, 3 },			  // alien 2 // 44,32
	{ "..\\images\\aliens2.png", 2, 3 },			  // alien 3 // 48,32
	{ "..\\images\\spaceship.png", 1, 1},			  // nave	 // 34,21
	{ "..\\images\\bunker.png", 4, 1 },				  // bunker  // 88,57
	{ "..\\images\\stars.png", 1, 1 }
};

// constructora
Game::Game() : randomGenerator(time(nullptr))
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
}

// destructora
Game::~Game()
{
	// limpia elementos de juego
	for (int i = 0; i < aliens.size(); i++) delete aliens[i];
	for (int i = 0; i < bunkers.size(); i++) delete bunkers[i];
	for (int i = 0; i < laseres.size(); i++) delete laseres[i];
	delete cannon;

	// limpia las texturas
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); // cierra pantalla
}

#pragma region Logica de Juego
// ----- LOGICA DE JUEGO -----
// cargar | manejar eventos -> actualizar -> pintar -> manejar eventos etc

// indica que el juego ha terminado
void Game::EndGame()
{
	exit = true;
}

// CARGA
void Game::loadTextures()
{
	try {
	// bucle para rellenar el array de texturas
		for (int i = 0; i < NUM_TEXTURES; i++) {

			// crea la textura con el url, width y height
			Texture* tex = new Texture(renderer, textureSpec[i].url, textureSpec[i].nh, textureSpec[i].nw);

			// la mete en el array
			textures[i] = tex;
			if (textures[i] == nullptr) {
				cout << "Textura null";
			}
		}
	}
	catch (...) {
		cout << "Texura no encontrada";
		EndGame();
	}
}

void Game::loadMap()
{
	try {
		ifstream in("..\\mapas\\original.txt");
		if (in.fail())
		{
			throw ("No se ha podido leer mapa");
		}

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
		}
	}

	catch (...) {
		cout << "Error en la carga de mapas";
		EndGame();
	}
}

// RUN
void Game::run()
{
	// get ticks al inicio del bucle
	startTime = SDL_GetTicks();

	while (!exit) 
	{
		handleEvents();
		
		// tiempo desde ultima actualizacion
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime > TIME_BT_FRAMES) {
			update(true); // actualiza todos los objetos de juego
			startTime = SDL_GetTicks();
		}
		render(); // renderiza todos los objetos de juego
	}
}

// ACTUALIZAR 
void Game::update(bool damage)
{
	if (aliens.size() == 0) exit = true;

	// ----------------------------------- ALIEN -----------------------------------------
	for (int i = 0; i < aliens.size(); i++) {

		// si devuelve que esta muerto
		if (!aliens[i]->update(damage)) {
			
			// borra la memoria dinamica
			delete aliens[i];

			// lo quita del vector
			aliens.erase(aliens.begin()+i);
		}
	}

	// ------------------------------------CANNON -----------------------------------------
	if (!cannon->update(damage)) {
		EndGame();
		cout << "GAME OVER" << endl;
	}

	// ----------------------------------- BUNKER -----------------------------------------
	for (int i = 0; i < bunkers.size(); i++) {

		// si ha detectado que esta muerto
		if (!bunkers[i]->update()) {
			
			// borra la memoria dinamica
			delete bunkers[i];
			
			// elimina el laser del vector de laseres
			bunkers.erase(bunkers.begin() + i);
		}
	}

	// ----------------------------------- LASER -----------------------------------------
	for (int i = 0; i < laseres.size(); i++) {
		
		// si ha detectado que esta muerto
		if (laseres[i]->update(damage) || !laseres[i]->IsAlive()) {

			// variable auxiliar para guardar el laser
			Laser* deadlaser = laseres[i];

			// borra la memoria dinamica
			delete laseres[i];

			// elimina el laser del vector de laseres
			laseres.erase(laseres.begin() + i);
		}
	}
}

// PINTAR
void Game::render()
{
	// limpia pantalla
	SDL_RenderClear(renderer);

	// render del fondo
	renderBackground();

	// render de los aliens
	for (int i = 0; i < aliens.size(); i++)
		aliens[i]->render();

	// render del cannon
	cannon->render();

	// render del bunker
	for (int i = 0; i < bunkers.size(); i++)
		bunkers[i]->render();

	// render del laser
	for (int i = 0; i < laseres.size(); i++)
		laseres[i]->render();

	// render de todo
	SDL_RenderPresent(renderer);
}

void Game::renderBackground()
{
	// renderiza el fondo
	textures[Fondo]->render();
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
		if (event.type == SDL_QUIT) EndGame();

		// MANEJO DE EVENTOS DE OBJETOS DE JUEGO
		else { cannon->handleEvents(event); }
	}
}
#pragma endregion

// devuelve la direccion
int Game::getDirection() { return alienDir; }	

// cambia la direccion
void Game::cannotMove() {

	alienDir = -alienDir;

	for (int i = 0; i < aliens.size(); i++) {
		aliens[i]->lowerAlien();
	}
}

// crea un laser
void Game::fireLaser(Point2D<double> pos, Vector2D<double> vel, bool frenemy)
{
	// en el vector de laseres: inserta un &laser al final
	laseres.push_back(new Laser(pos, vel, frenemy, this));
}

// DETECCION DE COLISIONES
bool Game::checkColision(Laser* laser)
{
	int i = 0;
	bool collision = false;

	// COLISIONES CON ALIENS
	// si el laser es de la nave
	if (laser->getFrenemy()) {

		// recorre todos los aliens que hay
		while (i < aliens.size() && !collision) {

			// si se intersecciona el laser con un alien
			if (SDL_HasIntersection(aliens[i]->getRect(), laser->getRect())) {
				
				// marca la colision como que ha colisionado
				collision = true;

				// le dice al alien que le han dado
				aliens[i]->hit();
			}
			i++;
		}
	}

	// COLISIONES CON CANNON
	// si el laser es del alien
	else {
		// si se intersecciona el laser con un alien
		if (SDL_HasIntersection(cannon->getRect(), laser->getRect())) {

			// le dice a la nave que le han dado
			cannon->hit();
		}
	}

	// reinicia el contador
	i = 0;

	// COLISIONES CON OTRO LASER
	// recorre los lasers
	while (i < laseres.size() && !collision) {

		// si colisiona con otro laser y es de diferente origen
		if (SDL_HasIntersection(laser->getRect(), laseres[i]->getRect()) 
			&& laser->getFrenemy() == !laseres[i]->getFrenemy()) {

			collision = true;

			// le dice a los laseres que le han dado
			laseres[i]->hit();
		}
		i++;
	}

	// reinicia el contador
	i = 0;

	// COLISIONES CON BUNKERS
	// recorre los bunkers
	while (i < bunkers.size() && !collision) {

		// si colisiona con un bunker
		if (SDL_HasIntersection(bunkers[i]->getRect(), laser->getRect())) {

			collision = true;

			// le dice a los bunkeres que le han dado
			bunkers[i]->hit();
		}
		i++;
	}
	return collision;
}
