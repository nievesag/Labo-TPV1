#ifndef GAME_H
#define GAME_H

#include "checkML.h"
#include <SDL.h>
#include <array>
#include "texture.h"

// #include <iostream>

using namespace std;
using uint = unsigned int;

class Game
{
	// atributos privados -> QUE NO VARIABLES
private:
	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer !!!!!!! TODO EN EL MISMO RENDERER

	// tiene que ser estática porque es un atributo, constante para todos los objetos de la clase
	// inicializarlas aqui
	static constexpr uint winWidth = 800; 
	static constexpr uint winHeight = 600;

	bool exit; // se llama exit (salida para los que no sepan catalan)

	struct TextureSpec 
	{
		const char* url;
		int nw, nh;
	};

	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 5;

	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	array<TextureSpec, NUM_TEXTURES> textureSpec{};

	// enum texture name -> el indice tiene la info de la textura
	enum TextureName Alien1, Alien2, Alien3, Nave, Bunker;
	
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// array de las texturas como tal de tipo texture (añadir el include y meterlas en la carpeta)
	array<Texture*, NUM_TEXTURES> textures;

	// INI ELEMENTOS DE JUEGO (vector2D): (TODO) 
	// ??

	// metodos publicos
public:
	// ---- constructora ----
	// se cargan las texturas y se guardan en los arrays 
	// necesario iniciar ahi el exit???? (falla si no hay nada) (no poner NUM_TEXTURES pq es estatica y no modificable)
	// igual que en el vector yo haría un setPlayer(posicion(Vector2D)) y un getPlayer(posicion) 
	// la contructora del game debe inicializar los objetos de juego en una posición

	Game::Game() 
		: exit(false) { }


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
	void getDirection();

	// ---- cannotMove ----
	// confirma si se pueden seguir moviendo en la misma direccion los aliens
	bool cannotMove();

	// ---- fireLaser -----
	// dispara laseres wow
	void fireLaser();
};

#endif // GAME_H