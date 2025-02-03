#pragma once
#include "Transform.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Window
{
public:
	Window(const char* title, int window_width, int window_height, bool use_vsync);
	~Window();

	void update_render();
	void clean();

	// Getters
	SDL_Surface* get_surface() const;
	SDL_Renderer* get_renderer() const noexcept { return renderer_; }
	SDL_Window* get_window() const noexcept { return window_; }
	Vector2D get_window_size() const noexcept { return stored_window_size_; }

private:
	Vector2D stored_window_size_;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
};

