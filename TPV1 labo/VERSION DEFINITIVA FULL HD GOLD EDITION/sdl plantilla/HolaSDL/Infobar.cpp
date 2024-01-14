#include "checkML.h"

#include "Infobar.h"
#include "SDLApplication.h"
#include "PlayState.h"

Infobar::Infobar(const Point2D<double>& position, Texture* cannonTexture, int spacing, GameState* gameState, SDL_Renderer* renderer)
	: GameObject(gameState), position(position), cannonTexture(cannonTexture), spacing(spacing), renderer(renderer) {}

void Infobar::renderLifes() const
{
	SDL_Rect livesRect{
		position.getX() + spacing,
		position.getY() - spacing,
		cannonTexture->getFrameWidth(),
		cannonTexture->getFrameHeight()
	};
	for (int i = 1; i < currentLifes + 1; i++)
	{
		cannonTexture->renderFrame(livesRect, cannonTexture->getNumRows() - 1, cannonTexture->getNumColumns() - 1);
		livesRect.x = cannonTexture->getFrameWidth() * i + spacing * (i + 1);
	}
}

void Infobar::renderScore() const
{
	SDL_Surface* textSurface = font->generateSurface(std::to_string(currentScore).c_str(), color);
	Texture* scoreTexture = font->generateTexture(renderer, std::to_string(currentScore).c_str(), color);

	const SDL_Rect scoreRect{
		winWidth - textSurface->w - spacing,
		winHeight - textSurface->h - spacing,
		textSurface->w,
		textSurface->h
	};
	SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(scoreTexture);
}

void Infobar::render() const
{
	renderLifes();
	renderScore();
}