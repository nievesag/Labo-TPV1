//
// Implementación de la clase Coche -> funciona como el struct coche
//
#include <iostream>
#include <string>
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

// declaraciones de metodos
	// Setter
void setCodigo(int c, Coche& coche) {
	coche.codigo = c;
}

	// Getter
int getCodigo() {
	return codigo;
}

	// Setter
void setPrecio(int p) {
	precio = p;
}

	// Getter
int getPrecio() {
	return precio;
}

	// Setter
void setNombre(string n) {
	nombre = n;
}

	// Getter
string getNombre() {
	return nombre;
}