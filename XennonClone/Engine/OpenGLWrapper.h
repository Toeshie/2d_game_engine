#pragma once

struct SDL_Window;
typedef void* SDL_GLContext;

class OpenGLWrapper
{
public:
	OpenGLWrapper() = delete;
	OpenGLWrapper(const OpenGLWrapper&) = delete;
	OpenGLWrapper& operator=(const OpenGLWrapper&) = delete;

	static void init() noexcept;
	static SDL_GLContext initialize_glad(SDL_Window* window);
};

