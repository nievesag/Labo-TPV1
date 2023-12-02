#ifndef GAME_H
#define GAME_H

#include <list>
#include <array>
#include <vector>
#include <string>
#include "texture.h"
#include "GameObject.h"
#include <random>
#include <fstream>

// -------------
#include "Alien.h"
#include "ShooterAlien.h"
#include "Cannon.h"
#include "Laser.h"
#include "Bunker.h"
#include "SceneObject.h"
#include "Mothership.h"
#include "Ufo.h"


using namespace std;
using uint = unsigned int;

// constantes de tamaño de pantalla -> inicializar en h
// tiene que ser estática porque es un atributo (constante para todos los objetos de la clase)
static constexpr uint winWidth = 800;
static constexpr uint winHeight = 600;

// ------------------- FRAMES ---------------------
// gestion de frames y framerate 
static constexpr double FRAMERATE = 60,						// frames por segundo
						TIME_BT_FRAMES = 1 / FRAMERATE,		// tiempo entre frames
						LASER_SPEED = 6 * TIME_BT_FRAMES,	// velocidad de laser
						ALIEN_SPEED = 5 * TIME_BT_FRAMES,	// velocidad de aliens
						CANNON_SPEED = 10 * TIME_BT_FRAMES,	// velocidad de cannon
						UFO_SPEED = 6 * TIME_BT_FRAMES,		// velocidad de ufo
						ALIEN_FR = 8 * FRAMERATE,			// cantidad de frames entre updates del alien
						END_GAME = 300,						// distancia de los aliens para acabar
						ALIEN_RF = 5 * FRAMERATE;			// cada cuanto se actualiza el alien
						

// ------------------------------------- SAVE & READ FILES ----------------------------
// archivo de strings con las roots de las carpetas etc
static string SAVED_FOLDER = "..\\saved\\";


// ----------------------------------- G A M E  ------------------------------------
class Game
{
public:
	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 7;

	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	array<Texture*, NUM_TEXTURES> textures{};

	// atributos privados
private:

	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer !!! TODO EN EL MISMO RENDERER

	// enum texture name -> el indice tiene la info de la textura
	enum TextureName { Alien1, Alien2, Alien3, Nave, Escudo, Fondo, UfoT };

	// booleano salida del juego
	bool exit = false;

	// default variables
	int defaultLives = 1,	// default number of lives
		defaultFrame = 0;	// default starting frame
	

	// lista de objetos de escena (cannon, aliens, bunkeres, laser)
	list<SceneObject*> sceneObjectsList;

	// lista de iteradores de objetos que eliminar
	list<list<SceneObject*>::iterator> objectsToErase;

	// puntero al mothership
	Mothership* milfship;

	// MANEJO DEL TIEMPO EN RUN
	mt19937_64 randomGenerator;	// crea semilla
	uint32_t startTime, frameTime;	

	int SCORE = 0;	// score general del player

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
	// salva la partida guardando la info de todos los objetos en un archivo 
	void save(const string& file);

	// carga la partida leyendo el archivo indicado
	void load(const string& file);

	// ---- handleEvents ----
	// input del jugador
	void handleEvents();

	// ---- hasDied ----
	// metodo que llaman los objetos cuando han de ser eliminados
	void hasDied(list<SceneObject*>::iterator& it);

	// ---- EndGame ----
	// acaba el juego (setea exit a true)
	void EndGame();

	// devuelve si choca con algo (colisiones vamos)
	bool damage(Laser* myLaser);

	// ---- dispara el laser ----
	// dispara el laser (lo crea)
	void fireLaser(Point2D<double> pos, char frenemy);

	// ---- saca el ufo ----
	// crea ufo
	void showUfo(Point2D<double> pos);

	// ------------------- GETTERS ------------------
	uint getWinWidth() { return winWidth; }
	uint getWinHeight() { return winHeight; }
	
	SDL_Renderer* getRenderer() { return renderer; };

	int getRandomRange(int min, int max) {
		return uniform_int_distribution<int>(min, max)(randomGenerator);
	}

	// muestra en consola la puntuacion del jugador
	void PlayerScore();

	// aumenta el score con la cantidad indicada
	void increaseScore(int score);

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

	// delete scene objects
	void deleteSceneObjects();

	// guarda la partida (esto va dentro del handle events de la S de save pero es por orden)
	void saveThisGame();

	// carga la paprtida indicada (lo mismo que la anterior)
	void loadThisGame();

	// carga cualquier archivo
	void loadAnyFile(const string& file);
};

#endif