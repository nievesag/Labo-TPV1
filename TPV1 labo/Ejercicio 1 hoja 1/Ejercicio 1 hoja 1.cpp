// 
//

#include <iostream>
#include<array>
using namespace std;

void MoveVector(int vector[], int tam)
{
	array<int, 5> a;
	for (int i = 0; i < tam; i++)
	{
		a[(i + 1) % sizeof(a)] = vector[i];
	}
}



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
		for (int i = 0; i < sizeof(a); i++)
		{
			a[(i + 1) % sizeof(a)] = vector[i];
		}
		return a;
	}

};

int main()
{
	std::cout << "Hello World!\n";

	const int tam = 5;
	int vector[5] = { 0, 1, 2, 3, 4 }; // vector de enteros
	MoveVector(vector, tam); // puntero para guardar la direccion

	for (int i = 0; i < sizeof(vector); i++) 
	{

	}

	return 0;
	
}

