#include "checkML.h"
#include "SDLApplication.h"

#include "PlayState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

PlayState::PlayState(SDLApplication* game) : app(game), GameState(game) {

}

SDL_Renderer* PlayState::getAppRenderer() {

	return app->getRenderer();
}

// LOGICA DE JUEGO
// cargar | manejar eventos -> actualizar -> pintar -> manejar eventos etc

// LOADS
void PlayState::loadTextures()
{

	
	// bucle para rellenar el array de texturas
	for (int i = 0; i < app->getNumText(); i++) {

		cout << " texture " << i << endl;

		// crea la textura con el url, width y height
		Texture* tex = new Texture(app->getRenderer(), app->getTextureSpec(i).url, app->getTextureSpec(i).nh, app->getTextureSpec(i).nw);

		// la mete en el array
		app->setTexture(i, tex);


		if (app->getTexture(i) == nullptr) {

			// !!!!!!!! MIRAR 
			//throw SDLError("Error cargando texturas "s + SDL_GetError());
		}
	}
	
	
}

void PlayState::loadAnyFile(const string& file, const string& root)
{
	// lee el mapa
	ifstream in(root + file + ".txt");

	// !!!!!! MIRAR
	//if (in.fail()) throw FileNotFoundError("No se ha podido leer el mapa "s + file + ".txt");

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
				SceneObject* obj = new Cannon(cooldown, coord, app->getTexture(Nave)->getFrameWidth(),
					app->getTexture(Nave)->getFrameHeight(), vidas, app->getTexture(Nave), this);

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
				SceneObject* obj = new Alien(mother, defaultFrame, alienType, coord, app->getTexture(alienType)->getFrameWidth(),
					app->getTexture(alienType)->getFrameHeight(), defaultLives, app->getTexture(alienType), this);

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
					app->getTexture(alienType)->getFrameWidth(), app->getTexture(alienType)->getFrameHeight(), defaultLives,
					app->getTexture(alienType), this);

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
				SceneObject* obj = new Bunker(hits, coord, app->getTexture(Escudo)->getFrameWidth(),
					app->getTexture(Escudo)->getFrameHeight(), vidas, app->getTexture(Escudo), this);

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

				/*
				// textures[Escudo]->getFrameWidth(), textures[Escudo]->getFrameHeight()
				SceneObject* obj = new Ufo(Point2D<double>(winWidth, y), app->getTexture(UfoT)->getFrameWidth(),
					app->getTexture(UfoT)->getFrameHeight(), vidas, app->getTexture(UfoT), this);

				// lo mete en la lista
				sceneObjectsList.push_back(obj);
				*/
				


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
					SDL_SetRenderDrawColor(app->getRenderer(), 255, 0, 114, 255);	// cannon
				}
				else {
					SDL_SetRenderDrawColor(app->getRenderer(), 255, 242, 0, 255);	// aliens
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



		// si no existe una mothership la crea
		if (mother == nullptr) {

			// crea la mothership
			mother = new Mothership(defaultMothershipLevel, this, 30, 0);
		}

		/*
		// settea el mothership en los aliens
		for (SceneObject a : sceneObjectsList)
		{
			// !!!!!! SETTEAR BIEN EL MOTHERSHIP
			
			// si es un alien setea el mothership
			if (alien != nullptr) {
				// llama al setteador
				alien->setMothership(mother);

				// añade al contador de aliens de la mothership
				mother->addAlien();
			}
			
			
		}
		*/
	}
	
	
}

// UPDATE
void PlayState::update()
{
	//
	//cout << "update" << endl;

	// actualiza el mothership
	//mother->update();

	//bucle for each para recorrer los objetos de la lista sceneObjectsList:
	//		-> tipo del objeto (& porque CREO que devuelve un puntero CREO) a : lista
	for (SceneObject& a : sceneObjectsList) {

		a.update();
	}

	// tambien se puede hacer con un iterador:
	// AHORA MISMO NO VA CON ITERADORES (SI LO DESCOMENTAS DA ERROR) PEROÇ
	// QUIERO SACARLO CON ITERADORES IGUAL
	// for(GameList<SceneObject, true>::iterator it = sceneObjectsList.begin(); it != sceneObjectsList.end(); it++)

	// borra los objetos a borrar
	//deleteSceneObjects();

}

// RENDER
void PlayState::render() const 
{
	renderBackground();

	//bucle for each para recorrer los objetos de la lista sceneObjectsList:
	for (SceneObject& a : sceneObjectsList) {
		a.render();
	}
}

void PlayState::renderBackground() const {

	// renderiza el fondo
	app->getTexture(Fondo)->render();
}

// MANEJO DE EVENTOS
void PlayState::handleEvent(const SDL_Event& event)
{
	// gestiona todos los eventos del estado correspondiente
	GameState::handleEvent(event);

	// si se pulsa esc
	if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

		// pausa el juego
		// (aniade el estado de pausa a la maquina de estados de application)
		application->getgsMachine()->pushState(new PauseState(application));
	}
}

// GUARDADO
void PlayState::save(const string& file)
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

void PlayState::saveThisGame()
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
		//EndGame();

		// se ha salvado el juego
		cout << "Game saved!" << endl;
	}
	else cout << "Invalid number :(";
}

// MANEJO DE ESTADOS
bool PlayState::onEnter()
{
	//
	
	std::cout << "entering PlayState\n";

	loadTextures();

	// carga la partida
	loadAnyFile("save7", "..\\mapas\\");

	return true;
}

bool PlayState::onExit()
{
	cout << "exiting PlayState\n";
	return true;
}

void PlayState::EndGame()
{


}

// COLISONES
bool PlayState::damage(SDL_Rect rect, char frenemy)
{
	for (SceneObject a : sceneObjectsList) {

		// se ha pegado un hostion (colisiones)
		if (a.hit(&rect, frenemy)) {
			// devuelve si ha hitteado	
			return true;
		}
	}
	return false;
}

void PlayState::hasDied(GameList<SceneObject, true>::anchor i)
{
	// que cojones es un anchor ?????
	// aniade el ANCHOR del objeto a la lista de borradores
	objectsToErase.push_back(i);

}

void PlayState::fireLaser(Point2D<double> pos, char frenemy)
{
	if (frenemy == 'a') {
		SDL_SetRenderDrawColor(app->getRenderer(), 255, 0, 114, 255);	// cannon
	}
	else {
		SDL_SetRenderDrawColor(app->getRenderer(), 255, 242, 0, 255);	// aliens
	}
	// crea el laser
	SceneObject* newObj = new Laser(frenemy, pos, defaultLaserW, defaultLaserH, defaultLives, nullptr, this);

	// lo mete en la lista:
	// cuando se añade a la lista un objeto, le asigna directamente el anchor (entiendo que es un iterador
	// pero estatico ??? tipo no se mueve) para luego poder usarlo en eliminaciones de objetos.
	sceneObjectsList.push_back(newObj);
}

void PlayState::increaseScore(int score)
{


}

// BORRADO
void PlayState::deleteSceneObjects()
{
	// creo que no hace falta este metodo por como va la clase gameList pero lo dejo asi
	// de momento hasta que tenga tiempo para estudarmela
	if (objectsToErase.size() > 0) {

		// bucle para borrar los objetos que han de ser borrados
		for (auto a : objectsToErase) {

			// borramos el objeto
			delete (a);

			// lo borra de la lista
			sceneObjectsList.erase(a);
		}
		objectsToErase.clear();
	}
}

// GETTERS
int PlayState::getRandomRange(int min, int max)
{
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

string PlayState::getID() const
{
	return s_playID;
}