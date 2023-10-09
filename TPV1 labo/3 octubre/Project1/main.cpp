// Ines Primo
// Nieves Alonso

// AMPLIACIÓN CON CLASES

#include <iostream>

#include <string>
#include <array>
#include <algorithm>

#include <windows.h>
#include <fstream>


// inclusion de las clases
#include "Date.h"
#include "ListaCoches.h"
#include "ListaAlquiler.h"

using namespace std;

#pragma region metodos
// LEER ALQUILER
/*
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
}
*/

// si quitamos el & peta btw
void Prep(ListaCoches& listCoch, ListaAlquiler& listAlq) {

    listCoch.leerModelos();

    listAlq.leerAlquileres(listCoch);
}

void TryOuts(ListaCoches& list) {

    //1548 30 Volkswagen Golf

    int i = list.buscarCoche(1548, list.getTam());
    cout << i;
}

void BorraMem(ListaCoches& lista) {

    //lista.deleteMem();
}
#pragma endregion

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    
    ListaCoches listCoch;
    ListaAlquiler listAlq;

    listCoch.leerModelos();

    listAlq.leerAlquileres(listCoch);

    listAlq.ordenarAlquileres();

    cout << listAlq;

    listCoch.~ListaCoches();

    listAlq.~ListaAlquiler();

    //BorraMem(list);

    //leerModelos();

    //leerAlquileres();

    //ordenarAlquileres();

    //mostrarAlquileres();
}