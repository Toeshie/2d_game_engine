#pragma once
#include "GameWorld.h"
#include "Transform.h"

class Player;
class PlayerUI;
class PlayerHealthUI;

class XennonGameWorld : public game_world
{
public:
	void add_score(unsigned int value);
	void clear_current();
	
	// Getters
	unsigned int get_best_score() const { return best_score_; }
	unsigned int get_current_score() const { return current_score_; }
	unsigned short get_current_player_life() const { return current_player_life_count_; }

protected:
	// Inherited via game_world
	void start() override;
	void update(float delta) override;

	void respawn_player();
	void on_player_die();
	void on_health_changed(int dmg);

private:
	void save_high_score();
	void load_high_score();
	std::string get_high_score_file_path() const;

	// Score tracking
	unsigned int current_score_ = 0;
	unsigned int best_score_ = 0;

	// Player respawn
	float player_respawn_time_ = 2.f;
	float current_wait_time_ = 0;

	// Player lives
	unsigned short max_player_life_count_ = 3;
	unsigned short current_player_life_count_ = 0;

	// Player positioning
	Vector2D player_start_pos_ = Vector2D(240, 700);

	// Game objects
	Player* player_ = nullptr;
	PlayerUI* ui_player_ = nullptr;
	PlayerHealthUI* player_health_ui_ = nullptr;

	bool bPlayerDead = false;
};

