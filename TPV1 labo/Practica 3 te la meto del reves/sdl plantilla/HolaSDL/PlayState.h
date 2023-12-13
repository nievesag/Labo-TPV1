#ifndef PLAYSTATE_H
#define PLAYSTATE_H

// includes
#include <SDL.h>
#include <random>
#include <fstream>
#include <string>

// 
#include "GameState.h"
#include "gameList.h"
#include "SceneObject.h"
#include "Laser.h"
#include "SDLApplication.h"

using namespace std;
using uint = unsigned int;

//class SDLApplication;

class PlayState : public GameState{

private:

	//------------------------------------------ GENERAL ---------------------------

	// id del estado
	const string s_playID = "PLAY";

	// default variables
	int defaultLives = 1,	// default number of lives
		defaultFrame = 0,	// default starting frame
		ans = 0,			// respuesta en los menuses
		laserW = 4,			// dimensiones del laser
		laserH = 10,
		defaultCooldown = 10,// default cooldown (si es -1 se genera uno)
		defaultUfoHeight = 10,
		defaultLaserW = 4,
		defaultLaserH = 10,
		defaultMothershipLevel = 0;

	// ------------------------------------ TEXTURAS -----------------------------------
	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 7;

	// enum texture name -> el indice tiene la info de la textura
	enum TextureName { Alien1, Alien2, Alien3, Nave, Escudo, Fondo, UfoT };

	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	array<Texture*, NUM_TEXTURES> textures{};

	struct TextureSpec
	{
		const char* url;

		// width height
		int nw, nh;
	};

	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo TextureSpec 
	// ubicacion, col, fil
	array<TextureSpec, SDLApplication::NUM_TEXTURES> textureSpec{
		TextureSpec{"..\\images\\aliens2.png", 2, 3},	  // alien 1 // 32,32
		{ "..\\images\\aliens2.png", 2, 3 },			  // alien 2 // 44,32
		{ "..\\images\\aliens2.png", 2, 3 },			  // alien 3 // 48,32
		{ "..\\images\\spaceship.png", 1, 1 },			  // nave	 // 34,21
		{ "..\\images\\bunker.png", 4, 1 },				  // bunker  // 88,57
		{ "..\\images\\stars.png", 1, 1 },				  // fondo 
		{ "..\\images\\ovni2.png", 3, 1 }				  // ufo	 // 48,26
	};


	// -------------------------------------- CARGA Y DESCARGA ---------------------------
	// archivo de strings con las roots de las carpetas etc
	string SAVED_FOLDER = "..\\saved\\";


protected:

	// este es el nuevo game... pero que hace el atiguo ????

	// en Game: punteros a window y render
	//			array de texturas
	//			maquina de estados

	SDLApplication* app;


	// lista de objetos de escena (cannon, aliens, bunkeres, laser)
	GameList<SceneObject, true> sceneObjectsList;

	// lista de iteradores de objetos que eliminar
	//list<list<SceneObject*>::iterator> objectsToErase;
	// lista de anchors de objetos a eliminar
	list<GameList<SceneObject, true>::anchor>objectsToErase;

	// puntero al mothership
	Mothership* mother;

	// MANEJO DEL TIEMPO EN RUN
	mt19937_64 randomGenerator;	// crea semilla
	uint32_t startTime, frameTime;

	int SCORE = 0;	// score general del player

	char k; // crea un char para guardar el numero

public:

	// constructora
	PlayState::PlayState(SDLApplication* game) : GameState(game), app(game) {
	
	};

	// -------------------------------- HERENCIA --------------------------------
	// update
	void update() override;

	// render
	void render() override;

	// save
	void save(const string& file);

	// es como la constructora del antiguo game, lee la partida 
	// y carga todos los objetos y los prepara
	bool onEnter() override;

	// limpia los objetos
	bool onExit() override;

	//
	string getID() const override;


	// ------------------------------- GETTERS Y SETTERS --------------------------
	// genera un int aleatorio con un minimo y un maximo
	int getRandomRange(int min, int max);


	// ------------------------------ COLISIONES Y COMBATE ---------------------------
	// collisiones
	bool damage(SDL_Rect rect, char frenemy);

	// guatafac
	void hasDied(GameList<SceneObject, true>::anchor i);

	// dispara el laser (lo crea)
	void fireLaser(Point2D<double> pos, char frenemy);


	// ------------------------------------- OTROS ----------------------------
	// delete scene objects
	void deleteSceneObjects();

	// guarda la partida (esto va dentro del handle events de la S de save pero es por orden)
	void saveThisGame();

	// carga las texturas
	void loadTextures();

	// carga el cualquier archivo
	void loadAnyFile(const string& file, const string& root);

};

#endif