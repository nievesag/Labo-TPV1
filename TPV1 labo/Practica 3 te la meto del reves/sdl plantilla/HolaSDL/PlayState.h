#ifndef PLAYSTATE_H
#define PLAYSTATE_H

// includes
#include <SDL.h>
#include <random>
#include <fstream>
#include <string>
#include "checkML.h"

// 
#include "GameState.h"
#include "SDLApplication.h"

//
#include "SceneObject.h"
#include "gameList.h"
#include "Alien.h"
#include "ShooterAlien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"
#include "Ufo.h"

using namespace std;
using uint = unsigned int;

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


	// -------------------------------------- CARGA Y DESCARGA ---------------------------
	// archivo de strings con las roots de las carpetas etc
	string SAVED_FOLDER = "..\\saved\\";


protected:
	// este es el nuevo game, pero.... que hace el atiguo ????

	// en Game: punteros a window y render
	//			array de texturas
	//			maquina de estados

	SDLApplication* app;

	// lista de objetos de escena (cannon, aliens, bunkeres, laser)
	GameList<SceneObject, true> sceneObjectsList;

	// archivo que leer, lo pasas del menu inicial, ya sea carga o no
	string loadFile;

	// lista de iteradores de objetos que eliminar
	//list<list<SceneObject*>::iterator> objectsToErase;
	// lista de anchors de objetos a eliminar
	//list<GameList<SceneObject, true>::anchor>objectsToErase;

	//
	//GameList<SceneObject, true> toBeErased;

	// puntero al mothership
	Mothership* mother = nullptr;

	mt19937_64 randomGenerator;	// crea semilla

	int SCORE = 0;	// score general del player

	char k; // crea un char para guardar el numero

	void HandleEvent(const SDL_Event &event) override;

public:
	// constructora
	PlayState::PlayState(SDLApplication* game, string loadFile);

	// -------------------------------- HERENCIA --------------------------------
	// update
	void update() override;

	// render
	void render() const override;


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

	//
	void EndGame();

	SDL_Renderer* getAppRenderer();

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
	void loadAnyFile(const string& fileAndRoot);

	//
	void increaseScore(int score);
	
	// 
	void renderBackground() const;

	// 
	bool mayGrantReward(SDL_Rect rect);
};

#endif