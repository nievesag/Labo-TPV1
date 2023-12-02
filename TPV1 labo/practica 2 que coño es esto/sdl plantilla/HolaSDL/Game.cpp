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

	mainMenu();

	//loadMap();
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

// GUARDAR
void Game::save(const string& file)
{
	// abre un canal para guardar en un archivo con el nombre deseado
	ofstream out(SAVED_FOLDER + file + ".txt");

	milfship->save(out);

	// bucle para llegar a los save de todos los objetos
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		(*it)->save(out);
	}

	// guarda los puntos
	out << "7 " << SCORE << endl;

	// cierra el hilo
	out.close();

}

void Game::load(const string& file)
{

	loadAnyFile(file);

	//cout << "se cargaaaaaaaaaaaaa" << endl;
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

		// escanea y evalua que tecla has tocado
		SDL_Scancode key = event.key.keysym.scancode;

		// si se solicita quit bool exit = true
		if (event.type == SDL_QUIT) EndGame();

		// si se pulsa una tecla
		else if (event.type == SDL_KEYDOWN && (key == SDL_SCANCODE_S || key == SDL_SCANCODE_L)) {

			// si es la tecla S (save)
			if (key == SDL_SCANCODE_S) {

				// guarda la partida (incluye la gestion del 'menu')
				saveThisGame();
			}
			// si es la tecla L (load)
			else if (key == SDL_SCANCODE_L) {

				// carga la partida indicada
				loadThisGame();
			}
		}
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

		// bucle para borrar los objetos que han de ser borrados
		for (auto a : objectsToErase) {

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

#pragma region Gestion de menuses
void Game::saveThisGame()
{
	// pregunta en que numero se va a guardar la partida
	cout << "Save this game in slot: " << std::endl;

	// crea un char para guardar el numero y lo lee
	char k;
	cin >> k;

	// comprueba que sea un numero, si no lo es le dice que es invalido
	if (isdigit(k))
	{
		// pasa numero a string despues del save (savek)
		save("save" + to_string(k - '0'));

		// acaba el juego
		EndGame();

		// se ha salvado el juego !!!!!
		cout << "Game saved!" << endl;
	}
	else cout << "Invalid number :(";

}

void Game::loadThisGame()
{
	// pregunta que slot se quiere cargar
	cout << "Load slot: " << std::endl;

	// crea un char para guardar el numero y lo lee
	char k;
	cin >> k;

	// comprueba que sea un numero, si no lo es le dice que es invalido
	if (isdigit(k))
	{
		// pasa numero a string despues del save (savek)
		load("save" + to_string(k - '0'));

		// se ha salvado el juego !!!!!
		cout << "Game loaded!" << endl;
	}
	else cout << "Invalid number :(";

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

	if (frenemy == 'a') {
		SDL_SetRenderDrawColor(renderer, 255, 0, 114, 255);	// cannon
	}	
	else {
		SDL_SetRenderDrawColor(renderer, 255, 242, 0, 255);	// aliens
	}
	
	// crea el laser
	SceneObject* newObj = new Laser(frenemy, pos, 4, 10, 1, nullptr, this);

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
void Game::showUfo(Point2D<double> pos)
{
	// settea la velocidad
	Vector2D<double> vel(0, 1);
	double min = getRandomRange(2, 7);
	double max = getRandomRange(8, 15);

	SDL_SetRenderDrawColor(renderer, 255, 0, 114, 255);	// cannon

	vel.setX(-1);

	// crea el ufo
	Ufo* newObj = new Ufo(min, max, vel, pos, textures[UfoT]->getFrameWidth(), textures[UfoT]->getFrameHeight(), 1, textures[UfoT], this);

	// lo mete en la lista
	sceneObjectsList.push_back(newObj);

	//iterador al final de la lista
	list<SceneObject*>::iterator newit = sceneObjectsList.end();
	
	newit--;

	// le pasa el iterador
	newObj->setListIterator(newit);
	
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
	milfship = new Mothership(1, this, 30, 0);

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

				//
				obj = new ShooterAlien(defaultCooldown, milfship, 0, atype, coord, textures[atype]->getFrameWidth(), 
					textures[atype]->getFrameHeight(), 2, textures[atype], this);
			}
			else {
				// sobrecargas: Alien(mothership, frame, type, position, width, height, lifes, texture, game)
				obj = new Alien(milfship, 0, atype, coord, textures[atype]->getFrameWidth(), 
					textures[atype]->getFrameHeight(), 2, textures[atype], this);
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

void Game::loadAnyFile(const string& file)
{
	// lee el mapa
	ifstream in(SAVED_FOLDER + file + ".txt");
	if (in.fail()) throw ("No se ha podido leer mapa");

	// variables auxiliares
	int objID;						// id
	int x, y;						// pos
	int alienType, cooldown, vidas,	// otros
		estado, hits, timer, score;
	char color;						// color

	// mientras no se acabe el archivo sigue leyendo
	while (!in.eof()) {
		
		// lee el identificador
		in >> objID;

		// switch para leer y crear cada objeto
		switch (objID)
		{
			// si es el cannon
			case 0: {
				// set up del archivo para el cannon:
				// id x y vidas cd

				// ---------------- Lectura de variables ---------------
				// lee la posicion
				in >> x;
				in >> y;

				// lee las vidas y el cd
				in >> vidas;
				in >> cooldown;
				
				// crea el vector
				Point2D<double> coord(x, y);

				// ---------------- Creacion del objeto ------------------
				// nave
				SceneObject* obj = new Cannon(cooldown, coord, textures[Nave]->getFrameWidth(), textures[Nave]->getFrameHeight(), vidas, textures[Nave], this);

				// lo mete en la lista
				sceneObjectsList.push_back(obj);

				//iterador al final de la lista
				list<SceneObject*>::iterator newit = sceneObjectsList.end();

				// el ultimo iterador es ???, por lo que le restamos 1 para que no sea invalido
				newit--;

				// le pasa el iterador
				obj->setListIterator(newit);

				// ----------------------- Fin del stup -----------------------

				// acaba el caso
				break;
				}

			// si es un alien
			case 1: {
				// setup del alien:
				// id x y type

				// ---------------- Lectura de variables ---------------
				// lee la posicion
				in >> x;
				in >> y;

				// crea el vector
				Point2D<double> coord(x, y);

				// lee el tipo
				in >> alienType;

				// ---------------- Creacion del objeto ------------------
				
				// sobrecargas: Alien(mothership, frame, type, position, width, height, lifes, texture, game)
				SceneObject* obj = new Alien(milfship, defaultFrame, alienType, coord, textures[alienType]->getFrameWidth(), 
					textures[alienType]->getFrameHeight(), defaultLives, textures[alienType], this);

				// lo mete en la lista
				sceneObjectsList.push_back(obj);

				//iterador al final de la lista
				list<SceneObject*>::iterator newit = sceneObjectsList.end();

				// el ultimo iterador es ???, por lo que le restamos 1 para que no sea invalido
				newit--;

				// le pasa el iterador
				obj->setListIterator(newit);

				// ----------------------- Fin del stup -----------------------

				// acaba el caso
				break;
				}

			// si es un shotter alien
			case 2: {
				// setup del shooter alien:
				// id x y type cooldown

				// ---------------- Lectura de variables ---------------

				// lee la posicion
				in >> x;
				in >> y;

				// crea el vector
				Point2D<double> coord(x, y);

				// lee el tipo
				in >> alienType;

				in >> cooldown;

				// ---------------- Creacion del objeto ------------------

				//
				SceneObject* obj = new ShooterAlien(cooldown, milfship, defaultFrame, alienType, coord, 
					textures[alienType]->getFrameWidth(), textures[alienType]->getFrameHeight(), defaultLives, 
					textures[alienType], this);

				// lo mete en la lista
				sceneObjectsList.push_back(obj);

				//iterador al final de la lista
				list<SceneObject*>::iterator newit = sceneObjectsList.end();

				// el ultimo iterador es ???, por lo que le restamos 1 para que no sea invalido
				newit--;

				// le pasa el iterador
				obj->setListIterator(newit);


				// ----------------------- Fin del stup -----------------------

				// acaba el caso
				break;
				}
			
			// si es el mothership
			case 3:{
				// setup de la mothership:
				// id level estado timer

				// ---------------- Lectura de variables ---------------

				// lee la altura
				in >> y;

				// lee el tipo
				in >> estado;
				in >> timer;

				// ---------------- Creacion del objeto ------------------

				// crea la mothership
				milfship = new Mothership(y, this, timer, estado);

				// ----------------------- Fin del stup -----------------------

				// acaba el caso
				break;
				}

			// si es un bunker
			case 4: {
				// setup del bunker:
				// id x y vidas hits

				// ---------------- Lectura de variables ---------------

				// lee la posicion
				in >> x;
				in >> y;

				// crea el vector
				Point2D<double> coord(x, y);

				// lee el tipo
				in >> vidas;
				in >> hits;

				// ---------------- Creacion del objeto ------------------

				//bunker
				SceneObject* obj = new Bunker(hits, coord, textures[Escudo]->getFrameWidth(), 
					textures[Escudo]->getFrameHeight(), vidas, textures[Escudo], this);

				// lo mete en la lista
				sceneObjectsList.push_back(obj);

				//iterador al final de la lista
				list<SceneObject*>::iterator newit = sceneObjectsList.end();

				newit--;

				// le pasa el iterador
				obj->setListIterator(newit);

				// ----------------------- Fin del stup -----------------------

				// acaba el caso
				break;
			}

			// si es el ufo
			case 5: {
				// setup del ufo:
				// id y estado cooldown hits

				// ---------------- Lectura de variables ---------------

				// lee la posicion
				in >> y;

				// crea el vector
				Point2D<double> coord(0, y);

				// lee 
				in >> estado;
				in >> cooldown;
				in >> hits;


				// ---------------- Creacion del objeto ------------------


				// ----------------------- Fin del stup -----------------------

				// acaba el caso
				break;
			}

			// si es un laser
			case 6: {
				// setup del laser:
				// id x y color

				// ---------------- Lectura de variables ---------------

				// lee la posicion
				in >> x;
				in >> y;

				// crea el vector
				Point2D<double> coord(x, y);

				// lee el tipo
				in >> color;

				// ---------------- Creacion del objeto ------------------

				if (color == 'a') {
					SDL_SetRenderDrawColor(renderer, 255, 0, 114, 255);	// cannon
				}
				else {
					SDL_SetRenderDrawColor(renderer, 255, 242, 0, 255);	// aliens
				}

				//bunker
				SceneObject* obj = new Laser(color, coord, laserW, laserH, 
					defaultLives, nullptr, this);

				// lo mete en la lista
				sceneObjectsList.push_back(obj);

				//iterador al final de la lista
				list<SceneObject*>::iterator newit = sceneObjectsList.end();

				newit--;

				// le pasa el iterador
				obj->setListIterator(newit);

				// ----------------------- Fin del stup -----------------------

				// acaba el caso
				break;
			}

			// si es la puntuacion
			case 7: {
				in >> score;

				SCORE = score;

				break;
			}

		}

		// settea el mothership en los aliens
		for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++)
		{
			// hace un dynamic cast de cada alien
			Alien* alien = dynamic_cast<Alien*>(*it);

			// si es un alien setea el mothership
			if (alien != nullptr) {
				// llama al setteador
				alien->setMothership(milfship);

				// añade al contador de aliens de la mothership
				milfship->addAlien();
			}
		}
	}


}

void Game::mainMenu()
{
	// pregunta si quieres cargar juego
	cout << "Load game? \n  Yes -> 1 \n  No -> 0" << endl;

	// recibe la respuesta
	cin >> ans;

	// si la respuesta es invalida le dice que lo vuelva a intentar
	while (ans != 0 && ans != 1) {

		cout << "Invalid input, remember: \n  Yes -> 1 \n  No -> 0" << endl;
		cin >> ans;
	}
	
	// si la respuesta es no carga 
	if (ans == 0) {

		// carga un mapa
		loadMap();
	}
	else if (ans == 1) {

		// carga una partida
		loadThisGame();
		//loadMap(); // placeholder apra que no pete
	}

}
#pragma endregion