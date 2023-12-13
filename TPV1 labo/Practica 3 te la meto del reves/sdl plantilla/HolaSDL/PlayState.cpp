#include "PlayState.h"
#include "checkML.h"
#include "SDLApplication.h"

void PlayState::update()
{
	//
	cout << "update" << endl;

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

void PlayState::render()
{
	//
	cout << "render" << endl;

	//bucle for each para recorrer los objetos de la lista sceneObjectsList:
	for (SceneObject& a : sceneObjectsList) {
		a.render();
	}
}

bool PlayState::onEnter()
{
	//
	
	std::cout << "entering PlayState\n";

	return true;
}

bool PlayState::onExit()
{
	cout << "exiting PlayState\n";
	return true;
}

string PlayState::getID() const
{
	return s_playID;
}

int PlayState::getRandomRange(int min, int max)
{
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

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

void PlayState::loadTextures()
{
	// bucle para rellenar el array de texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {

		// crea la textura con el url, width y height
		Texture* tex = new Texture(app->getRenderer(), textureSpec[i].url, textureSpec[i].nh, textureSpec[i].nw);

		// la mete en el array
		textures[i] = tex;
		if (textures[i] == nullptr) {

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


		// settea el mothership en los aliens
		for (SceneObject a : sceneObjectsList)
		{
			// !!!!!! SETTEAR BIEN EL MOTHERSHIP
			/*
			// si es un alien setea el mothership
			if (alien != nullptr) {
				// llama al setteador
				alien->setMothership(mother);

				// añade al contador de aliens de la mothership
				mother->addAlien();
			}
			*/
			
		}
}

