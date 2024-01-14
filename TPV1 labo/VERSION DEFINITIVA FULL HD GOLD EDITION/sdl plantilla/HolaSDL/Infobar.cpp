#include "checkML.h"

#include "Infobar.h"
#include "SDLApplication.h"
#include "PlayState.h"

Infobar::Infobar(const Point2D<double>& position, Texture* cannonTexture, int spacing, GameState* gameState, SDL_Renderer* renderer)
	: GameObject(gameState), position(position), cannonTexture(cannonTexture), spacing(spacing), renderer(renderer) {}

Infobar::~Infobar()
{
	delete font;
}

void Infobar::renderLifes() const
{
	SDL_Rect lifesRect{
		position.getX() + spacing,
		position.getY() - spacing,
		cannonTexture->getFrameWidth(),
		cannonTexture->getFrameHeight()
	};

	for (int i = 1; i < currentLifes + 1; i++)
	{
		cannonTexture->renderFrame(lifesRect, cannonTexture->getNumRows() - 1, cannonTexture->getNumColumns() - 1);
		lifesRect.x = cannonTexture->getFrameWidth() * i + spacing * (i + 1);
	}
}

void Infobar::renderScore() const
{
	//SDL_Surface* textSurface = font->generateSurface(std::to_string(currentScore).c_str(), color);
	const Texture* scoreTexture = font->generateTexture(renderer, std::to_string(currentScore).c_str(), color);

	const SDL_Rect scoreRect{
		winWidth - scoreTexture->getFrameWidth() - spacing,
		winHeight - scoreTexture->getFrameHeight() - spacing,
		scoreTexture->getFrameWidth(),
		scoreTexture->getFrameHeight()
	};

	scoreTexture->render(scoreRect);
	delete scoreTexture;
}

void Infobar::render() const
{
	renderLifes();
	renderScore();
}