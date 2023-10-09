//
// Implementación de la clase ListaAlquiler
//

#include "ListaAlquiler.h"
#include "ListaCoches.h"
#include "Coche.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

bool ListaAlquiler::leerAlquileres(ListaCoches listCoches)
{
    // abre el archivo rent.txt
    fstream rent("rent.txt");

    if (rent.is_open()) {

        // saca el tamaño de la lista de coches
        rent >> tamListaAlquiler;

        Alquiler al;

        // crea el array dinamico ListAlquiler con elementos de tipo coalquiler y tamaño tamListaAlquileres
        ListAlquiler = new Alquiler[tamListaAlquiler];

        int a = 0, b = 0;

        // bucle para leer los datos
        for (int i = 0; i < tamListaAlquiler; i++)
        {
            al = al.leeAlquiler(listCoches);

            // añade el alquiler
            ListAlquiler[i] = al.leeAlquiler(listCoches);
        }
    }

    return rent.is_open(); // true -> archivo coches abierto / false -> error
}

void ListaAlquiler::ordenarAlquileres()
{
    Alquiler* a = ListAlquiler + 8;
    sort(ListAlquiler, a);
}

/*
void ListaAlquiler::mostrarAlquileres()
{
    for (int i = 0; i < tamListaAlquiler; i++) {
        cout << ListAlquiler[i].getYear();
        cout << "/";
        cout << ListAlquiler[i].getMes();
        cout << "/";
        cout << ListAlquiler[i].getDia();

        cout << " ";
        if (ListAlquiler[i].getCoche(i) == nullptr) {
            cout << "ERROR: Modelo inexistente";
        }
        else {
            cout << ListAlquiler[i].getCoche(i)->getNombre();
            cout << " ";
            cout << ListAlquiler[i].getCant();
            cout << " dia(s) por ";

            if (ListAlquiler[i].getCoche(i) == nullptr) {
                cout << ListAlquiler[i].getCoche(i)->getNombre();
            }
            cout << ListAlquiler[i].getCoche(i)->getPrecio() * ListAlquiler[i].getCant();
            cout << " euros";
        }
        cout << "\n";
    }
}*/


// equivalente a mostrar alquileres
ostream& operator<<(ostream& out, const ListaAlquiler& list)
{
    for (int i = 0; i < list.tamListaAlquiler; i++) {
        out << list.ListAlquiler[i].getYear();
        out << "/";
        out << list.ListAlquiler[i].getMes();
        out << "/";
        out << list.ListAlquiler[i].getDia();

        out << " ";
        if (list.ListAlquiler[i].getCoche(i) == nullptr) {
            out << "ERROR: Modelo inexistente";
        }
        else {
            out << list.ListAlquiler[i].getCoche(i)->getNombre();
            out << " ";
            out << list.ListAlquiler[i].getCant();
            out << " dia(s) por ";

            if (list.ListAlquiler[i].getCoche(i) == nullptr) {
                out << list.ListAlquiler[i].getCoche(i)->getNombre();
            }
            out << list.ListAlquiler[i].getCoche(i)->getPrecio() * list.ListAlquiler[i].getCant();
            out << " euros";
        }
        out << "\n";
    }
    return out;
}

ListaAlquiler::~ListaAlquiler() {
    // borra la memoria dinamica
    delete[] ListAlquiler;
    ListAlquiler = nullptr;
    tamListaAlquiler = 0;
}



