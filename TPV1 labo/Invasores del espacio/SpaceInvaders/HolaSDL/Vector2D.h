//
// Declaraci�n de la clase Vector2D
//

#ifndef VECTOR2D_H
#define VECTOR2D_H

// !!! por las plantillas usar definiciones de funciones en el h -> el c�digo depende del argumento que le pases (c�digo no cerrado)
template <typename T> class Vector2D 
{
	// variables privadas
private: 
	T x, y;

	// metodos publicos
public:
	// METODOS
	// constructora
	// destructora
	// getter x
	// getter y

	// OPERADORES
	// suma / resta (+/-)
	// producto escalar (*)
	// producto vector-escalar (*)	
};

// establecer alias
template <typename T> using Point2D = Vector2D;
#endif

