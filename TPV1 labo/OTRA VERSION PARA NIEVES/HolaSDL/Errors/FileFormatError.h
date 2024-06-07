#ifndef FILEFORMATERROR_H
#define FILEFORMATERROR_H

#include "InvadersError.h"
#include "../checkML.h"

class FileFormatError : public InvadersError
{
	// para los errores provocados en la lectura de los archivos de datos del juego (mapas y partidas guardadas)
	// la excepción debe almacenar y mostrar el nombre de archivo y el número de línea del error junto con el mensaje
public:
	FileFormatError(const std::string& message);
};
#endif