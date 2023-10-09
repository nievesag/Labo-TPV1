//
// Implementación de la clase Alquiler -> funciona como el struct alquiler
//
#include <iostream>
#include "Alquiler.h"
#include "ListaCoches.h"
#include <fstream>
#include <windows.h>

// si lo tiene el h lo necesita el cpp??
#include "Date.h"
#include "Coche.h"
//#include "ListaAlquiler.h"

using namespace std;

// constructora con las variables declaradas en h
Alquiler::Alquiler(Coche* c, Date* date, int date2, int dia, int mes, int year, int cant)
    : coche(coche), date(date), date2(date2), dia(dia), mes(mes), year(year), cant(cant) { }

// constructora del tipo coche 
Alquiler::Alquiler(const Alquiler& alquiler)
    : coche(alquiler.coche), date(alquiler.date), dia(alquiler.dia), mes(alquiler.mes), year(alquiler.year), cant(alquiler.cant) { }

bool Alquiler::operator<(const Alquiler& izq) const
{
    // Definición del orden
    return false;
}

// falta el const (lo he quitado porque no iba)
Alquiler Alquiler::leeAlquiler(ListaCoches& listCoches)
{
    Alquiler al;

    // abre el archivo rent.txt
    fstream rent("rent.txt");

    int a = 0, b = 0;

    if (rent.is_open()) {

        int extra = 0;
        rent >> extra;

        // lee el codigo
        rent >> a;

        // b recibe el indice del coche, si no existe recibe -1
        b = listCoches.buscarCoche(a, 10);

        // si no existe el puntero -> valor de puntero null
        if (b == -1) al.setCoche(nullptr);

        // si existe el puntero indica al coche
        else {
            Coche* caux = nullptr;
            caux = listCoches.getListCoches();
            caux += b;
            al.setCoche(caux);
        }

        char barra = ' ';
        int aux = 0;

        // lee la fecha
        rent >> aux;
        al.setYear(aux);
        // char para leer la barra de la fecha
        rent >> barra;
        rent >> aux;
        al.setMes(aux);
        rent >> barra;
        rent >> aux;
        al.setDia(aux);

        al.setDate(al.getYear() + 100 * al.getMes() + 10000 * al.getDia());

        // lee la cantidad de dias
        rent >> aux;

        al.setCant(aux);
    }

    return al;
}

// escribe
ostream& operator<<(ostream& out, const Alquiler& a) {
    out << a.coche->getCodigo()
        << " " << a.date
        << " " << a.cant;

    return out;
}

/*
// lee
istream& operator>>(istream& in, Alquiler& a) {
    char space;
    int codigo, b;
    ListaCoches listCoches;

    in >> a;
    b = listCoches.buscarCoche(codigo, 8);

    return in;
}
*/