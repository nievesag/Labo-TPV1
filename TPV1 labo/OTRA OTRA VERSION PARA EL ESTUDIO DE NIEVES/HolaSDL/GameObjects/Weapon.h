#pragma once
#include "SceneObject.h"

class Weapon
{
protected:
	// atributos
	char c;

public:
	Weapon(char ch) : c(ch) {}

	// metodos para consultar sus caracteristicas
	char getChar()
	{
		return c;
	}

};