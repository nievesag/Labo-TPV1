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

class PlayState : public GameState{

private:

	// id del estado
	const string s_playID;

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

protected:

	// este es el nuevo game... pero que hace el atiguo ????

	// en Game: punteros a window y render
	//			array de texturas
	//			maquina de estados

	SDLApplication* app;


	// lista de objetos de escena (cannon, aliens, bunkeres, laser)
	list<SceneObject*> sceneObjectsList;

	// lista de iteradores de objetos que eliminar
	list<list<SceneObject*>::iterator> objectsToErase;

	// puntero al mothership
	//Mothership* mother;

	// MANEJO DEL TIEMPO EN RUN
	mt19937_64 randomGenerator;	// crea semilla
	//uint32_t startTime, frameTime;

	int SCORE = 0;	// score general del player

	//char k; // crea un char para guardar el numero

public:

	// constructora
	PlayState::PlayState(SDLApplication* game) : GameState(game), app(game) {};

	// -------------------------------- HERENCIA --------------------------------
	// update
	void update();

	// render
	virtual void render();

	// save
	void save(const ostream& file);

	//
	virtual bool onEnter();

	//
	virtual bool onExit();

	//
	virtual string getID() const;


	// ------------------------------- GETTERS Y SETTERS --------------------------
	// genera un int aleatorio con un minimo y un maximo
	int getRandomRange(int min, int max);


	// ------------------------------ COLISIONES Y COMBATE ---------------------------
	// collisiones
	bool damage(SDL_Rect rect, char frenemy);

	// guatafac
	void hasDied(GameList<SceneObject>::anchor i);

	// dispara el laser (lo crea)
	void fireLaser(Point2D<double> pos, char frenemy);


	// ------------------------------------- OTROS ----------------------------
	// delete scene objects
	void deleteSceneObjects();

};

#endif