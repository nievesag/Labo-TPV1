#ifndef GAME_H
#define GAME_H

#include <list>

using namespace std;
using uint = unsigned int;

class SceneObject;

class Game
{
	// atributos privados
private:
	list<SceneObject*> sceneObjectsList;

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