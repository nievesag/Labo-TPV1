#include "checkML.h"
#include <SDL.h>

// #include <iostream>

using namespace std;
using uint = unsigned int;


class Game
{
	// atributos privados -> QUE NO VARIABLES
private:
	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer !!!!!!! TODO EN EL MISMO RENDERER

	// tiene que ser est�tica porque es un atributo, constante para todos los objetos de la clase
	// inicializarlas aqui
	static constexpr uint winWidth = 800; 
	static constexpr uint winHeight = 600;

	bool exit; // se llama exit (salida para los que no sepan catalan)

	struct TextureSpec 
	{
		const char* url;
		int nw, nh;
	};

	// ARRAY DE TEXTURAS -> array est�tico de tam NUM_TEXTURES de elementos de tipo Texture* 

	// enum texture name -> el indice tiene la info de la textura
	
	// INI ELEMENTOS DE JUEGO (vector2D): (TODO) 


	// metodos publicos
public:
	// constructora
	// destructora
	// run
	// render
	// update
	// handleEvents -> input del jugador
	// getDirection
	// bool cannotMove
	// fireLaser
};

