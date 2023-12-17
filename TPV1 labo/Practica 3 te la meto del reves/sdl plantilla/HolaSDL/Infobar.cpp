#include "Infobar.h"

Infobar::Infobar(const Point2D<>& position, Texture* texture, int padding, PlayState* playState) 
	: position(position), padding(padding), GameObject(playState)
{


}

void Infobar::render() const
{
	// render del coso

}

void Infobar::update()
{
	// update del score
}

void Infobar::save(std::ostream& os) const 
{
	// save del coso (esto esta en el playstate actualmente es muy facil de implementar)

}
