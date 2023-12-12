#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

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
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"

using namespace std;
using uint = unsigned int;

// constantes de tamanyo de pantalla -> inicializar en h
// tiene que ser estática porque es un atributo (constante para todos los objetos de la clase)
static constexpr uint winWidth = 800;
static constexpr uint winHeight = 600;

// ------------------- FRAMES ---------------------
// gestion de frames y framerate 
static constexpr int FRAMERATE = 60,						// frames por segundo
					TIME_BT_FRAMES = 100 / FRAMERATE,		// tiempo entre frames
					ALIEN_FR = 8 * FRAMERATE,				// cantidad de frames entre updates del alien
					END_GAME = 300,							// distancia de los aliens para acabar
					ALIEN_RF = 5 * FRAMERATE,				// cada cuanto se actualiza el alien
					SHOOT_FRAMES = TIME_BT_FRAMES * 100,	// cantidad de frames entre updates
					ANIMATION_DURATION = 10;


static constexpr double LASER_SPEED = 1 * TIME_BT_FRAMES,	// velocidad de laser
						ALIEN_SPEED = 10 * TIME_BT_FRAMES,	// velocidad de aliens
						CANNON_SPEED = 1 * TIME_BT_FRAMES,	// velocidad de cannon
						UFO_SPEED = 6 * TIME_BT_FRAMES;		// velocidad de ufo
						

// ---------------------------- SAVE & READ FILES ----------------------------
// archivo de strings con las roots de las carpetas etc
static string SAVED_FOLDER = "..\\saved\\";

// -------------------------------- G A M E --------------------------------
class SDLApplication
{
public:
	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 7;

	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	array<Texture*, NUM_TEXTURES> textures{};

	// atributos privados
private:

	// -------------------------------------- MAQUINA DE ESTADOS --------------------------
	// placeholder ?

	// crea un puntero a la maquina de estados
	GameStateMachine* gsMachine;








	// -------------------------------------- SDL --------------------------------
	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer !!! TODO EN EL MISMO RENDERER
	SDL_Event event;

	int winX, winY; // Posición de la ventana

	// enum texture name -> el indice tiene la info de la textura
	enum TextureName { Alien1, Alien2, Alien3, Nave, Escudo, Fondo, UfoT };

	struct TextureSpec
	{
		const char* url;

		// width height
		int nw, nh;
	};

	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo TextureSpec 
	// ubicacion, col, fil
	array<TextureSpec, SDLApplication::NUM_TEXTURES> textureSpec{
		TextureSpec{"..\\images\\aliens2.png", 2, 3},	  // alien 1 // 32,32
		{ "..\\images\\aliens2.png", 2, 3 },			  // alien 2 // 44,32
		{ "..\\images\\aliens2.png", 2, 3 },			  // alien 3 // 48,32
		{ "..\\images\\spaceship.png", 1, 1 },			  // nave	 // 34,21
		{ "..\\images\\bunker.png", 4, 1 },				  // bunker  // 88,57
		{ "..\\images\\stars.png", 1, 1 },				  // fondo 
		{ "..\\images\\ovni2.png", 3, 1 }				  // ufo	 // 48,26
	};

	// booleano salida del juego
	bool exit = false;

	// lista de punteros a oyentes
	list<EventHandler*> eventListeners;
public:
	// para registrar oyentes no se si se hace aqui
	void addEventListener(EventHandler* event);

	TextureSpec getTexture(TextureSpec textureSpec) const { return textureSpec; }

	// ref a state machine

// ------------------------- LA MAYORIA DE LO DE ABAJO NO LO NECESITA -------------

private:
	int type;

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
	
	// lista de objetos de escena (cannon, aliens, bunkeres, laser)
	list<SceneObject*> sceneObjectsList;

	// lista de iteradores de objetos que eliminar
	list<list<SceneObject*>::iterator> objectsToErase;

	// puntero al mothership
	Mothership* mother;

	// MANEJO DEL TIEMPO EN RUN
	mt19937_64 randomGenerator;	// crea semilla
	uint32_t startTime, frameTime;	

	int SCORE = 0;	// score general del player

	char k = ' '; // crea un char para guardar el numero

	// metodos publicos 
public:
	// ---- constructora ----
	// la contructora del game debe inicializar los objetos de juego en una posición
	SDLApplication::SDLApplication();

	// ---- destructora ----
	SDLApplication::~SDLApplication();

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
	void load(const string& file, const string& root);

	// ---- handleEvents ----
	// input del jugador
	void handleEvents();

	// ---- hasDied ----
	// metodo que llaman los objetos cuando han de ser eliminados
	void hasDied(list<SceneObject*>::iterator& it);

	// ---- EndGame ----
	// acaba el juego (setea exit a true)
	void EndGame();

	// devuelve si choca con algo (colisiones)
	bool damage(Laser* myLaser);

	// ---- dispara el laser ----
	// dispara el laser (lo crea)
	void fireLaser(Point2D<double> pos, char frenemy);

	// ------------------- GETTERS -------------------
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

	// renderea el fondo
	void renderBackground();

	// delete scene objects
	void deleteSceneObjects();

	// guarda la partida (esto va dentro del handle events de la S de save pero es por orden)
	void saveThisGame();

	// carga la paprtida indicada (lo mismo que la anterior)
	void loadThisGame();

	// carga cualquier archivo
	void loadAnyFile(const string& file, const string& root);

	// ---- Main menu ----
	void mainMenu();
};

#endif