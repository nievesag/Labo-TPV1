#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "../Vector2D.h"
#include "../texture.h"
#include <list>
#include "gameList.h"
//#include "Weapon.h"

class Weapon;
class GameState;
class PlayState;

class SceneObject : public GameObject
{
private:

	int defaultdestW = 4,
		defaultdestH = 10;

	// atributos protegidos
protected:
	// posicion del objeto
	Point2D<double> position;

	// dimension del objeto (height & width)
	int width, height;

	// vidas del objeto
	int vidas;

	Texture* texture;

	// rectangulo del render
	SDL_Rect destRect;

	// puntero al playstate
	PlayState* playState;

	// anchor
	GameList<SceneObject, true>::anchor sceneanc = nullptr;

	// metodos publicos
public:
	SceneObject(Point2D<double> position, int width, int height, int vidas, Texture* texture,  PlayState* game)
		: position(position), width(width), height(height), vidas(vidas), texture(texture), GameObject(game), playState(game)
	{ 
		// si hay textura entonces no es un laser y tiene dimensiones
		if (texture != nullptr) {
			// setea las dimensiones
			destRect.w = texture->getFrameWidth();
			destRect.h = texture->getFrameHeight();
		}
		// si no tiene textura entonces es un laser y le da las dimensiones marcadas
		else
		{
			// setea las dimensiones del laser
			destRect.w = defaultdestW;
			destRect.h = defaultdestH;
		}

		destRect.x = position.getX();
		destRect.y = position.getY();
	}

	// para fuera de playState
	SceneObject(Point2D<double> position, int width, int height, Texture* texture, GameState* game)
		: position(position), width(width), height(height), texture(texture), GameObject(game)
	{
		// si hay textura entonces no es un laser y tiene dimensiones
		if (texture != nullptr) {
			// setea las dimensiones
			destRect.w = texture->getFrameWidth();
			destRect.h = texture->getFrameHeight();
		}
		// si no tiene textura entonces es un laser y le da las dimensiones marcadas
		else
		{
			// setea las dimensiones del laser
			destRect.w = defaultdestW;
			destRect.h = defaultdestH;
		}

		destRect.x = position.getX();
		destRect.y = position.getY();
	}

	// PARA REWARDS
	SceneObject(Point2D<double> position, int width, int height, PlayState* game)
		: position(position), width(width), height(height), GameObject(game), playState(game)
	{
		// si hay textura entonces no es un laser y tiene dimensiones
		if (texture != nullptr) {
			// setea las dimensiones
			destRect.w = texture->getFrameWidth();
			destRect.h = texture->getFrameHeight();
		}
		// si no tiene textura entonces es un laser y le da las dimensiones marcadas
		else
		{
			// setea las dimensiones del laser
			destRect.w = defaultdestW;
			destRect.h = defaultdestH;
		}

		destRect.x = position.getX();
		destRect.y = position.getY();
	}

	// --------------> los override van en las clases hijas que lo especifiquen <--------------
	// (en alien, cannon, laser, bunker)
	// metodo virtual: para que lo usen los hijos
	// const: porque no es un metodo que cambie datos

	// ---- render ----
	// renderiza
	virtual void render() const;

	// ---- update ----
	// actualiza
	virtual void update();

	// ---- save ----
	// guarda objeto
	virtual void save(std::ostream& out) const;

	// ---- hit ----
	// colisiones
	virtual bool hit(SDL_Rect* ataque, Weapon* frenemy);

	virtual void updateRect();

	// devuelve rect (posicion) de cada objeto
	//SDL_Rect getRect() { SDL_Rect rect = destRect; return rect; };

	SDL_Rect getRect();

	// ----- Iterador de la lista ------
	// Un iterador funciona como un puntero que apunta a los items de la lista 
	// begin(), end(), advance(), next(), prev(), inserter()
	void setListAnchor(GameList<SceneObject, true>::anchor newanc) // list<SceneObject*>::iterator& newit
	{
		// setea el iterador de la posicion del objeto en la lista
		sceneanc = newanc;
	};

	Point2D<double> getPosition() const { return position; };

	Texture* getTexture() const { return texture; };
};
#endif