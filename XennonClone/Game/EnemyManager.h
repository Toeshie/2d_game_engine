#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"

class Enemy; // Forward declaration

class EnemyManager : public game_object
{
protected:
    Vector2D rusher_spawn_locations_[4] = { Vector2D(50, -10), Vector2D(300, -10.f), Vector2D(150, -10.f), Vector2D(200, -10.f) };

    Vector2D loner_spawn_spawn_locations_[6] = {
        // right side
        Vector2D(600, 300), Vector2D(600, 50), Vector2D(600, 200),
        // left side
        Vector2D(-100, 300), Vector2D(-100, 50), Vector2D(-100, 200)
    };

    Vector2D asteroid_spawn_locations_[10] = {
        Vector2D(50, -10), Vector2D(100, -10), Vector2D(150, -10), Vector2D(200, -10),
        Vector2D(250, -10), Vector2D(300, -10), Vector2D(350, -10), Vector2D(400, -10),
        Vector2D(450, -10), Vector2D(500, -10)
    };

    Vector2D drone_spawn_locations[4] = { Vector2D(50, -10), Vector2D(300, -10.f), Vector2D(150, -10.f), Vector2D(200, -10.f) };

    float current_time_;
    float spawn_delay_ = 5;
    int max_enemies_ = 25;
    std::vector<class Enemy*> enemies_;
    static EnemyManager* instance_;
    int enemy_count_ = 0;

public:
    static EnemyManager* get_instance() { return instance_; }

    virtual void start() override;
    virtual void update(float deltaTime) override;

    Enemy* spawn_asteroid();
    void spawn_enemy_at_random();

    void delete_enemy(class Enemy* enemy);
    void add_enemy(Enemy* enemy);

    void clear_all_enemies();
};