#include <memory>
#include "GameEngine.h"
#include "SDL.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "PhysicsWorld.h"
#include "InputComponent.h"
#include "TimerManager.h"
#include "Input.h"
#include "ObjectInstanceTracker.h"
#include "MathHelper.h"
#include "TextureManager.h"
#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Renderer.h"
#include "OpenGLWrapper.h"
#include "RenderComponent.h"
#include "FontLoader.h"

float triangleArea(Vector2D A, Vector2D B, Vector2D C);
bool isInsideSquare(Vector2D A, Vector2D B, Vector2D C, Vector2D D, Vector2D P);

game_world* GameEngine::world_ = nullptr;
float GameEngine::elapsed_ms_ = 0.f;

std::vector<game_object*> GameEngine::game_object_list;
std::vector<render_component*> GameEngine::render_components_list;
std::vector<render_component*> GameEngine::ui_render_list;
std::vector<input_component*> GameEngine::pawn_list;

GameEngine* GameEngine::instance_{ nullptr };

GameEngine::~GameEngine()
{
	delete window_;
	delete sdl_;
	delete input_;
	delete physics_world_;
	TimerManager::shutdown();
}	

void GameEngine::init(const char* windowTitle, int windowWidth, int windowHeight, game_world* World)
{
	if (instance_) {
		delete this;
		return;
	}

	instance_ = this;
	
	sdl_ = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	if (sdl_ == nullptr) return;

	Renderer::screen_width = windowWidth;
	Renderer::screen_height = windowHeight;
	
	OpenGLWrapper::init();
	
	window_ = new Window(windowTitle, windowWidth, windowHeight, true);
	if (window_ == nullptr) return;
	
	world_ = World;
	input_ = new Input();
	
	physics_world_ = new physics_world();
	if (physics_world_) {
		physics_world_->init();
	}
	
	font_loader_ = new FontLoader();
	if (font_loader_) {
		font_loader_->init("font16x16.bmp");
	}
	
	TimerManager::initialize();
}

void GameEngine::start_and_run()
{
	bool isRunning = true;
	SDL_Event ev;
	const int lock = 1000 / max_fps_;
	Uint32 mTicksCount = SDL_GetTicks();


	SDL_GLContext context = OpenGLWrapper::initialize_glad(window_->get_window());

	std::string vertexPath = TextureManager::get_path_translated("../Engine/shaders/vertexShader.glsl");
	std::string fragmentPath = TextureManager::get_path_translated("../Engine/shaders/fragmentShader.glsl");
	
	unsigned int shaderProgram = Shader::create_program_from_shader_files(
		vertexPath.c_str(),
		fragmentPath.c_str()
	);

	if (shaderProgram == 0) {
		//Failed to create shader program
	}

	auto textureUniformLocation = glGetUniformLocation(shaderProgram, "Textures");
	int samplers[32];
	for (int i = 0; i < 32; i++)
	{
		samplers[i] = i;
	}
	glUniform1iv(textureUniformLocation, 32, samplers);

	Renderer::init();
	start();

	while (isRunning)
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + lock));
		elapsed_ms_ = (SDL_GetTicks() - mTicksCount) / 1000.0f;	

		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT)
		{
			isRunning = false;
		}
		else
		{
			handle_input(ev);
		}
		
		physics_world::get_instance()->execute_stashed_events();

		physics_world_->update_physics(elapsed_ms_);

		update();

		render(shaderProgram);

		destroy_pending();

		mTicksCount = SDL_GetTicks();
	}

	
	destroy_all();


	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window_->get_window());

	Renderer::stop();
	SDL_Quit();
}


void GameEngine::destroy_pending()
{
	if (pending_destroy_.size() > 0) {
		for (auto obj : pending_destroy_) {
			std::vector<std::shared_ptr<Component>> comps = obj->get_all_components();
			for (int i = 0; i < comps.size();++i) {
				if (comps[i]) {
					comps[i]->on_destroyed();
				}
				ObjectInstanceTracker::remove_component_count(comps[i].get());
			}
			obj->on_destroyed();
			remove_game_object(obj);
		}
		pending_destroy_.clear();
	}
}

void GameEngine::add_pending_destroy(game_object* obj)
{
	pending_destroy_.push_back(obj);
}

void GameEngine::destroy_all()
{
	for (auto obj : game_object_list) {
		if (!obj) continue;
		
		std::vector<std::shared_ptr<Component>> comps = obj->get_all_components();
		for (const auto& comp : comps) {
			if (comp) {
				ObjectInstanceTracker::remove_component_count(comp.get());
			}
		}
		remove_game_object(obj);
	}
	game_object_list.clear();
	render_components_list.clear();
	ui_render_list.clear();
	pawn_list.clear();
}

void GameEngine::start()
{
	world_->init(this);
	world_->start();
}

void GameEngine::handle_input(SDL_Event& ev)
{
	input_->receive_input_event(ev);

	for (int i = 0; i < pawn_list.size();++i)
	{
		if (pawn_list[i] != nullptr)
		{
			pawn_list[i]->handle_events();
		}
	}
}

void GameEngine::update()
{
	TimerManager::execute_handles();
	world_->update(elapsed_ms_);
	for (int i = 0; i < game_object_list.size();++i) 
	{
		if (game_object_list[i] != nullptr)
		{
			if (game_object_list[i]->get_is_enabled()) {
				game_object_list[i]->update(elapsed_ms_);
				const std::vector<std::shared_ptr<Component>> comps = game_object_list[i]->get_all_components();
				for (auto cpt : comps) {
					cpt->update(elapsed_ms_);
				}
			}
		}
	}
}

void GameEngine::render(unsigned int shaderProgramID)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	Renderer::begin_batch();

	// Render world objects
	for (auto mR : render_components_list)
	{
		if (!mR || !mR->get_is_active()) continue;
		
		update_component_visibility(mR);
		mR->render();
	}

	// Render UI objects
	for (auto UIR : ui_render_list) {
		if (!UIR || !UIR->get_is_active()) continue;
		
		update_component_visibility(UIR);
		UIR->render();
	}

	Renderer::end_batch();
	Renderer::flush();
	SDL_GL_SwapWindow(window_->get_window());
	window_->clean();
}

void GameEngine::update_component_visibility(render_component* component)
{
	if (!component || !component->get_owner_game_object()) return;

	Vector2D pos = component->get_owner_game_object()->get_transform()->get_position();
	Vector2D win = window_->get_window_size();
	bool isInside = isInsideSquare(Vector2D(-20, -20), Vector2D(win.x, -20), 
								  win, Vector2D(-20, win.y), pos);

	if (isInside) {
		if (!component->get_is_visible()) {
			component->set_is_visible(true);
			component->get_owner_game_object()->on_became_visible();
		}
	} else {
		if (component->get_is_visible()) {
			component->set_is_visible(false);
			component->get_owner_game_object()->on_became_hidden();
		}
	}
}

float triangleArea(Vector2D A,Vector2D B ,Vector2D C ){
	return (C.x * B.y - B.x * C.y) - (C.x * A.y - A.x * C.y) + (B.x * A.y - A.x * B.y);
}

 bool isInsideSquare(Vector2D A ,Vector2D B ,Vector2D C ,Vector2D D ,Vector2D P)
{
	if (triangleArea(A,B,P) > 0 || triangleArea(B,C,P) > 0 || triangleArea(C,D,P) > 0 || triangleArea(D,A,P) > 0) {
		return false;
	}
	return true;
}

bool IsInside(Vector2D windowConfines, Vector2D pos, float Leeway) {

	if (pos < windowConfines) {
		return true;
	}
	return false;
}

void GameEngine::add_game_object(game_object* gameObject)
{
	if (gameObject == nullptr) { return; }
	game_object_list.push_back(gameObject);
	ObjectInstanceTracker::add_object_count(gameObject);
}

void GameEngine::remove_game_object(game_object* gameObject)
{
	for (int i = 0; i < game_object_list.size(); ++i) 
	{
		if (game_object_list[i] == gameObject)
		{
			ObjectInstanceTracker::remove_object_count(gameObject);
			game_object_list.erase(game_object_list.begin()+i);
			
			return;
		}
	}
}

void GameEngine::add_render_component(render_component* renderComponent)
{
	if (renderComponent == nullptr) { return; }
	if (renderComponent->get_is_ui()) {
		ui_render_list.push_back(renderComponent);
	}
	else {
		render_components_list.push_back(renderComponent);
	}

	sort_render_components();
}

void GameEngine::remove_render_component(render_component* renderComponent)
{
	if (renderComponent!=nullptr) {
		if (renderComponent->get_is_ui()) {
			for (int i = 0; i < ui_render_list.size(); ++i)
			{
				if (ui_render_list[i] == renderComponent)
				{
					ui_render_list.erase(ui_render_list.begin() + i);
					return;
				}
			}
		}
		else {
			for (int i = 0; i < render_components_list.size(); ++i)
			{
				if (render_components_list[i] == renderComponent)
				{
					render_components_list.erase(render_components_list.begin() + i);
					return;
				}
			}
		}
		sort_render_components();
	}
}

void GameEngine::add_pawn(input_component* pawn)
{
	if (pawn == nullptr) { return; }
	pawn_list.push_back(pawn);
}

void GameEngine::remove_pawn(input_component* pawn)
{
	for (int i = 0; i < pawn_list.size(); ++i)
	{
		if (pawn_list[i] == pawn)
		{
			pawn_list.erase(pawn_list.begin() + i);
			return;
		}
	}
}

SDL_Renderer* GameEngine::get_renderer() 
{
	if (window_) {
		return window_->get_renderer();
	}
	return nullptr;
}

Vector2D GameEngine::get_window_size() 
{
	return window_->get_window_size();
}


void GameEngine::sort_render_components()
{
	for (unsigned int i = 0; i < render_components_list.size() - 1; ++i)
	{
		int lowestIndex = i;
		for (unsigned int j = i + 1; j < render_components_list.size(); ++j)
		{
			if (render_components_list[j]->get_render_priority() < 
				render_components_list[lowestIndex]->get_render_priority())
			{
				lowestIndex = j;
			}
		}

		if (i != lowestIndex)
		{
			std::swap(render_components_list[i], render_components_list[lowestIndex]);
		}
	}
}




