#ifndef INFOBAR_H
#define INFOBAR_H

#pragma once

// INCLUDES
#include "GameObject.h"
#include <SDL_ttf.h>


class Game;

class Infobar : public GameObject
{
private:

	// color del score y fuente del score 
	//TTF_Font* font = TTF_OpenFont(FONT_ROOT.c_str(), 24);
	SDL_Color color = { 255, 255, 255, 255 };

	// puntuacion
	int SCORE = 0;

	// padding (separacion con margenes ?)
	int padding;

	// posicion del score
	Point2D<double> position;


public:
	// constructora del infobar
	Infobar(const Point2D<>& position, Texture* texture, int padding, PlayState* playState);

	// render del infobar
	void render() const override;

	// update del infobar
	void update() override;

	// save del infobar
	void save(std::ostream& os) const override {}


};

#endif

