#ifndef PLAYSTATE_H
#define PLAYSTATE_H

// includes
#include <SDL.h>
#include <random>
#include <fstream>
#include <string>
#include "../checkML.h"

// 
#include "GameState.h"
#include "../SDLApplication.h"

//
#include "../GameObjects/SceneObject.h"
#include "../GameObjects/gameList.h"
#include "../GameObjects/Alien.h"
#include "../GameObjects/ShooterAlien.h"
#include "../GameObjects/Bunker.h"
#include "../GameObjects/Cannon.h"
#include "../GameObjects/Laser.h"
#include "../GameObjects/Bomb.h"
#include "../GameObjects/Ufo.h"
#include "../GameObjects/Rewards.h"
#include "../GameObjects/InfoBar.h"

class Cannon;
class Mothership;

class PlayState : public GameState{
private:
	// ------------- GENERAL -------------
	// id del estado
	const std::string s_playID = "PLAY";

	// default variables
	int infobarSpacing = 10,	// espaciado para el infobar
		defaultLives = 1,	    // default number of lives
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

	// ------------- CARGA Y GUARDADO -------------
	// archivo de strings con las roots de las carpetas etc
	std::string SAVED_FOLDER = "..\\saved\\";

protected:
	SDLApplication* app;

	// lista de objetos de escena (cannon, aliens, bunkeres, laser)
	GameList<SceneObject, true> sceneObjectsList;

	// archivo que leer, lo pasas del menu inicial, ya sea carga o no
	std::string loadFile;

	// puntero al mothership
	Mothership* mother = nullptr;

	// puntero al cannon
	Cannon* cannonRef = nullptr;

	// puntero a infobar
	Infobar* infoBar;

	std::mt19937_64 randomGenerator;	// crea semilla

	char k; // crea un char para guardar el numero

	void HandleEvent(const SDL_Event &event) override;

public:
	int score = 0;	// score general del player

	// constructora
	PlayState(SDLApplication* game, std::string loadFile);

	~PlayState();

	// update
	void update() override;

	// render
	void render() const override;
	void renderBackground() const;

	// save
	void save(const std::string& file);

	// es como la constructora del antiguo game, lee la partida 
	// y carga todos los objetos y los prepara
	bool onEnter() const override;

	// limpia los objetos
	bool onExit() const override;

	void goEndState(bool victory);

	// getter de id del estado
	std::string getID() const override;

	//
	void EndGame();

	// ------------- GETTERS Y SETTERS GENERALES -------------
	// genera un int aleatorio con un minimo y un maximo
	int getRandomRange(int min, int max);

	// getter del renderer de SDLApplication
	SDL_Renderer* getAppRenderer() const;

	// getter del SDLApplication
	//SDLApplication* getApplication() const;

	// ------------- CONTROL DE COLISIONES -------------
	// colisiones
	bool damage(SDL_Rect rect, Weapon frenemy);

	// avisa si se ha muerto un objeto
	void hasDied(GameList<SceneObject, true>::anchor i);

	// ------------- GENERACION DE LASERES Y BOMBAS -------------
	// dispara el laser (lo crea)
	void fireLaser(Point2D<double> pos, char frenemy);

	// dispara una bomba (la crea)
	void fireBomb(Point2D<double> pos);

	// ------------- GUARDADO Y CARGA DE PARTIDA -------------
	// guarda la partida (esto va dentro del handle events de la S de save pero es por orden)
	void saveThisGame();

	// carga el cualquier archivo
	void loadAnyFile(const std::string& fileAndRoot);

	// ------------- TEXTURAS -------------
	// carga las texturas
	void loadTextures();

	// ------------- SCORE -------------
	int getScore() const { return score; }

	// ------------- BOMB -------------
	int getMinProbBomb() const { return minProbabilityBomb; }

	int getMaxProbBomb() const { return maxProbabilityBomb; }

	// ------------- REWARDS -------------
	bool mayGrantReward(SDL_Rect rect) const;

	// dropea reward (la crea)
	void dropReward(Point2D<double> pos);

	int getMinProbReward() const { return minProbabilityReward; }

	int getMaxProbReward() const { return maxProbabilityReward; }

	// ------------- KAMIKAZE -------------
	Point2D<double> getCannonPos() const;

	// crea kamikaze
	void createKamikaze(Point2D<double> pos);
};

#endif