#ifndef SDLERROR_H
#define SDLERROR_H

#include "InvadersError.h"
#include "checkML.h"

class SDLError : public InvadersError
{
    // para todos los errores relacionados con la inicialización y uso de SDL
public:
    // para obtener un mensaje específico sobre el error de SDL, se almacenará en la excepción
    SDLError(const std::string& message);
};
#endif