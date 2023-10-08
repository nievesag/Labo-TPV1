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

bool ListaAlquiler::leerAlquileres() 
{
    // abre el archivo rent.txt
    fstream rent("rent.txt");

    if (rent.is_open()) {

        // saca el tamaño de la lista de coches
        rent >> tamListaAlquiler;

        // crea el array dinamico ListaCoches con elementos de tipo coalquiler y tamaño tamListaAlquileres
        ListAlquiler = new Alquiler[tamListaAlquiler];

        int a, b;

        // Coche *p = ListCoches;

        // bucle para leer los datos
        for (int i = 0; i < tamListaAlquiler; i++)
        {
            // lee el codigo
            rent >> a;

            // b recibe el indice del coche, si no existe recibe -1
            b = ListCoches.buscarCoche(ListCoches, a, 10);

            // si no existe el puntero -> valor de puntero null
            if (b == -1) ListAlquiler[i].coche = nullptr;
            // si existe el puntero indica al coche
            else ListAlquiler[i].coche = ListCoches + b;

            char barra = ' ';

            // lee la fecha
            rent >> ListAlquiler[i].year;
            // char para leer la barra de la fecha
            rent >> barra;
            rent >> ListAlquiler[i].mes;
            rent >> barra;
            rent >> ListAlquiler[i].dia;

            ListAlquiler[i].fecha = ListAlquiler[i].year + 100 * ListAlquiler[i].mes + 10000 * ListAlquiler[i].dia;

            // lee la cantidad de dias
            rent >> ListAlquiler[i].cant;
        }

        // ----------DEBUG------------
        ///*
        for (int i = 0; i < tamListaAlquiler; i++) {
            cout << ListAlquiler[i].fecha;
            cout << " ";
            cout << ListAlquiler[i].cant;
            cout << " ";
            if (!ListAlquiler[i].coche) cout << "ERROR";
            else cout << ListAlquiler[i].coche->codigo;
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
        cout << ListAlquiler[i].year;
        cout << "/";
        cout << ListAlquiler[i].mes;
        cout << "/";
        cout << ListAlquiler[i].dia;

        cout << " ";
        if (ListAlquiler[i].coche == nullptr) {
            cout << "ERROR: Modelo inexistente";
        }
        else {
            cout << ListAlquiler[i].coche->nombre;
            cout << " ";
            cout << ListAlquiler[i].cant;
            cout << " dia(s) por ";

            if (ListAlquiler[i].coche == nullptr) {
                cout << ListAlquiler[i].coche->nombre;
            }
            cout << ListAlquiler[i].coche->precio * ListAlquiler[i].getCant();
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