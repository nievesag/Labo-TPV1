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
#include "ListaAlquiler.h"

using namespace std;

// constructora con las variables declaradas en h
Alquiler::Alquiler(Coche* c, Date* date, int dia, int mes, int year, int cant)
    : coche(coche), date(date), dia(dia), mes(mes), year(year), cant(cant) { }

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

    int tamListaAlquileres;

    // abre el archivo rent.txt
    fstream rent("rent.txt");

    int a, b;

    if (rent.is_open()) {

        // lee el codigo
        rent >> a;

        // b recibe el indice del coche, si no existe recibe -1
        b = listCoches.buscarCoche(a, 10);

        // si no existe el puntero -> valor de puntero null
        if (b == -1) al.setCoche(nullptr);

        // si existe el puntero indica al coche
        else al.setCoche(listaCoches & +b);

        char barra = ' ';
        int aux;

        // lee la fecha
        rent << aux;
        al.setYear(aux);
        // char para leer la barra de la fecha
        rent << barra;
        rent << aux;
        al.setMes(aux);
        rent << barra;
        rent << aux;
        al.setDia(aux);

        al.setDate(al.getYear() + 100 * al.getMes() + 10000 * al.getDia());

        // lee la cantidad de dias
        rent << aux;

        al.setCant(aux);

        /*
        // saca el tamaño de la lista de coches
        rent >> tamListaAlquileres;


        // crea el array dinamico ListaCoches con elementos de tipo coalquiler y tamaño tamListaAlquileres
        ListaAlquiler listAlquiler = new ListaAlquiler[tamListaAlquileres];

        int a, b;

        // bucle para leer los datos
        for (int i = 0; i < tamListaAlquileres; i++)
        {
            // lee el codigo
            rent >> a;

            // b recibe el indice del coche, si no existe recibe -1
            b = listCoches.buscarCoche(ListaCoches, a, 10);

            // si no existe el puntero -> valor de puntero null
            if (b == -1) ListaAlquiler[i].coche = nullptr;
            // si existe el puntero indica al coche
            else ListaAlquiler[i].coche = ListaCoches + b;

            char barra = ' ';

            // lee la fecha
            rent >> ListaAlquiler[i].year;
            // char para leer la barra de la fecha
            rent >> barra;
            rent >> ListaAlquiler[i].mes;
            rent >> barra;
            rent >> ListaAlquiler[i].dia;

            ListaAlquiler[i].fecha = ListaAlquiler[i].year + 100 * ListaAlquiler[i].mes + 10000 * ListaAlquiler[i].dia;

            // lee la cantidad de dias
            rent >> ListaAlquiler[i].cant;
        }

        // ----------DEBUG------------
        ///*
        for (int i = 0; i < tamListaAlquileres; i++) {
            cout << ListaAlquiler[i].fecha;
            cout << " ";
            cout << ListaAlquiler[i].cant;
            cout << " ";
            if (!ListaAlquiler[i].coche) cout << "ERROR";
            else cout << ListaAlquiler[i].coche->codigo;
            cout << "\n";
        }

    }

    return rent.is_open(); // true -> archivo coches abierto / false -> error
        */

        return al; // true -> archivo coches abierto / false -> error
    }
        
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

// destructora
ListaAlquiler::~ListaAlquiler() {
    // borra la memoria dinamica (se supone) (eu confio)
    delete[] ListAlquiler;
    ListAlquiler = nullptr;
    tamListaAlquiler = 0;
}

// escribe
ostream& operator<<(ostream& out, const Alquiler& a) {
    out << a.coche->getCodigo()
        << " " << a.date
        << " " << a.cant;

    return out;
}