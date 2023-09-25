// Ines Primo
// Nieves Alonso

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <windows.h>
#include <algorithm>
//#include "Date.h"

using namespace std;

// elemento tipo coche
struct coche {
    int codigo;
    int precio;
    string nombre;
};

// elemento tipo alquiler
struct alquiler {
    coche* coche; // puntero a coche
    int fecha;
    int dia;
    int mes;
    int year;
    int cant;
};

// declaracion del array dinamico ListaCoches
coche* ListaCoches;
int tamListaCoches = 0; // inicializacion a 0

// declaracion del array dinamico ListaAlquiler
alquiler* ListaAlquiler;
int tamListaAlquileres = 0; // inicializacion a 0

#pragma region metodos
bool leerModelos()
{
    // abre el archivo coches.txt
    fstream coches("coches.txt");

    string c;

    if (coches.is_open()) {

        // saca el tamaño de la lista de coches
        coches >> tamListaCoches;

        // crea el array dinamico ListaCoches con elementos de tipo coche y tamaño tamListaCoches
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
            ListaCoches[i].nombre += " " + c; // para las dos palabras del modelo del coche
        }

        // ----------DEBUG------------
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

    return coches.is_open(); // true -> archivo coches abierto / false -> error
}

bool leerAlquileres() {
    // abre el archivo rent.txt
    fstream rent("rent.txt");

    if (rent.is_open()) {

        // saca el tamaño de la lista de coches
        rent >> tamListaAlquileres;

        // crea el array dinamico ListaCoches con elementos de tipo coalquiler y tamaño tamListaAlquileres
        ListaAlquiler = new alquiler[tamListaAlquileres];

        int a, b;

        // bucle para leer los datos
        for (int i = 0; i < tamListaAlquileres; i++)
        {
            // lee el codigo
            rent >> a;
            // b recibe el indice del coche, si no existe recibe -1
            b = buscarCoche(ListaCoches, a, 10);

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

    return rent.is_open(); // true -> archivo coches abierto / false -> error
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

bool operator<(const alquiler& izdo, const alquiler& dcho) {
    // Definición del orden
    return izdo.fecha < dcho.fecha;
}

void ordenarAlquileres() {

    alquiler* a = ListaAlquiler + 8;
    sort(ListaAlquiler, a);

    //--------DEBUG---------
    /*
    for (int i = 0; i < 8; i++) {

        cout << ListaAlquiler[i].fecha;
        cout << "\n";
    }
    */
}

void mostrarAlquileres() {

    for (int i = 0; i < tamListaAlquileres; i++) {
        cout << ListaAlquiler[i].year;
        cout << "/";
        cout << ListaAlquiler[i].mes;
        cout << "/";
        cout << ListaAlquiler[i].dia;

        cout << " ";
        if (ListaAlquiler[i].coche == nullptr) {
            cout << "ERROR: Modelo inexistente";
        }
        else {
            cout << ListaAlquiler[i].coche->nombre;
            cout << " ";
            cout << ListaAlquiler[i].cant;
            cout << " dia(s) por ";

            if (ListaAlquiler[i].coche == nullptr) {
                cout << ListaAlquiler[i].coche->nombre;
            }
            cout << ListaAlquiler[i].coche->precio * ListaAlquiler[i].cant;
            cout << " euros";
        }
        cout << "\n";
    }
}
#pragma endregion

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    leerModelos();

    leerAlquileres();

    ordenarAlquileres();

    mostrarAlquileres();
}