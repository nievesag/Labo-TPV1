#include "FileNotFoundError.h"

FileNotFoundError::FileNotFoundError(const std::string& message) : InvadersError(message) 
{ 
	errorMessage = message; 
}