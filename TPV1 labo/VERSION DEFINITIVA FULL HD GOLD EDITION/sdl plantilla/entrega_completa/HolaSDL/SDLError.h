#ifndef SDLERROR_H
#define SDLERROR_H

#include "InvadersError.h"
#include "checkML.h"

class SDLError : public InvadersError
{
    // para todos los errores relacionados con la inicializaci�n y uso de SDL
public:
    // para obtener un mensaje espec�fico sobre el error de SDL, se almacenar� en la excepci�n
    SDLError(const std::string& message);
};
#endif