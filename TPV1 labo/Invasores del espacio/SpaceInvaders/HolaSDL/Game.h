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


// ------------------------------ GAME ------------------------------
class Game
{
	// ----- TEXTURES -----
public:
	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 5;
	
	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	array<Texture*, NUM_TEXTURES> textures{};


	// ----- ATRIBUTOS PRIVADOS -----
private:
	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer !!!!!!! TODO EN EL MISMO RENDERER

	// constantes de tamaño de pantalla -> inicializar en h
	// tiene que ser estática porque es un atributo (constante para todos los objetos de la clase)
	static constexpr uint winWidth = 800;
	static constexpr uint winHeight = 600;

	// booleano salida del juego
	bool exit;

	int alienDir = 1;

	// enum texture name -> el indice tiene la info de la textura
	enum TextureName {Alien1, Alien2, Alien3, Nave, Escudo};

	// declaración de los elementos de juego
	Cannon* cannon;
	vector<Alien*> aliens;
	vector<Bunker*> bunkers;
	
	// ----- METODOS PUBLICOS -----
public:
	// ---- constructora ----
	// la contructora del game debe inicializar los objetos de juego en una posición
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
	void update();

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
	void fireLaser();

	// ---- getters ----
	/*
	Cannon* getCannon() {
		return cannon;
	}

	bool getExit() {
		return exit;
	}
	*/

	uint getWinWidth() {
		return winWidth;
	}

	uint getWinHeight() {
		return winHeight;
	}


	// ----- METODOS AUXILIARES -----
private:
	// ---- loadTexture ----
	// se cargan las texturas y se guardan en los arrays
	void loadTextures();

	// ----- loadMap ------
	// para poder cargar el mapa con la informacion necesaria
	// (crea los aliens y tal)
	// pretendo que aqui se lean los txt y que se hagan bucles para crear los bichitos
	void loadMap();
};

#endif // GAME_H 