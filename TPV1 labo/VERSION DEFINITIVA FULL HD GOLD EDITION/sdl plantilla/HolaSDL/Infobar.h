#ifndef INFOBAR_H
#define INFOBAR_H

#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include "GameObject.h"
#include "texture.h"
#include "Font.h"

class Infobar : public GameObject
{
private:
	
	Texture* cannonTexture; // textura para las vidas
	Texture* scoreTexture;  // textura para la fuente de texto

	mutable Texture* numberTexture;

	Font* font;	// fuente

	// VARIABLES PARA MOSTRAR LAS VIDAS
	const int lifesStartX = 20;
	const int lifesStartY = 15;

	const int lifesSeparationX = 45;
	const int lifesSeparationY = 25;

	const int lifesPerRow = 5;

	int currentLifes;

	// VARIABLES PARA MOSTRAR LA PUNTUACION
	const int scoreStartX = 480;
	const int scoreStartY = 15;

	int currentScore = 0;

	void RenderLifes() const;
	void RenderScore() const;

public:
	//constructor
	Infobar(GameState* game, Font* font, Texture* cannontext, Texture* scoreText, int playerLifes)
		: GameObject(game), font(font), cannonTexture(cannontext), scoreTexture(scoreText), numberTexture(nullptr), currentLifes(playerLifes) {};

	//destructor
	~Infobar() {
		delete numberTexture;
	}

	void render() const override;

	void update() override {};

	void save(std::ostream& out)const override {};

	//cambiar esto por acceso a las variables?
	void updateCurrentLifes(int lifes);
	void updateCurrentScore(int score);
};

#endif