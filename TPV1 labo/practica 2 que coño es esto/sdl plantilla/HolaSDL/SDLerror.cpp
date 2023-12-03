#include "SDLError.h"

SDLError::SDLError(const std::string& message) : InvadersError(message) 
{ 
	errorMessage = message; 
}