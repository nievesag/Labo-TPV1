//
// Implementación de la clase Alquiler -> funciona como el struct alquiler
//
#include <iostream>
#include "Alquiler.h"
#include <fstream>

// si lo tiene el h lo necesita el cpp??
#include "Date.h"
#include "Coche.h"

using namespace std;

// constructora con las variables declaradas en h
Alquiler::Alquiler(Coche* coche, Date* date, int cant)
	: coche(coche), date(date), cant(cant) { }

// constructora del tipo coche 
Alquiler::Alquiler(const Alquiler& alquiler)
	: coche(alquiler.coche), date(alquiler.date), cant(alquiler.cant) { }

// lee
istream& operator>>(istream& in, Alquiler& a) {
	char space;
	string ap;

	in >> a.coche->getCodigo() >> space >> a.date >> space >> a.cant;

	return in;
}

// escribe
ostream& operator<<(ostream& out, const Alquiler& a) {
	out << a.coche->getCodigo()
		<< " " << a.date
		<< " " << a.cant;

	return out;
}