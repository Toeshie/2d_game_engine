#pragma once
#include "InitError.h"
#include <SDL_stdinc.h>

class SDLWrapper
{
public:
	explicit SDLWrapper(Uint32 flags = 0);

	virtual ~SDLWrapper();

	SDLWrapper(const SDLWrapper&) = delete;
	SDLWrapper& operator=(const SDLWrapper&) = delete;
};

