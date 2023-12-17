#include "checkML.h"
#include "SDLApplication.h"

#include "PlayState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

PlayState::PlayState(SDLApplication* game, string loadFile) : app(game), GameState(game), loadFile(loadFile) {

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

void PlayState::loadAnyFile(const string& fileAndRoot)
{
	// lee el mapa
	ifstream in(fileAndRoot + ".txt");

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
		// set up del archivo para cada objeto
		switch (objID)
		{
			// CANNON
			case 0: {

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

				break;
			}

			// ALIEN
			case 1: {

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

				break;
			}

			// SHOOTER ALIEN
			case 2: {

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

				break;
			}

			// MOTHERSHIP
			case 3: {

			// ---------------- Lectura de variables ---------------

				// lee la altura
				in >> y;

				// lee el tipo
				in >> estado;
				in >> timer;

			// ---------------- Creacion del objeto ------------------

				// crea la mothership
				mother = new Mothership(y, this, timer, estado);

				break;
			}

			// BUNKER
			case 4: {


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

				break;
			}

			// UFO
			case 5: {

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
				SceneObject* obj = new Ufo(Point2D<double>(winWidth, y), app->getTexture(UfoT)->getFrameWidth(),
					app->getTexture(UfoT)->getFrameHeight(), vidas, app->getTexture(UfoT), this);

				// lo mete en la lista
				sceneObjectsList.push_back(obj);
				
				break;
			}

			// LASER
			case 6: {

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

				break;
			}

			// PUNTUACION
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
	}
}

// UPDATE
void PlayState::update()
{
	// actualiza el mothership
	mother->update();

	//bucle for each para recorrer los objetos de la lista sceneObjectsList:
	//		-> tipo del objeto (& porque CREO que devuelve un puntero CREO) a : lista
	for (SceneObject& a : sceneObjectsList) {

		a.update();
	}
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

bool PlayState::mayGrantReward(SDL_Rect rect)
{
	// deteccion de colision de la reward con el cannon
	return false;
}

// MANEJO DE EVENTOS
void PlayState::HandleEvent(const SDL_Event& event)
{
	// gestiona todos los eventos del estado correspondiente
	GameState::HandleEvent(event);

	// si se pulsa esc
	if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

		// pausa el juego
		// (aniade el estado de pausa a la maquina de estados de application)
		application->getgsMachine()->pushState(new PauseState(application, this));
	}
}

// GUARDADO
void PlayState::save(const string& file)
{
	// abre un canal para guardar en un archivo con el nombre deseado
	ofstream out(SAVED_FOLDER + file + ".txt");

	mother->save(out);
	
	for (GameList<SceneObject, true>::forward_iterator i = sceneObjectsList.begin(); i != sceneObjectsList.end(); ++i) {

		(*i).save(out);
	}

	// guarda los puntos
	out << "7 " << SCORE << endl;

	// cierra el hilo
	out.close();
}

void PlayState::saveThisGame()
{
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
	cout << "entering PlayState\n";
	loadAnyFile(loadFile);	// carga la partida
	return true;
}

bool PlayState::onExit()
{
	cout << "exiting PlayState\n";
	return true;
}

void PlayState::EndGame()
{
	application->setExit(true);
}

// COLISONES
bool PlayState::damage(SDL_Rect rect, char frenemy)
{
	for (SceneObject& a : sceneObjectsList) {

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
	//objectsToErase.push_back(i);

	sceneObjectsList.erase(i);

	//toBeErased.push_back(i);
}


void PlayState::fireLaser(Point2D<double> pos, char frenemy)
{
	// crea el laser
	SceneObject* newObj = new Laser(frenemy, pos, defaultLaserW, defaultLaserH, defaultLives, nullptr, this);

	// lo mete en la lista:
	// cuando se añade a la lista un objeto, le asigna directamente el anchor (entiendo que es un iterador
	// pero estatico ??? tipo no se mueve) para luego poder usarlo en eliminaciones de objetos.
	sceneObjectsList.push_back(newObj);
}

void PlayState::fireBomb(Point2D<double> pos) {

	// crea el laser
	//SceneObject* newObj = new Laser(frenemy, pos, defaultLaserW, defaultLaserH, defaultLives, nullptr, this);
	// Bomb(Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
	SceneObject* newObj = new Bomb(pos, app->getTexture(BOMBA)->getFrameWidth(), app->getTexture(BOMBA)->getFrameHeight(),
		defaultBombLives, app->getTexture(BOMBA), this);

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
	/*
	// elimina los objetos de objectsToErase
	toBeErased.clear();


	// creo que no hace falta este metodo por como va la clase gameList pero lo dejo asi
	// de momento hasta que tenga tiempo para estudarmela
	
	if (!objectsToErase.empty()) {

		// bucle para borrar los objetos que han de ser borrados
		for (auto a : objectsToErase) {

			// borramos el objeto
			delete (a);

			// lo borra de la lista
			sceneObjectsList.erase(a);
		}
		objectsToErase.clear();
	}
	*/
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