#include "checkML.h"
#include "SDLApplication.h"

#include "FileNotFoundError.h"
#include "SDLError.h"
#include "FileFormatError.h" 
#include "button.h"

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

	boton = new Button(this);
	//cannon = new Cannon();

	//gsMachine->addEventListener(boton);
	//gsMachine->addEventListener(cannon);




	// --------------------- MAQUINA DE ESTADOS ---------------------------
	// !!! el render de los estados debe ser const pero hay un error y no tengo ganas ahora de arreglarlo
	// crea una maquina de estados
	gsMachine = new GameStateMachine();

	GameState* mms = new MainMenuState(this);

	GameState* ps = new PlayState(this);

	//
	gsMachine->pushState(ps);
}

SDLApplication::~SDLApplication()
{


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); // cierra pantalla
}

#pragma region LOGICA DE JUEGO
// ----- LOGICA DE JUEGO -----
// cargar | manejar eventos -> actualizar -> pintar -> manejar eventos etc

// MANEJAR EVENTOS 
void SDLApplication::handleEvents()
{
	// EVENTOS NO TOCAR O LA TENEMOS ------------
	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else
			// emite el evento para todos los subscriptores
			emit(event);
	}

	/*
	while (SDL_PollEvent(&event) && !exit) {

		// escanea y evalua que tecla has tocado
		SDL_Scancode key = event.key.keysym.scancode;

		// si se pulsa una tecla
		if (key == SDL_SCANCODE_S) {

			gsMachine->replaceState(new PlayState(this));
		}
	}
*/

	// HASTA AKI ------------
	/*
		// lo antiguo !!!! limpiar
		ifstream in("..\\mapas\\original.txt");

		// escanea y evalua que tecla has tocado
		SDL_Scancode key = event.key.keysym.scancode;

		// si se solicita quit bool exit = true
		if (event.type == SDL_QUIT) EndGame();

		// si se pulsa una tecla
		else if (event.type == SDL_KEYDOWN && (key == SDL_SCANCODE_S || key == SDL_SCANCODE_L)) {

			// si es la tecla S (save)
			if (key == SDL_SCANCODE_S) {

				// guarda la partida (incluye la gestion del 'menu')
				saveThisGame();
			}
			// si es la tecla L (load)
			else if (key == SDL_SCANCODE_L) {

				// carga la partida indicada
				loadThisGame();
			}
		}
		// MANEJO DE EVENTOS DE OBJETOS DE JUEGO
		else { 
			// el objeto en begin es el cannon
			list<SceneObject*>::iterator it = sceneObjectsList.begin();

			// DYNAMIC CAST: se comprueba en ejecucion que el objeto 
			// en la posicion begin del iterador apunte a un objeto de tipo Cannon
			// si lo es se accede al metodo 
			dynamic_cast<Cannon*>(*it)->handleEvent(event);
		}
		*/
}

void SDLApplication::connect(SDLEventCallback cb)
{
	callbacks.push_back(cb);
}

void SDLApplication::emit(const SDL_Event& event) const
{
	// Llama a todas las funciones registradas
	for (const SDLEventCallback& callback : callbacks)
		callback(event);
}

// --------------------------------------------- NO SE NECESITA?
#pragma region COJONES

// RUN
void SDLApplication::run()
{
	// get ticks al inicio del bucle
	//startTime = SDL_GetTicks();

	/*
	
	
	
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
*/
	
	/*
	// escribe game over
	cout << "GAME OVER" << endl;
	// escribe puntuacion
	PlayerScore();
	*/
}

// ACTUALIZAR 
void SDLApplication::update()
{
	//
	gsMachine->update();

}

void SDLApplication::render()
{

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