#ifndef GAME_H
#define GAME_H

#include <list>
#include <array>
#include <vector>
#include "texture.h"
#include "GameObject.h"
#include <random>
//#include "SceneObject.h"

using namespace std;
using uint = unsigned int;

// promesa del caballero (item del lol)
class SceneObject;




// constantes de tamaño de pantalla -> inicializar en h
	// tiene que ser estática porque es un atributo (constante para todos los objetos de la clase)
static constexpr uint winWidth = 800;
static constexpr uint winHeight = 600;


// ----------------------------------- x X x G A M E x X x ------------------------------------
class Game
{
	//  ------------------  P L A C E H O L D E R R R R R R R R R R R  omg ---------------------
public:
	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 6;

	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	array<Texture*, NUM_TEXTURES> textures{};

	// atributos privados
private:

	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer !!! TODO EN EL MISMO RENDERER

	// booleano salida del juego
	bool exit;

	// 
	list<SceneObject*> sceneObjectsList;

	// puntero al mothership
	GameObject* milfship;

	// TAL VEZ i n f o b a r heheheheheheh
	//

	// crea semilla
	mt19937_64 randomGenerator;

	uint32_t startTime, frameTime;	// manejo de tiempo en run

	// ?¿?¿?¿?¿?¿?¿?¿?¿?¿ (se pone aqui o en el milf???????????????????????????¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿)
	int SCORE;	// score general del player

	// metodos publicos 
public:
	// ---- constructora ----
	// la contructora del game debe inicializar los objetos de juego en una posición
	Game::Game();

	// ---- destructora ----
	Game::~Game();

	// ---- run ----
	// bucle principal del juego
	void run();

	// ---- update ----
	// actualiza el juego
	void update();

	// ---- render ----
	// renderiza la pantalla
	void render();

	// ---- CARGAR Y SALVAR PARTIDAS ----
	void save();
	void load();

	// acaba el juego (setea exit a true vamos)
	void EndGame();
};

#endif