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
#include "Bomb.h"
#include "Ufo.h"
#include "Rewards.h"

class Cannon;
class Mothership;

using namespace std;
using uint = unsigned int;

class PlayState : public GameState{
private:

	// ---- GENERAL -----

	// id del estado
	const string s_playID = "PLAY";

	// default variables
	int defaultLives = 1,	    // default number of lives
		defaultFrame = 0,	    // default starting frame
		ans = 0,			    // respuesta en los menuses
		laserW = 4,			    // dimensiones del laser
		laserH = 10,
		defaultCooldown = 10,   // default cooldown (si es -1 se genera uno)
		defaultUfoHeight = 10,
		defaultLaserW = 4,
		defaultLaserH = 10,
		defaultBombLives = 2,
		defaultMothershipLevel = 0,
		minProbabilityBomb = 1,
		maxProbabilityBomb = 2,
		minProbabilityReward = 1,
		maxProbabilityReward = 1;

	// ---- CARGA Y GUARDADO ----
	// archivo de strings con las roots de las carpetas etc
	string SAVED_FOLDER = "..\\saved\\";

protected:
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

	// puntero al cannon
	Cannon* cannonRef;

	mt19937_64 randomGenerator;	// crea semilla


	char k; // crea un char para guardar el numero

	void HandleEvent(const SDL_Event &event) override;

public:
	int SCORE = 0;	// score general del player

	// constructora
	PlayState::PlayState(SDLApplication* game, string loadFile);

	// update
	void update() override;

	// render
	void render() const override;
	void renderBackground() const;

	// save
	void save(const string& file);

	// es como la constructora del antiguo game, lee la partida 
	// y carga todos los objetos y los prepara
	bool onEnter() override;

	// limpia los objetos
	bool onExit() override;

	void goEndState(bool victory);

	// getter de id del estado
	string getID() const override;

	//
	void EndGame();

	// ---- GETTERS Y SETTERS GENERALES ----

	// genera un int aleatorio con un minimo y un maximo
	int getRandomRange(int min, int max);

	// getter del renderer de SDLApplication
	SDL_Renderer* getAppRenderer();

	// getter del SDLApplication
	SDLApplication* getApplication();

	// ---- CONTROL DE COLISIONES ----
	// colisiones
	bool damage(SDL_Rect rect, char frenemy);

	// avisa si se ha muerto un objeto
	void hasDied(GameList<SceneObject, true>::anchor i);

	// ---- GENERACION DE LASERES Y BOMBAS ----
	// dispara el laser (lo crea)
	void fireLaser(Point2D<double> pos, char frenemy);

	// dispara una bomba (la crea)
	void fireBomb(Point2D<double> pos);

	// ---- ELIMINACION OBJETOS ----
	// delete scene objects
	void deleteSceneObjects();

	// ---- GUARDADO Y CARGA DE PARTIDA ----
	// guarda la partida (esto va dentro del handle events de la S de save pero es por orden)
	void saveThisGame();

	// carga el cualquier archivo
	void loadAnyFile(const string& fileAndRoot);

	// ---- TEXTURAS ----
	// carga las texturas
	void loadTextures();

	// ---- SCORE ----
	void increaseScore(int score);

	int getScore() { return SCORE; }

	// ---- BOMB ----
	int getMinProbBomb() { return minProbabilityBomb; }

	int getMaxProbBomb() { return maxProbabilityBomb; }

	// ---- REWARDS ----
	bool mayGrantReward(SDL_Rect rect) const;

	// dropea reward (la crea)
	void dropReward(Point2D<double> pos);

	int getMinProbReward() { return minProbabilityReward; }

	int getMaxProbReward() { return maxProbabilityReward; }
};

#endif