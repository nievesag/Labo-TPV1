// 
//

#include <iostream>
#include<array>
using namespace std;

void MoveVector(array<int, 5> vector, int tam)
{
	array<int, 5> a;
	for (int i = 0; i < tam; i++)
	{
		a[(i + 1) % a.size()] = vector[i];
	}

	for (int i = 0; i < vector.size(); i++)
	{
		cout << a[i];
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
	

	const int tam = 5;
	array<int, 5> vector = { 0, 1, 2, 3, 4 }; // vector uwuwuwuwu

	for (int i = 0; i < vector.size(); i++)
	{
		cout << vector[i];
	}


	std::cout << "Hello World!\n"; // gonorrea


	MoveVector(vector, tam); // puntero para guardar la direccion

	return 666;
}

