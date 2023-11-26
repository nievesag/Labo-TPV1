#include "Laser.h"

void Laser::render() const
{
}

bool Laser::update()
{
	return false;
}

void Laser::move()
{
	// mueve al laser
	position = position + vel;
}
