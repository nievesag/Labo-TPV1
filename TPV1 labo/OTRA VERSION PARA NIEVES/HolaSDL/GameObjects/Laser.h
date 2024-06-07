#ifndef LASER_H
#define LASER_H

#include "../checkML.h"
#include "../Vector2D.h"
#include "../texture.h"
#include "SceneObject.h"
#include "GameObject.h"

class SDLApplication;
class PlayState;

class Laser : public SceneObject
{
	// atributos privados
private:
	// rojo 'r'  si viene de la nave
	// azul 'a' si viene de los aliens
	char laserType;

	Vector2D<double> vel;

	bool alive;

	int cooldown;

	// metodos publicos 
public:
	// ---- constructora ----
	Laser(char type, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game);

	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	void save(std::ostream& out) const override;

	// ---- hit ----
	// colisiones
	bool hit(SDL_Rect* rect, char frenemy) override;

	// devuelve si esta fuera del marco de juego 
	bool isOut() const;

	// devuelve si esta vivo el laser
	bool IsAlive() const { return alive; }

	char getColor() const { return laserType; };

protected:
	// mueve el laser segun el vector velocidad
	void move();

	// actualiza el rect
	void updateRect() override;
};

#endif