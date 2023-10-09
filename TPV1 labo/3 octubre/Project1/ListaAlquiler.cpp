//
// Implementaci�n de la clase ListaAlquiler
//

#include "ListaAlquiler.h"
#include "ListaCoches.h"
#include "Coche.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

bool ListaAlquiler::leerAlquileres() 
{
    // abre el archivo rent.txt
    fstream rent("rent.txt");

    if (rent.is_open()) {

        // saca el tama�o de la lista de coches
        rent >> tamListaAlquiler;

        // crea el array dinamico ListaCoches con elementos de tipo coalquiler y tama�o tamListaAlquileres
        ListAlquiler = new Alquiler[tamListaAlquiler];

        int a, b;

        // bucle para leer los datos
        for (int i = 0; i < tamListaAlquiler; i++)
        {
            // lee el codigo
            rent >> a;

            // b recibe el indice del coche, si no existe recibe -1
            b = ListCoches.buscarCoche(ListCoches, a, 10);

            // si no existe el puntero -> valor de puntero null
            if (b == -1) ListAlquiler[i].getCoche(i) = nullptr;

            // si existe el puntero indica al coche
            else ListAlquiler[i].getCoche(i) = ListCoches + b;

            char barra = ' ';

            // lee la fecha
            rent << ListAlquiler[i].getYear();
            // char para leer la barra de la fecha
            rent << barra;
            rent << ListAlquiler[i].getMes();
            rent << barra;
            rent << ListAlquiler[i].getDia();

            ListAlquiler[i].getDate() = ListAlquiler[i].getYear() + 100 * ListAlquiler[i].getMes() + 10000 * ListAlquiler[i].getDia();

            // lee la cantidad de dias
            rent << ListAlquiler[i].getCant();
        }

        // ----------DEBUG------------
        ///*
        for (int i = 0; i < tamListaAlquiler; i++) {
            cout << ListAlquiler[i].getDate();
            cout << " ";
            cout << ListAlquiler[i].getCant();
            cout << " ";
            if (!ListAlquiler[i].getCoche()) cout << "ERROR";
            else cout << ListAlquiler[i].getCoche()->getCodigo();
            cout << "\n";
        }
    }

    return rent.is_open(); // true -> archivo coches abierto / false -> error
}

void ListaAlquiler::ordenarAlquileres() 
{
    Alquiler* a = ListAlquiler + 8;
    sort(ListAlquiler, a);

    //--------DEBUG---------
    ///*
    for (int i = 0; i < 8; i++) {

        cout << ListAlquiler[i].getDate();
        cout << "\n";
    }
}

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
}

void ListaAlquiler::deleteMem() 
{
    // borra la memoria dinamica (se supone) (eu confio)
    delete[] ListAlquiler;
}