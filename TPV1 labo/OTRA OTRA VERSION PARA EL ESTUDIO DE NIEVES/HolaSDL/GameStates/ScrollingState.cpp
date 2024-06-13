#include "ScrollingState.h"
#include "../checkML.h"

ScrollingState::ScrollingState(SDLApplication* game, Texture* texture, GameState* next) :
			GameState(game), next_(next), tex(texture)
{
	scrollImg = new ScrollImage(Point2D<double>(0, winHeight), winWidth, winHeight, tex, this);

	addObject(scrollImg);
}

void ScrollingState::render() const
{
	// renderiza la imagen
	scrollImg->render();
}

void ScrollingState::update()
{
	// actualiza la imagen
	scrollImg->update();

	// si ha llegado al final, pasas al siguiente estado
	if(scrollImg->getFinish())
	{
		NextState();
	}
}

bool ScrollingState::onEnter() const { return true; }

bool ScrollingState::onExit() const { return true; }

void ScrollingState::HandleEvent(const SDL_Event& event)
{
	GameState::HandleEvent(event);

	if(event.type == SDL_KEYDOWN)
	{
		NextState();
	}
}

void ScrollingState::NextState()
{
	// lo pasa al gsMachine que ya luego hace sus cosas
	application->getgsMachine()->pushState(next_);
}

std::string ScrollingState::getID() const
{
	return std::string();
}