#include "checkML.h"
#include "SDLApplication.h"

#include "FileNotFoundError.h"
#include "SDLError.h"
#include "FileFormatError.h" 

using namespace std;

// constructora del game
SDLApplication::SDLApplication()
{
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);

	// crea la ventana
	window = SDL_CreateWindow("Space Invaders", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);

	// crea el renderer para la ventana
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// ERRORES DE SDL
	if (window == nullptr || renderer == nullptr)
		throw SDLError("Error cargando ventana de juego o renderer "s + SDL_GetError());


	// ---------------------- TEXRTURAS ----------------------------------

	loadTextures();


	// --------------------- MAQUINA DE ESTADOS ---------------------------
	// !!! el render de los estados debe ser const pero hay un error y no tengo ganas ahora de arreglarlo
	// crea una maquina de estados
	gsMachine = new GameStateMachine();

	//GameState* mms = new MainMenuState(this);

	GameState* ps = new PlayState(this, "..\\mapas\\prueba");

	//GameState* es = new EndState(this);

	//GameState* pause = new PauseState(this);

	//
	gsMachine->pushState(mms);
}

SDLApplication::~SDLApplication()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); // cierra pantalla
}

// MANEJAR EVENTOS 
void SDLApplication::handleEvents()
{
	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else {
			gsMachine->handleEvent(event);
		}
	}
}

// RUN
void SDLApplication::run()
{
	// get ticks al inicio del bucle
	startTime = SDL_GetTicks();

	while (!exit)
	{
		handleEvents();

		// tiempo desde ultima actualizacion
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime > TIME_BT_FRAMES) {
			update(); // actualiza todos los objetos de juego
			startTime = SDL_GetTicks();
		}
		render(); // renderiza todos los objetos de juego
	}
}

void SDLApplication::loadTextures()
{
	// bucle para rellenar el array de texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {

		// crea la textura con el url, width y height
		Texture* tex = new Texture(renderer, textureSpec[i].url, textureSpec[i].nh, textureSpec[i].nw);

		// la mete en el array
		textures[i] = tex;
		if (textures[i] == nullptr) {

			throw SDLError("Error cargando texturas "s + SDL_GetError());
		}
	}
}

// --------------------------------------------- NO SE NECESITA?
void SDLApplication::update()
{
	//
	gsMachine->update();
}

void SDLApplication::render()
{
	//limpia la pantalla
	SDL_RenderClear(renderer);

	// renderiza
	gsMachine->render();

	// actualiza la pantalla
	SDL_RenderPresent(renderer);
}