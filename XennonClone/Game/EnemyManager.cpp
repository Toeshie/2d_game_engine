#include "EnemyManager.h"
#include "PhysicsComponent.h"
#include "GameWorld.h"
#include "Enemy.h"
#include "Loner.h"
#include "Rusher.h"
#include "Random"
#include "DronePack.h"
#include "TimerManager.h"
#include "MetalAsteroid.h"
#include "StoneAsteroid.h"

EnemyManager* EnemyManager::instance_ = nullptr;

void EnemyManager::start()
{
    if (instance_ != nullptr) {
        delete this;
        return;
    }
    instance_ = this;
    current_time_ = spawn_delay_;
}

void EnemyManager::update(float deltaTime)
{
    game_object::update(deltaTime);

    current_time_ -= deltaTime;
    if (current_time_ <= 0) {
        current_time_ = spawn_delay_;
        spawn_enemy_at_random();
    }
}

void EnemyManager::spawn_enemy_at_random()
{	
    if (enemy_count_ < max_enemies_) {
        Enemy* enemy = nullptr;
        Vector2D spawn_point;

        int get_number = (rand() % 100) / 25;
        switch (get_number)
        {
            case 0:
            {
                enemy = game_world::instantiate_object<Loner>();
                spawn_point = loner_spawn_spawn_locations_[rand() % 6];
                // Set move_direction based on spawn position
                if (spawn_point.x < 400) { 
                    static_cast<Loner*>(enemy)->move_direction = Vector2D::right();
                } else {
                    static_cast<Loner*>(enemy)->move_direction = Vector2D::left();
                }
                break;
            }
            case 1:
            {
                enemy = game_world::instantiate_object<Rusher>();
                spawn_point = rusher_spawn_locations_[rand() % 4];
                break;
            }
            case 2:
            {
                spawn_point = asteroid_spawn_locations_[rand() % 10];
                if (MathHelper::random_int_in_range(0, 99) >= 49) {
                    enemy = game_world::instantiate_object<StoneAsteroid>();
                } else {
                    enemy = game_world::instantiate_object<MetalAsteroid>();
                }
                break;
            }
            default:
            case 3:
            case 4:
            {
                // Drone Pack
                spawn_point = drone_spawn_locations[rand() % 4];
                if (game_world::find_all_objects_with_tag("Drone").size() < 6) {
                    game_object* drone_pack = game_world::instantiate_object<DronePack>();
                    if (drone_pack) {
                        drone_pack->get_transform()->set_position(spawn_point);
                    }
                }
                break;
            }
        }
        if (enemy) {
            enemy_count_++;
            enemy->get_component<PhysicsComponent>()->set_position(spawn_point);
            enemies_.push_back(enemy);
        }
    }
}

Enemy* EnemyManager::spawn_asteroid()
{
    Enemy* enemy = nullptr;
    Vector2D spawn_point = asteroid_spawn_locations_[rand() % 10];
    if (MathHelper::random_int_in_range(0, 99) >= 49) {
        enemy = game_world::instantiate_object<StoneAsteroid>();
    } else {
        enemy = game_world::instantiate_object<MetalAsteroid>();
    }
    if (enemy) {
        enemy_count_++;
        enemy->get_component<PhysicsComponent>()->set_position(spawn_point);
        enemies_.push_back(enemy);
    }
    return enemy;
}

void EnemyManager::delete_enemy(Enemy* enemy)
{
    if (!enemy)
        return;
    for (int i = 0; i < enemies_.size(); ++i)
    {
        if (enemies_[i] == enemy)
        {
            enemy_count_--;
            enemies_.erase(enemies_.begin() + i);
            return;
        }
    }
}

void EnemyManager::add_enemy(Enemy* enemy)
{
    enemies_.push_back(enemy);
}

void EnemyManager::clear_all_enemies()
{
    for (auto& enemy : enemies_) {
        game_world::destroy_object(enemy);
    }
    enemies_.clear();
    enemy_count_ = 0;
}