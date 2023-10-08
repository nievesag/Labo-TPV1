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
Alquiler::Alquiler(Coche* coche, Date* date, int dia, int mes, int year, int cant)
	: coche(coche), date(date), dia(dia), mes(mes), year(year), cant(cant) { }

// constructora del tipo coche 
Alquiler::Alquiler(const Alquiler& alquiler)
	: coche(alquiler.coche), date(alquiler.date), dia(alquiler.dia), mes(alquiler.mes), year(alquiler.year), cant(alquiler.cant) { }

// lee
istream& operator>>(istream& in, Alquiler& a) {
	char space;

	in >> coche.getCodigo() >> space >> a.dia >> a.mes >> a.year >> space >> a.cant;

	return in;
}

// escribe
ostream& operator<<(ostream& out, const Alquiler& a) {
	out << a.coche->getCodigo()
		<< " " << a.date
		<< " " << a.cant;

	return out;
}