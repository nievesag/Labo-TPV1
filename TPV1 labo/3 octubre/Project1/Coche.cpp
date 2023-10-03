//
// Implementación de la clase Coche
//
#include <iostream>
#include <string>
#include <iomanip>
#include "Coche.h"

using namespace std;

// constructora con las variables declaradas en h
Coche::Coche(int p, int c, string n) 
	: precio(p), codigo(c), nombre(n) { }

// constructora del tipo coche 
Coche::Coche(const Coche& coche)
	: precio(coche.precio), codigo(coche.codigo), nombre(coche.nombre) { }

// lee
istream& operator>>(istream& in, Coche& c) {
	char space;
	string ap;

	in >> c.codigo >> space >> c.precio >> space >> c.nombre >> space >> ap;
	c.nombre += " " + ap;

	return in;
}

// escribe
ostream& operator<<(ostream& out, const Coche& c) {
	out << c.codigo
		<< " " << c.precio
		<< " " << c.nombre;

	return out;
}

