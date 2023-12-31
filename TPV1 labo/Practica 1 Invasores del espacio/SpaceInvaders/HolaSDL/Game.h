#ifndef GAME_H
#define GAME_H

// MEMORY LEAKS
#include "checkML.h"

// SDL
#include <SDL.h>
#include "SDL_image.h"

// AUX
#include <array>
#include <vector>
#include <fstream>
#include <random>
#include <time.h>
	// classes
#include "texture.h"
#include "Vector2D.h"

// GAME ELEMENTS
#include "Cannon.h"
#include "Alien.h"
#include "Bunker.h"
#include "Laser.h"

using namespace std;
using uint = unsigned int;


// gestion de frames y framerate 
static constexpr double FRAMERATE = 60,						// frames por segundo
						TIME_BT_FRAMES = 1 / FRAMERATE,		// tiempo entre frames
						LASER_SPEED = 6 * TIME_BT_FRAMES,	// velocidad de laser
						ALIEN_SPEED = 4 * TIME_BT_FRAMES,	// velocidad de aliens
						CANNON_SPEED = 10 * TIME_BT_FRAMES,	// velocidad de cannon
						END_GAME = 300,						// distancia de los aliens para acabar
						ALIEN_RF = 5 * FRAMERATE;			// cada cuanto se actualiza el alien

				
// constantes de tama�o de pantalla -> inicializar en h
	// tiene que ser est�tica porque es un atributo (constante para todos los objetos de la clase)
static constexpr uint winWidth = 800;
static constexpr uint winHeight = 600;

// ------------------------------ GAME ------------------------------
class Game
{
	// ----- TEXTURES -----
public:
	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 6;
	
	// ARRAY DE TEXTURAS -> array est�tico de tam NUM_TEXTURES de elementos de tipo Texture* 
	array<Texture*, NUM_TEXTURES> textures{};

	// ----- ATRIBUTOS PRIVADOS -----
private:
	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer !!! TODO EN EL MISMO RENDERER

	// booleano salida del juego
	bool exit;

	int laserCoolDown = 500,  // cooldown del laser
		alienDir = 1,		  // direccion de los aliens
		alienFrameUpdate = 0;

	// enum texture name -> el indice tiene la info de la textura
	enum TextureName {Alien1, Alien2, Alien3, Nave, Escudo, Fondo};

	// declaraci�n de los elementos de juego
	Cannon* cannon;
	vector<Alien*> aliens;
	vector<Bunker*> bunkers;
	vector<Laser*> laseres;

	// crea semilla
	std::mt19937_64 randomGenerator;
	
	uint32_t startTime, frameTime;	// manejo de tiempo en run


	int SCORE;	// score general del player

	// ----- METODOS PUBLICOS -----
public:
	// ---- constructora ----
	// la contructora del game debe inicializar los objetos de juego en una posici�n
	Game::Game();

	// ---- destructora ----
	Game::~Game();

	// ---- run ----
	// bucle principal del juego
	void run();

	// ---- render ----
	// renderiza la pantalla
	void render();

	// ---- update ----
	// actualiza el juego
	void update(bool damage);

	// ---- handleEvents ----
	// input del jugador
	void handleEvents();

	// ---- getDirection ----
	// direccion de movimiento de los alienigenas
	int getDirection();

	// ---- cannotMove ----
	// confirma si se pueden seguir moviendo en la misma direccion los aliens
	void cannotMove();

	// ---- fireLaser -----
	// dispara laseres wow
	void fireLaser(Point2D<double> pos, Vector2D<double> vel, bool frenemy);

	// gestiona las colisiones con el laser especificado
	bool checkColision(Laser* laser);

	// acaba el juego (setea exit a true vamos)
	void EndGame();

	uint getWinWidth() {
		return winWidth;
	}

	uint getWinHeight() {
		return winHeight;
	}

	// placeholder
	void setExit(bool aux) {
		exit = aux;
	}

	bool GetExit() {
		return exit;
	}

	// devuelve el puntero al renderer
	SDL_Renderer* getRenderer() { return renderer; }

	
	int Game::getRandomRange(int min, int max) {
		return uniform_int_distribution<int>(min, max)(randomGenerator);
	}

	int GetAlienFrameUpdate() { return alienFrameUpdate;  }

	// ----- METODOS AUXILIARES -----
private:
	// ---- loadTexture ----
	// se cargan las texturas y se guardan en los arrays
	void loadTextures();

	// ----- loadMap ------
	// para poder cargar el mapa con la informacion necesaria (crea los aliens y tal)
	// pretendo que aqui se lean los txt y que se hagan bucles para crear los bichitos
	void loadMap();

	// renderea el fondo
	void renderBackground();

	// muestra en consola la puntuacion del jugador
	void PlayerScore();
};

#endif // GAME_H 