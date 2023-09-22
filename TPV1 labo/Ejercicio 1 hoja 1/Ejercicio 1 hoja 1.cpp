// Inés Primo López
// Nieves Alonso Gilsanz

#include <iostream>
#include<array> // incluye la nomenclatura moderna para los arrays 
using namespace std;

// método que reordena el vector
void MoveVector(array<int, 5> vector, int tam) // se le pasa el array<tipo, tamaño> -> vector resultado / entero tam para el for
{
	array<int, 5> a; // declaración del array a de tamaño 5 elementos -> vector inicial
	for (int i = 0; i < tam; i++) // recorre el array hasta tam (se pasa su valor en main)
	{
		a[(i + 1) % a.size()] = vector[i]; // áplicación de la fórmula del array circular para reordenar a en vector
										   // la posición 0 en "a" va a ser la 1 en en "vector" etc...
	}

	for (int i = 0; i < vector.size(); i++) // recorre vector entero
	{
		cout << a[i]; // escribe a reorganizado
	}
}

// clase vector xd
/* 
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

}; */

int main() 
{
	const int tam = 5; // establece el tamaño del array a reordenar
	array<int, 5> vector = { 0, 1, 2, 3, 4 }; // inicializa el vector

	for (int i = 0; i < vector.size(); i++) // recorre vector
	{
		cout << vector[i]; // va escribiendo el vector antes de ser reorganizado 
						   // (lo que hemos inicializado antes)
	}

	cout << "\n"; // salto de línea
	
	std::cout << "Hello World!\n"; // gonorrea

	MoveVector(vector, tam); // ejecuta el método

	return 666;
}