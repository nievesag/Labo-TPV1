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
#include "SceneObject.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "EndState.h"
#include "PauseState.h"


class Button;

using namespace std;
using uint = unsigned int;

// SI ESTÁN DENTRO DE LA CLASE:
// constantes de tamanyo de pantalla -> inicializar en h
// tiene que ser estática porque es un atributo (constante para todos los objetos de la clase)
constexpr uint winWidth = 800;
constexpr uint winHeight = 600;

// ---- FRAMES ----
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
				UFO_SPEED = 6 * TIME_BT_FRAMES,		// velocidad de ufo
				REWARD_SPEED = 1 * TIME_BT_FRAMES;	// velocidad de reward
						

// ---- TEXTURAS ----
// enum texture name -> el indice tiene la info de la textura
enum TextureName { Alien1, Alien2, Alien3, Nave, Escudo, Fondo, UfoT, BOMBA, Reward, Shield, MainMenu, NewGame,
						LoadGame, ExitGame, ContGame, SaveGame, GoBack, GameIsOver, YouWon, Code };

// ---- SAVE & READ FILES ----
// archivo de strings con las roots de las carpetas etc
static string SAVED_FOLDER = "..\\saved\\";

// ---- APPLICATION ----
class SDLApplication
{
	// atributos privados
private:
	// ---- MAQUINA DE ESTADOS ----
	// crea un puntero a la maquina de estados
	GameStateMachine* gsMachine;

	// ---- MANEJO DEL TIEMPO EN RUN ----
	uint32_t startTime, frameTime;

	// ---- SDL ----
	SDL_Window* window = nullptr; // puntero a ventana
	SDL_Renderer* renderer = nullptr; // puntero a renderer TODO EN EL MISMO RENDERER
	int winX, winY; // posición de la ventana
	SDL_Event event; // evento a pollear

	// ---- TEXTURAS ----
	// cantidad de texturas que va a haber
	static const int NUM_TEXTURES = 20;

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

		TextureSpec{"..\\images\\aliens2.png", 2, 3},	  // alien 1 // 32,32			-> 0
		{ "..\\images\\aliens2.png", 2, 3 },			  // alien 2 // 44,32			-> 1
		{ "..\\images\\aliens2.png", 2, 3 },			  // alien 3 // 48,32			-> 2
		{ "..\\images\\spaceship.png", 1, 1 },			  // nave	 // 34,21			-> 3
		{ "..\\images\\bunker.png", 4, 1 },				  // bunker  // 88,57			-> 4
		{ "..\\images\\stars.png", 1, 1 },				  // fondo						-> 5
		{ "..\\images\\ovni2.png", 3, 1 },				  // ufo	 // 48,26			-> 6
		{ "..\\objetos\\bomb.png", 3, 1 },				  // BOMBA						-> 7
		{ "..\\objetos\\shield_reward.png", 3, 1 },		  // reward BOMBA				-> 8
		{ "..\\objetos\\shield.png", 3, 1 },			  // escudo						-> 9
		{ "..\\fondos\\mainMenu.png", 1, 1 },			  // fondo del menu inicial		-> 10
		{ "..\\textos\\nuevaPartida.png", 1, 1 },		  // texto: NUEVA PARTIDA		-> 11
		{ "..\\textos\\cargarPartida.png", 1, 1},		  // texto: CARGAR PARTIDA		-> 12
		{ "..\\textos\\salir.png", 1, 1 },				  // texto: SALIR				-> 13
		{ "..\\textos\\continuar.png", 1, 1 },			  // texto: CONTINUAR			-> 14
		{ "..\\textos\\guardarPartida.png", 1, 1 },		  // texto: GUARDAR				-> 15
		{ "..\\textos\\volverAlMenu.png", 1, 1 },		  // texto: VOLVER AL MENU		-> 16
		{ "..\\textos\\gameOver.png", 1, 1 },			  // texto: GAME OVER			-> 17
		{ "..\\textos\\hasGanado.png", 1, 1 },			  // texto: HAS GANADO			-> 18
		{ "..\\textos\\codigo.png", 1, 1 }				  // texto: CODIGO				-> 19
	};

	bool exit = false;

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

	// ---- handleEvents ----
	// input del jugador
	void handleEvents();

	// NO SE NECESITA???????????????????
	#pragma region borrar?
	// ---- update ----
	// actualiza el juego
	void update();

	// ---- render ----
	// renderiza la pantalla
	void render();
	#pragma endregion

	// ---- SETTERS Y GETTERS ----
	#pragma region setters y getters
	// tamaño de ventana
	uint getWinWidth() { return winWidth; }
	uint getWinHeight() { return winHeight; }
	
	// renderer
	SDL_Renderer* getRenderer() { 
		return renderer; };

	// maquina de estados
	GameStateMachine* getgsMachine() { return gsMachine; }

	// get texturas
	array<Texture*, NUM_TEXTURES> getTextures() { return textures; }
	Texture* getTexture(TextureName tex) { return textures[tex]; }
	Texture* getTexture(int tex) { return textures[tex]; }
	TextureSpec getTextureSpec(int i) { return textureSpec[i]; }
	int getNumText() { return NUM_TEXTURES; }

	// set texturas
	void setTexture(int pos, Texture* tex) {

		textures[pos] = tex;
	}
	#pragma endregion

// ---- METODOS PRIVADOS ----
private:
	// ---- loadTexture ----
	// se cargan las texturas y se guardan en los arrays
	void loadTextures();
};

#endif