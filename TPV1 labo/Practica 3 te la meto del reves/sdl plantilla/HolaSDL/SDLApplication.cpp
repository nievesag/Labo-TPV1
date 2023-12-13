#include "checkML.h"
#include "SDLApplication.h"

#include "FileNotFoundError.h"
#include "SDLError.h"
#include "FileFormatError.h" 

using namespace std;

// constructora del game
SDLApplication::SDLApplication()
{
	
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// Inicializaci�n del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);

	// crea la ventana
	window = SDL_CreateWindow("Space Invaders", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);

	// crea el renderer para la ventana
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// ERRORES DE SDL
	if (window == nullptr || renderer == nullptr)
		throw SDLError("Error cargando ventana de juego o renderer "s + SDL_GetError());

	loadTextures();

	mainMenu();


	// --------------------- MAQUINA DE ESTADOS ---------------------------
	// !!! el render de los estados debe ser const pero hay un error y no tengo ganas ahora de arreglarlo
	// crea una maquina de estados


	gsMachine = new GameStateMachine();


	GameState* mms = new MainMenuState(this);

	//
	gsMachine->pushState(mms);

	
}

SDLApplication::~SDLApplication()
{
	// borra el mothership
	delete mother;

	// limpia las texturas
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); // cierra pantalla
}

#pragma region LOGICA DE JUEGO
// ----- LOGICA DE JUEGO -----
// cargar | manejar eventos -> actualizar -> pintar -> manejar eventos etc

// MANEJAR EVENTOS 
void SDLApplication::handleEvents()
{
	while (SDL_PollEvent(&event) && !exit) {

		// escanea y evalua que tecla has tocado
		SDL_Scancode key = event.key.keysym.scancode;

		// si se pulsa una tecla
		if (key == SDL_SCANCODE_S) {

			gsMachine->replaceState(new PlayState(this));
		}
	}

	// EVENTOS NO TOCAR O LA TENEMOS ------------
	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) {
		gsMachine->handleEvent(event);
	}

	// HASTA AKI ------------
	/*
		// lo antiguo !!!! limpiar
		ifstream in("..\\mapas\\original.txt");

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
		*/
}

// --------------------------------------------- NO SE NECESITA?
void SDLApplication::EndGame()
{
	exit = true;
}

// RUN
void SDLApplication::run()
{
	// get ticks al inicio del bucle
	startTime = SDL_GetTicks();

	while (!exit)
	{
		handleEvents();

		/*
		// tiempo desde ultima actualizacion
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime > TIME_BT_FRAMES) {
			update(); // actualiza todos los objetos de juego
			startTime = SDL_GetTicks();
		}

		render(); // renderiza todos los objetos de juego
		*/
	}
	
	/*
	// escribe game over
	cout << "GAME OVER" << endl;
	// escribe puntuacion
	PlayerScore();
	*/
}

// ACTUALIZAR 
void SDLApplication::update()
{
	//
	gsMachine->update();

	/*
	// actualiza el mothership
	mother->update();

	// actualiza los objetos de escena
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		(*it)->update();
	}

	// borra los objetos a borrar
	deleteSceneObjects();
	*/
}

// PINTAR
void SDLApplication::render()
{
	SDL_RenderClear(renderer);
	gsMachine->render();
	SDL_RenderPresent(renderer);

	/*
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
	*/
}

void SDLApplication::renderBackground()
{
	// renderiza el fondo
	textures[Fondo]->render();
}


// ELIMINACION DE OBJETOS
#pragma region ELIMINACION DE OBJETOS
void SDLApplication::deleteSceneObjects()
{
	if (objectsToErase.size() > 0) {

		// bucle para borrar los objetos que han de ser borrados
		for (auto a : objectsToErase) {

			// borramos el objeto
			delete (*a);

			// lo borra de la lista
			sceneObjectsList.erase(a);
		}
		objectsToErase.clear();
	}
}

void SDLApplication::hasDied(list<SceneObject*>::iterator& it)
{
	// aniade el objeto a la lista de borradores
	objectsToErase.push_back(it);
}
#pragma endregion

#pragma region MENUS
void SDLApplication::saveThisGame()
{
	// pregunta en que numero se va a guardar la partida
	cout << "Save this game in slot: " << std::endl;

	// lee el numero en char k
	cin >> k;

	// comprueba que sea un numero, si no lo es le dice que es invalido
	if (isdigit(k))
	{
		// pasa numero a string despues del save (savek)
		save("save" + to_string(k - '0'));

		// acaba el juego
		EndGame();

		// se ha salvado el juego
		cout << "Game saved!" << endl;
	}
	else cout << "Invalid number :(";
}

void SDLApplication::loadThisGame()
{
	// pregunta que slot se quiere cargar
	cout << "Load slot: " << std::endl;

	// lee el numero en char k
	cin >> k;

	// comprueba que sea un numero, si no lo es le dice que es invalido
	if (isdigit(k))
	{
		// pasa numero a string despues del save (savek)
		load("save" + to_string(k - '0'), "..\\saved\\");

		// se ha salvado el juego
		cout << "Game loaded!" << endl;
	}
	else cout << "Invalid number :(";
}
#pragma endregion

// MANEJAR SCORE
void SDLApplication::increaseScore(int score)
{
	SCORE += score;
}

void SDLApplication::PlayerScore()
{
	cout << "SCORE: " << SCORE << endl;
}

// GUARDAR
#pragma region SISTEMA GUARDADO
void SDLApplication::save(const string& file)
{
	/*

	// abre un canal para guardar en un archivo con el nombre deseado
	ofstream out(SAVED_FOLDER + file + ".txt");

	mother->save(out);

	// bucle para llegar a los save de todos los objetos
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++) {

		(*it)->save(out);
	}

	// guarda los puntos
	out << "7 " << SCORE << endl;

	// cierra el hilo
	out.close();
	*/
}

void SDLApplication::load(const string& file, const string& root)
{
	loadAnyFile(file, root);
}
#pragma endregion

// fin logica
#pragma endregion 

// CONTROL DE DA�O
#pragma region CONTROL DE DA�O
void SDLApplication::fireLaser(Point2D<double> pos, char frenemy)
{
	if (frenemy == 'a') {
		SDL_SetRenderDrawColor(renderer, 255, 0, 114, 255);	// cannon
	}
	else {
		SDL_SetRenderDrawColor(renderer, 255, 242, 0, 255);	// aliens
	}

	// crea el laser
	//SceneObject* newObj = new Laser(frenemy, pos, defaultLaserW, defaultLaserH, defaultLives, nullptr, this);

	// lo mete en la lista
	//sceneObjectsList.push_back(newObj);
}

bool SDLApplication::damage(Laser* myLaser)
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

// CARGA
#pragma region LOADS
void SDLApplication::loadTextures()
{
	// bucle para rellenar el array de texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {

		// crea la textura con el url, width y height
		Texture* tex = new Texture(renderer, textureSpec[i].url, textureSpec[i].nh, textureSpec[i].nw);

		// la mete en el array
		textures[i] = tex;
		if (textures[i] == nullptr) {

			throw SDLError("Error cargando texturas "s + SDL_GetError());
		}
	}
}

void SDLApplication::loadAnyFile(const string& file, const string& root)
{
	// lee el mapa
	ifstream in(root + file + ".txt");
	if (in.fail()) throw FileNotFoundError("No se ha podido leer el mapa "s + file + ".txt");

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

		/*
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
			SceneObject* obj = new Cannon(cooldown, coord, textures[Nave]->getFrameWidth(),
				textures[Nave]->getFrameHeight(), vidas, textures[Nave], this);

			// lo mete en la lista
			sceneObjectsList.push_back(obj);
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
			SceneObject* obj = new Alien(mother, defaultFrame, alienType, coord, textures[alienType]->getFrameWidth(),
				textures[alienType]->getFrameHeight(), defaultLives, textures[alienType], this);

			// lo mete en la lista
			sceneObjectsList.push_back(obj);

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

			SceneObject* obj = new ShooterAlien(cooldown, mother, defaultFrame, alienType, coord,
				textures[alienType]->getFrameWidth(), textures[alienType]->getFrameHeight(), defaultLives,
				textures[alienType], this);

			// lo mete en la lista
			sceneObjectsList.push_back(obj);


			// ----------------------- Fin del stup -----------------------

			// acaba el caso
			break;
		}

			  // si es el mothership
		case 3: {
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
			mother = new Mothership(y, this, timer, estado);

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

			// bunker
			SceneObject* obj = new Bunker(hits, coord, textures[Escudo]->getFrameWidth(),
				textures[Escudo]->getFrameHeight(), vidas, textures[Escudo], this);

			// lo mete en la lista
			sceneObjectsList.push_back(obj);


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
			in >> vidas;

			// ---------------- Creacion del objeto ------------------

			// textures[Escudo]->getFrameWidth(), textures[Escudo]->getFrameHeight()
			SceneObject* obj = new Ufo(Point2D<double>(winWidth, y), textures[UfoT]->getFrameWidth(),
				textures[UfoT]->getFrameHeight(), vidas, textures[UfoT], this);

			// lo mete en la lista
			sceneObjectsList.push_back(obj);


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
			Vector2D<double> coord(x, y);

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
			SceneObject* obj = new Laser(color, coord, laserW, laserH, defaultLives, nullptr, this);

			// lo mete en la lista
			sceneObjectsList.push_back(obj);

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
		*/
		
	}



	// si no existe una mothership la crea
	if (mother == nullptr) {

		// crea la mothership
		//mother = new Mothership(defaultMothershipLevel, this, 30, 0);
	}


	// settea el mothership en los aliens
	for (list<SceneObject*>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++)
	{
		// hace un dynamic cast de cada alien
		Alien* alien = dynamic_cast<Alien*>(*it);

		// si es un alien setea el mothership
		if (alien != nullptr) {
			// llama al setteador
			alien->setMothership(mother);

			// a�ade al contador de aliens de la mothership
			mother->addAlien();
		}
	}
}

void SDLApplication::mainMenu()
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
		//loadMap();

		loadAnyFile("original", "..\\mapas\\");
	}
	else if (ans == 1) {

		// carga una partida
		loadThisGame();
	}
}
#pragma endregion