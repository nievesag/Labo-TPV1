#include "checkML.h"
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
	{ "..\\images\\spaceship.png", 1, 1 },			  // nave	 // 34,21
	{ "..\\images\\bunker.png", 4, 1 },				  // bunker  // 88,57
	{ "..\\images\\stars.png", 1, 1 },				  // fondo 
	{ "..\\images\\ufo.png", 1, 2 }				      // ufo	 // 48,26
};

// constructora del game
Game::Game()
{
	int winX, winY; // Posición de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);

	// crea la ventana
	window = SDL_CreateWindow("Space Invaders", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);

	// crea el renderer para la ventana
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// ERRORES DE SDL
	if (window == nullptr || renderer == nullptr)
		throw "Error cargando ventana de juego o renderer"s;

	loadTextures();

	loadMap();
}

Game::~Game()
{
	// borra el mothership
	delete milfship;

	// limpia las texturas
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); // cierra pantalla
}

#pragma region LOGICA DE JUEGO
// ----- LOGICA DE JUEGO -----
// cargar | manejar eventos -> actualizar -> pintar -> manejar eventos etc

// ---------------------------------------------
void Game::EndGame()
{
	exit = true;
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
			update(); // actualiza todos los objetos de juego
			startTime = SDL_GetTicks();
		}

		render(); // renderiza todos los objetos de juego
	}
	
	// escribe gameover
	cout << "GAME OVER" << endl;
	// escribe punuacion
	PlayerScore();
}

// ACTUALIZAR 
void Game::update()
{
	// actualiza el mothership
	milfship->update();

	// actualiza los objetos de escena
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		(*it)->update();
	}

	// borra los objetos a borrar
	deleteSceneObjects();
}

// PINTAR
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

void Game::renderBackground()
{
	// renderiza el fondo
	textures[Fondo]->render();
}

// MANEJAR EVENTOS
void Game::handleEvents()
{
	SDL_Event event; // crea evento
	ifstream in("..\\mapas\\original.txt");
	int type;

	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) {

		// si se solicita quit bool exit = true
		if (event.type == SDL_QUIT) EndGame();

		// MANEJO DE EVENTOS DE OBJETOS DE JUEGO
		else { 
			// el objeto en begin es el cannon
			list<SceneObject*>::iterator it = sceneObjectsList.begin();

			// DYNAMIC CAST: se comprueba en ejecucion que el objeto 
			// en la posicion begin del iterador apunte a un objeto de tipo Cannon
			// si lo es se accede al metodo 
			dynamic_cast<Cannon*>(*it)->handleEvent(event);
		}
	}
}

// ELIMINACION DE OBJETOS
#pragma region ELIMINACION DE OBJETOS
void Game::deleteSceneObjects()
{
	if (objectsToErase.size() > 0) {

		//cout << "que hace esto aqui ¿?¿?¿?" << endl;

		// bucle para borrar los objetos que han de ser borrados
		for (auto a : objectsToErase) {

			//cout << "PERO ES QUE ENCIMA ENTRA ME MATO TIO" << endl;

			// FALTA CONTROL DE ITERATOR INVALIDO
			// nuevo iterator
			list<SceneObject*>::iterator newIt;

			//
			newIt = a;

			// borramos el objeto
			delete (*a);

			// lo borra de la lista
			sceneObjectsList.erase(a);
		}

		objectsToErase.clear();
	}
}

void Game::hasDied(list<SceneObject*>::iterator& it)
{
	// aniade el objeto a la lista de borradores
	objectsToErase.push_back(it);
}
#pragma endregion

// MANEJAR SCORE
void Game::increaseScore(int score)
{
	SCORE += score;
}

void Game::PlayerScore()
{
	cout << "SCORE: " << SCORE << endl;
}

// fin logica
#pragma endregion 

// CONTROL DE DAÑO
#pragma region CONTROL DE DAÑO
void Game::fireLaser(Point2D<double> pos, char frenemy)
{
	// settea la velocidad
	Vector2D<double> vel(0,1);

	if (frenemy == 'a') {
		SDL_SetRenderDrawColor(renderer, 255, 0, 114, 255);	// cannon

		vel.setY(1);
	}	
	else {
		SDL_SetRenderDrawColor(renderer, 255, 242, 0, 255);	// aliens

		vel.setY(-1);
	}
	
	// crea el laser
	SceneObject* newObj = new Laser(frenemy, vel, pos, 4, 10, 1, nullptr, this);

	// lo mete en la lista
	sceneObjectsList.push_back(newObj);

	//iterador al final de la lista
	list<SceneObject*>::iterator newit = sceneObjectsList.end();

	newit--;

	// le pasa el iterador
	newObj->setListIterator(newit);
}

bool Game::damage(Laser* myLaser)
{
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		// se ha pegado un hostion (colisiones)
		if ((*it)->hit(myLaser->getRect(), myLaser->getColor())) {
			// devuelve si ha hitteado	
			return true;
		}
	}
	return false;
}
#pragma endregion

// UFO
void Game::showUfo(Point2D<double> pos, int estate)
{
	/*
	// settea la velocidad
	Vector2D<double> vel(0, 1);
	double min = getRandomRange(2, 7);
	double max = getRandomRange(8, 15);

	SDL_SetRenderDrawColor(renderer, 255, 0, 114, 255);	// cannon

	vel.setX(-1);

	// crea el ufo
	SceneObject* newObj = new Ufo(min, max, vel, pos, textures[Ufo]->getFrameWidth(), textures[Ufo]->getFrameHeight(), 1, textures[Ufo], this);

	// lo mete en la lista
	sceneObjectsList.push_back(newObj);

	//iterador al final de la lista
	list<SceneObject*>::iterator newit = sceneObjectsList.end();
	
	newit--;

	// le pasa el iterador
	newObj->setListIterator(newit);
	*/
}

// CARGA
#pragma region LOADS
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
			// ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ esto es un throweo generico (es un placeholder)
			throw "uwu"s;
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

	// crea la mothership
	milfship = new Mothership(10, this, 30);

	// in.eof() devuelve si se ha acabado el fichero
	while (!in.eof()) {
		in >> type;
		in >> x;
		in >> y;
		Point2D<double> coord(x, y);

		// si es la nave
		if (type == 0) {

			// nave
			SceneObject* obj = new Cannon(200, coord, textures[Nave]->getFrameWidth(), textures[Nave]->getFrameHeight(), 1, textures[Nave], this);

			// lo mete en la lista
			sceneObjectsList.push_back(obj);

			//iterador al final de la lista
			list<SceneObject*>::iterator newit = sceneObjectsList.end();

			newit--;

			// le pasa el iterador
			obj->setListIterator(newit);
		}

		// si es un alien
		else if (type == 1) {
			in >> atype;

			SceneObject* obj;

			if (atype == 0) {

				double min = getRandomRange(2, 7);
				double max = getRandomRange(8, 15);

				//				 minCD(minCD), maxCD(maxCD)
				obj = new ShooterAlien(min, max, milfship, 0, atype, coord, textures[atype]->getFrameWidth(), textures[atype]->getFrameHeight(), 2, textures[atype], this);
			}
			else {
				// sobrecargas: Alien(mothership, frame, type, position, width, height, lifes, texture, game)
				obj = new Alien(milfship, 0, atype, coord, textures[atype]->getFrameWidth(), textures[atype]->getFrameHeight(), 2, textures[atype], this);
			}

			// lo mete en la lista
			sceneObjectsList.push_back(obj);

			//iterador al final de la lista
			list<SceneObject*>::iterator newit = sceneObjectsList.end();

			newit--;

			// le pasa el iterador
			obj->setListIterator(newit);
		}

		// si es un bunker
		else if (type == 2) {
			// esto no se q es
			Vector2D<int> vel(0, 0);

			//bunker
			SceneObject* obj = new Bunker(0, coord, textures[Escudo]->getFrameWidth(), textures[Escudo]->getFrameHeight(), 3, textures[Escudo], this);

			// lo mete en la lista
			sceneObjectsList.push_back(obj);

			//iterador al final de la lista
			list<SceneObject*>::iterator newit = sceneObjectsList.end();

			newit--;

			// le pasa el iterador
			obj->setListIterator(newit);
		}
	}
}
#pragma endregion