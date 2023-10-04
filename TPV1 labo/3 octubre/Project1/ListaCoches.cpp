//
// Implementación de la clase ListaCoches
//

#include <array>
#include "ListaCoches.h"
#include <fstream>
// #include "Coche.h" // ??????? si lista coches.h incluche coche.h esto tiene que incluirlo????????

using namespace std;

bool ListaCoches::leerModelos()
{
    // abre el archivo coches.txt
    fstream coches("coches.txt");

    string c;

    // saca el tamaño de la lista de coches
    coches >> tamListaCoches;

    // crea el array dinamico ListaCoches con elementos de tipo coche y tamaño tamListaCoches
    ListCoche = new Coche[tamListaCoches];

    // bucle para leer los datos
    for (int i = 0; i < tamListaCoches; i++)
    {
        // lee el codigo
        coches >> ListCoche[i].codigo;
        // lee el precio
        coches >> ListCoche[i].precio;
        // lee el nombre
        coches >> ListCoche[i].nombre;
        coches >> c;
        ListCoche[i].nombre += " " + c; // para las dos palabras del modelo del coche
    }
    return coches.is_open(); // true -> archivo coches abierto / false -> error
}

int ListaCoches::buscarCoche() 
{
    int size;
    int ini = 0, fini = size - 1;
    int med = -1;

    Coche *p = ListCoche;
    bool enc = false;

    // bucle continua mientras no se haya encontrado y no se pase ini de fini
    while (!enc && ini <= fini) {

        // reiniia el medio en cada vuelta
        med = (ini + fini) / 2;

        // si el codigo dado es menor que el que hemos encontrado
        if (coche.codigo < p[med].codigo) {
            // se mueve el indice del final hacia abajo la distancia de med - 1
            fini = med - 1;
        }
        else if (coche.codigo > p[med].codigo) {
            // se mueve el indice del principio hacia arriba la distancia med +1
            ini = med + 1;
        }
        // si son iguales se ha encontrado
        else enc = true;
    }

    if (ini > fini) med = -1;

    return med;
}
