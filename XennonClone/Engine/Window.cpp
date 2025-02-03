#include <SDL.h>
#include "Window.h"
#include "InitError.h"

Window::Window(const char* title, int window_width, int window_height, bool use_vsync)
	: stored_window_size_(window_width, window_height)
{
	window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		window_width, window_height, SDL_WINDOW_OPENGL);
	if (window_ == nullptr)
	{
		throw InitError();
	}

	renderer_ = SDL_CreateRenderer(window_, -1, use_vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
	if (!renderer_) {
		SDL_DestroyWindow(window_);
		throw InitError();
	}

	SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
}

Window::~Window()
{
	if (renderer_) {
		SDL_DestroyRenderer(renderer_);
	}
	if (window_) {
		SDL_DestroyWindow(window_);
	}
}

SDL_Surface* Window::get_surface() const
{
	return window_ ? SDL_GetWindowSurface(window_) : nullptr;
}

void Window::update_render()
{
	if (renderer_) {
		SDL_RenderPresent(renderer_);
	}
}

void Window::clean()
{
	if (renderer_) {
		SDL_RenderClear(renderer_);
	}
}
