#include "XennonGameWorld.h"
#include "GameObject.h"
#include "BackgroundStatic.h"
#include "Player.h"
#include "DronePack.h"
#include "PhysicsComponent.h"
#include "EnemyManager.h"
#include "BackgroundParallax.h"
#include "MetalAsteroid.h"
#include "HealthComponent.h"
#include "TimerManager.h"
#include "MathHelper.h"
#include "PowerUpManager.h"
#include "PlayerHealthUI.h"
#include "PlayerUI.h"
#include <fstream>
#include <SDL.h>
#include "AudioManager.h"

void XennonGameWorld::start()
{
	AudioManager::initialize();
	
	load_high_score();

	// Load all game sounds
	AudioManager::get_instance()->load_sound("../Assets/music/explosion.wav", "explosion_sound");
	AudioManager::get_instance()->load_sound("../Assets/music/shoot.wav", "player_shoot");
	AudioManager::get_instance()->load_sound("../Assets/music/PowerUp.wav", "powerup_collect");
	
	// Load and play background music
	if (AudioManager::get_instance()->load_music("../Assets/music/LITD.wav", "LITD")) {
		
		AudioManager::get_instance()->play_music("LITD", -1);
		
	} else {
		
	}
	AudioManager::get_instance()->set_master_volume(1.0f);  // Full volume
	AudioManager::get_instance()->set_music_volume(1.0f);   // Full music volume

	// initialize game objects
	instantiate_object<EnemyManager>();
	instantiate_object<PowerUpManager>();
	instantiate_object<BackgroundStatic>();
	instantiate_object<BackgroundParallax>();

	// initialize UI and player
	player_health_ui_ = instantiate_object<PlayerHealthUI>();
	player_ = instantiate_object<Player>();
	ui_player_ = instantiate_object<PlayerUI>();
	ui_player_->set_high_score(best_score_);
	
	// Setup player
	player_->get_component<PhysicsComponent>()->set_position(player_start_pos_);
	HealthComponent* playerHealth = player_->get_component<HealthComponent>();
	playerHealth->on_die.Add(this, &XennonGameWorld::on_player_die);
	playerHealth->on_damage_taken.Add(this, &XennonGameWorld::on_health_changed);
	playerHealth->on_heal.Add(this, &XennonGameWorld::on_health_changed);

	// initialize player life count
	current_player_life_count_ = max_player_life_count_;
}

void XennonGameWorld::update(float delta)
{
	if (bPlayerDead) {
		current_wait_time_ += delta;
		if (current_wait_time_>= player_respawn_time_) {
			respawn_player();
			current_wait_time_ = 0;
		}
	}
}

void XennonGameWorld::respawn_player()
{
	player_->get_component<HealthComponent>()->respawn();
	player_->get_component<PhysicsComponent>()->set_position(player_start_pos_);
	bPlayerDead = false;
	player_health_ui_->set_player_health(1, 1);
}

void XennonGameWorld::on_player_die()
{
	//Remove Lives
	current_player_life_count_ = MathHelper::clamp_int(current_player_life_count_- 1,0,max_player_life_count_);
	player_health_ui_->set_player_life_count(current_player_life_count_);
	bPlayerDead = true;
	if (!current_player_life_count_>0) {
		clear_current();
	}
}

void XennonGameWorld::on_health_changed(int dmg)
{
	HealthComponent* h = player_->get_component<HealthComponent>();

	player_health_ui_->set_player_health(h->get_current_health(), h->get_max_health());
}

void XennonGameWorld::add_score(unsigned int value)
{
	current_score_ += value;
	ui_player_->set_current_score(current_score_);
	if (current_score_>best_score_) {
		best_score_ = current_score_;
		ui_player_->set_high_score(best_score_);
		save_high_score();
	}
}

void XennonGameWorld::clear_current()
{
	current_score_ = 0;
	ui_player_->set_current_score(0);
	current_player_life_count_ = max_player_life_count_;
	player_health_ui_->set_player_life_count(max_player_life_count_);
}

std::string XennonGameWorld::get_high_score_file_path() const {
	char* basePath = SDL_GetPrefPath("XennonClone", "XennonGame");
	std::string path = std::string(basePath) + "highscore.dat";
	SDL_free(basePath);
	return path;
}

void XennonGameWorld::load_high_score() {
	std::string path = get_high_score_file_path();
	SDL_Log("Loading high score from: %s", path.c_str()); // add this
	std::ifstream file(path, std::ios::binary);
	if (file.good()) {
		file.read(reinterpret_cast<char*>(&best_score_), sizeof(best_score_));
	}
	file.close();
}

void XennonGameWorld::save_high_score() {
	std::ofstream file(get_high_score_file_path(), std::ios::binary);
	if (file.good()) {
		file.write(reinterpret_cast<const char*>(&best_score_), sizeof(best_score_));
	}
	file.close();
}

