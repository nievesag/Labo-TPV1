#ifndef GAME_H
#define GAME_H

#include <list>
#include <array>
#include <vector>
#include "texture.h"
#include "GameObject.h"
#include <random>
#include <fstream>

// -------------
#include "Alien.h"
#include "Cannon.h"
#include "Bunker.h"
#include "SceneObject.h"
#include "Mothership.h"


//#include "SceneObject.h"

using namespace std;
using uint = unsigned int;

// promesa del caballero (item del lol)
class SceneObject;


// constantes de tamaño de pantalla -> inicializar en h
	// tiene que ser estática porque es un atributo (constante para todos los objetos de la clase)
static constexpr uint winWidth = 800;
static constexpr uint winHeight = 600;

// ------------------- FRAMES ---------------------
// gestion de frames y framerate 
static constexpr double FRAMERATE = 60,						// frames por segundo
						TIME_BT_FRAMES = 1 / FRAMERATE,		// tiempo entre frames
						LASER_SPEED = 6 * TIME_BT_FRAMES,	// velocidad de laser
						ALIEN_SPEED = 4 * TIME_BT_FRAMES,	// velocidad de aliens
						CANNON_SPEED = 10 * TIME_BT_FRAMES,	// velocidad de cannon
						END_GAME = 300,						// distancia de los aliens para acabar
						ALIEN_RF = 5 * FRAMERATE;			// cada cuanto se actualiza el alien


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

	// enum texture name -> el indice tiene la info de la textura
	enum TextureName { Alien1, Alien2, Alien3, Nave, Escudo, Fondo };

	// booleano salida del juego
	bool exit = false;

	// 
	list<SceneObject*> sceneObjectsList;

	/// lo he cambiado a Mothership* pero no sse si esta bien ????????????????????????????????????????????????????
	// puntero al mothership
	Mothership* milfship;

	// TAL VEZ i n f o b a r heheheheheheh
	//

	// crea semilla
	mt19937_64 randomGenerator;

	uint32_t startTime, frameTime;	// manejo de tiempo en run

	// ?¿?¿?¿?¿?¿?¿?¿?¿?¿ (se pone aqui o en el milf????????????????¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿)
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

	// ---- handleEvents ----
	// input del jugador
	void handleEvents();

	// metodo que llaman los objetos cuando han de ser eliminados
	void hasDied(list<SceneObject*>::iterator it);

	// acaba el juego (setea exit a true vamos)
	void EndGame();

	// ------------------- GETTERS ------------------

	uint getWinWidth() { return winWidth; }
	uint getWinHeight() { return winHeight; }
	

// ------ METODOS PRIVADOS -------
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

	// crea el sdl rect
	SDL_Rect SetDestRect(SceneObject* obj);

	// lo mismo pero con textura y posicion
	SDL_Rect SetDestRect(Texture* tex, Point2D<double> pos);
};

#endif