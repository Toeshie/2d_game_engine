#include "SDL.h"
#include "InitError.h"

InitError::InitError() 
	: exception()
	, msg_(SDL_GetError()) 
{
}

InitError::InitError(const std::string& message) 
	: exception()
	, msg_(message) 
{
}

InitError::~InitError() noexcept 
{
}

const char* InitError::what() const noexcept 
{
	return msg_.c_str();
}