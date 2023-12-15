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

class Button;

using namespace std;
using uint = unsigned int;

// SI ESTÁN DENTRO DE LA CLASE:
// constantes de tamanyo de pantalla -> inicializar en h
// tiene que ser estática porque es un atributo (constante para todos los objetos de la clase)
constexpr uint winWidth = 800;
constexpr uint winHeight = 600;

// ------------------- FRAMES ---------------------
// gestion de frames y framerate 
constexpr int FRAMERATE = 60,						// frames por segundo
					TIME_BT_FRAMES = 100 / FRAMERATE,		// tiempo entre frames
					ALIEN_FR = 8 * FRAMERATE,				// cantidad de frames entre updates del alien
					END_GAME = 300,							// distancia de los aliens para acabar
					ALIEN_RF = 5 * FRAMERATE,				// cada cuanto se actualiza el alien
					SHOOT_FRAMES = TIME_BT_FRAMES * 100,	// cantidad de frames entre updates
					ANIMATION_DURATION = 10;


constexpr double LASER_SPEED = 1 * TIME_BT_FRAMES,	// velocidad de laser
						ALIEN_SPEED = 10 * TIME_BT_FRAMES,	// velocidad de aliens
						CANNON_SPEED = 1 * TIME_BT_FRAMES,	// velocidad de cannon
						UFO_SPEED = 6 * TIME_BT_FRAMES;		// velocidad de ufo
						

// ----------------------------------- TEXTURAS -------------------------------
 
// enum texture name -> el indice tiene la info de la textura
enum TextureName { Alien1, Alien2, Alien3, Nave, Escudo, Fondo, UfoT };

// ---------------------------- SAVE & READ FILES ----------------------------
// archivo de strings con las roots de las carpetas etc
static string SAVED_FOLDER = "..\\saved\\";

// -------------------------------- G A M E --------------------------------
class SDLApplication
{
public:

	// Lista de funciones a llamar cuando se produzca un evento
	std::vector<SDLEventCallback> callbacks;


	// atributos privados
private:

	// -------------------------------------- MAQUINA DE ESTADOS --------------------------
	// placeholder ?

	// crea un puntero a la maquina de estados
	GameStateMachine* gsMachine;

	// MANEJO DEL TIEMPO EN RUN
	
	uint32_t startTime, frameTime;

	// -------------------------------------- SDL --------------------------------
	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer !!! TODO EN EL MISMO RENDERER
	SDL_Event event;
	Button* boton;

	int winX, winY; // Posición de la ventana

	// ---------------------------------------- TEXTURAS -----------------------------
	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 7;

	// ARRAY DE TEXTURAS -> array estatico de tam NUM_TEXTURES de elementos de tipo Texture* 
	array<Texture*, NUM_TEXTURES> textures{};

	struct TextureSpec
	{
		const char* url;

		// width height
		int nw, nh;
	};

	// ARRAY DE TEXTURAS -> array est�tico de tam NUM_TEXTURES de elementos de tipo TextureSpec 
	// ubicacion, col, fil
	array<TextureSpec, NUM_TEXTURES> textureSpec{

		TextureSpec{"..\\images\\aliens2.png", 2, 3},	  // alien 1 // 32,32
		{ "..\\images\\aliens2.png", 2, 3 },			  // alien 2 // 44,32
		{ "..\\images\\aliens2.png", 2, 3 },			  // alien 3 // 48,32
		{ "..\\images\\spaceship.png", 1, 1 },			  // nave	 // 34,21
		{ "..\\images\\bunker.png", 4, 1 },				  // bunker  // 88,57
		{ "..\\images\\stars.png", 1, 1 },				  // fondo 
		{ "..\\images\\ovni2.png", 3, 1 }				  // ufo	 // 48,26
	};

	bool exit = false;

public:
	// lista de punteros a oyentes
	list<EventHandler*> eventListeners;

// ------------------------- LA MAYORIA DE LO DE ABAJO NO LO NECESITA -------------

private:
	
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

	//
	void emit(const SDL_Event& event) const;

	// Se suscribe a los eventos SDL del juego
	void connect(SDLEventCallback cb);

	// ------------------- GETTERS -------------------
	uint getWinWidth() { return winWidth; }
	uint getWinHeight() { return winHeight; }
	
	SDL_Renderer* getRenderer() { 
		
		cout << "AAAAA" << endl;

		return renderer; };


	// getters de texturas
	array<Texture*, NUM_TEXTURES> getTextures() { return textures; }

	Texture* getTexture(TextureName tex) { return textures[tex]; }

	Texture* getTexture(int tex) { return textures[tex]; }

	void setTexture(int pos, Texture* tex) {

		textures[pos] = tex;
	}

	TextureSpec getTextureSpec(int i) { return textureSpec[i]; }

	int getNumText() { return NUM_TEXTURES; }


// ------ METODOS PRIVADOS -------
private:

	// ---- loadTexture ----
	// se cargan las texturas y se guardan en los arrays
	void loadTextures();
};

#endif