//
// Declaración de la clase Date
//

#include <iostream>

#pragma once
class Vector
{
	private:
		int tam; // tamaño del vector (N en el enunciado)
		int vector[]; // vector de enteros

	public:
		int* MoveVector(int vector[])
		{
			static int a[sizeof(vector)]; // crea un array statico 
			int saveNum;
			for (int i = 0; i<sizeof(a); i++)
			{
				a[(i + 1) % sizeof(a)] = vector[i];
			}
			return a;
		}

};

