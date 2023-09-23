// Ines Primo
// Nieves Alonso

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <windows.h>
#include "Date.h"

using namespace std;

// elemento tipo coche
struct coche {
    int codigo;
    int precio;
    string nombre;
};

// elemento tipo alquiler
struct alquiler {
    coche* coche;
    string fecha;
    int cant;
};

// declaracion del array dinamico ListaCoches
coche* ListaCoches;
// declaracion del array dinamico ListaAlquiler
alquiler* ListaAlquiler;


bool leerModelos()
{
    int tamListaCoches = 0;

    // abre el archivo coches.txt
    fstream coches("coches.txt");

    string c;

    if (coches.is_open()) {

        // saca el tamaño de la lista de coches
        coches >> tamListaCoches;

        // crea el array dinamico ListaCoches
        ListaCoches = new coche[tamListaCoches];

        // bucle para leer los datos
        for (int i = 0; i < tamListaCoches; i++)
        {
            // lee el codigo
            coches >> ListaCoches[i].codigo;
            // lee el precio
            coches >> ListaCoches[i].precio;
            // lee el nombre
            coches >> ListaCoches[i].nombre;
            coches >> c;
            ListaCoches[i].nombre += " " + c;
        }


        // --------PARA DEBUG------------
        /*
        for (int i = 0; i < tamListaCoches; i++) {
            cout << ListaCoches[i].codigo;
            cout << " ";
            cout << ListaCoches[i].nombre;
            cout << " ";
            cout << ListaCoches[i].precio;
            cout << "\n";
        }
        */
    }

    return coches.is_open();
}


int buscarCoche(coche* List, int codigo, int size) {

    int ini = 0, fini = size - 1;
    int med = -1;

    coche* ptr = List;
    bool enc = false;

    // bucle continua mientras no se haya encontrado y no se pase ini de fini
    while (!enc && ini <= fini) {

        // reiniia el medio en cada vuelta
        med = (ini + fini) / 2;

        // si el codigo dado es menor que el que hemos encontrado
        if (codigo < ptr[med].codigo) {
            // se mueve el indice del final hacia abajo la distancia de med - 1
            fini = med - 1;
        }
        else if (codigo > ptr[med].codigo) {
            // se mueve el indice del principio hacia arriba la distancia med +1
            ini = med + 1;
        }
        // si son iguales se ha encontrado
        else enc = true;
    }

    if (ini > fini) med = -1;

    return med;
}


bool leerAlquileres() {

    int tamListaAlquileres = 0;

    // abre el archivo rent.txt
    fstream rent("rent.txt");

    if (rent.is_open()) {

        // saca el tamaño de la lista de coches
        rent >> tamListaAlquileres;

        // crea el array dinamico ListaCoches
        ListaAlquiler = new alquiler[tamListaAlquileres];

        int a, b;

        // bucle para leer los datos
        for (int i = 0; i < tamListaAlquileres; i++)
        {
            // lee el codigo
            rent >> a;
            // b recibe el indice del coche, si no existe recibe -1
            b = buscarCoche(ListaCoches, a, 10);

            // si no existe el puntero es null
            if (b == -1) ListaAlquiler[i].coche = nullptr;
            // si existe el puntero indica al coche
            else ListaAlquiler[i].coche = ListaCoches + b;

            // lee la fecha
            rent >> ListaAlquiler[i].fecha;
            // lee la cantidad de dias
            rent >> ListaAlquiler[i].cant;

        }

        // --------PARA DEBUG------------
        /*
        for (int i = 0; i < tamListaAlquileres; i++) {
            cout << ListaAlquiler[i].fecha;
            cout << " ";
            cout << ListaAlquiler[i].cant;
            cout << " ";
            if (!ListaAlquiler[i].coche) cout << "ERROR";
            else cout << ListaAlquiler[i].coche->codigo;
            cout << "\n";
        }
        */


    }



    return rent.is_open();
}


void ordenarAlquileres() {

}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    leerModelos();

    leerAlquileres();









}