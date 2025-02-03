#pragma once
#include <vector>
#include <memory>
#include "Transform.h"

// Forward declarations
class render_component;
class game_object;
class game_world;
class input_component;
class physics_world;
class SDLWrapper;
class Window;
class Input;
class FontLoader;
struct SDL_Renderer;
union SDL_Event;

class GameEngine
{
public:
	~GameEngine();
	
	// Initialization
	void init(const char* windowTitle, int windowWidth, int windowHeight, game_world* World);
	void start_and_run();

	// Engine Events
	void start();
	void handle_input(SDL_Event& ev);
	void update();
	void render(unsigned int shaderProgramID);

	// Object lifecycle management
	void destroy_pending();
	void add_pending_destroy(game_object* obj);
	void destroy_all();

	// Component visibility
	void update_component_visibility(render_component* component);

	// Static object manipulation methods
	static void add_game_object(game_object* gameObject);
	static void remove_game_object(game_object* gameObject);
	static void add_render_component(render_component* renderComponent);
	static void remove_render_component(render_component* renderComponent);
	static void add_pawn(input_component* pawn);
	static void remove_pawn(input_component* pawn);

	// Getters
	static std::vector<game_object*> get_all_game_objects() { return game_object_list; }
	static float get_delta_time() { return elapsed_ms_; }
	static GameEngine* get_instance() { return instance_; }
	SDL_Renderer* get_renderer();
	Window* get_window() { return window_; }
	Vector2D get_window_size();
	FontLoader* get_font_loader() { return font_loader_; }
	physics_world* get_physics_world() { return physics_world_; }

	// Rendering control
	static void sort_render_components();
	static bool is_using_open_gl_rendering;

private:
	// Singleton instance
	static GameEngine* instance_;

	// Core systems
	physics_world* physics_world_{nullptr};
	SDLWrapper* sdl_{nullptr};
	Window* window_{nullptr};
	Input* input_{nullptr};
	FontLoader* font_loader_{nullptr};

	// Game objects and components
	std::vector<game_object*> pending_destroy_;
	static std::vector<game_object*> game_object_list;
	static std::vector<render_component*> render_components_list;
	static std::vector<render_component*> ui_render_list;
	static std::vector<input_component*> pawn_list;

	// Game state
	static game_world* world_;
	static float elapsed_ms_;
	const int max_fps_{144};
};

