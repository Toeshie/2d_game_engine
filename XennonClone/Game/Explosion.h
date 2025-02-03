#pragma once
#include "GameObject.h"

class Explosion : public game_object
{
public:
	Explosion();
	explicit Explosion(Transform* transform);

	void on_animation_end();

private:
	void initialize(); 

	class Sprite* sprite_component_ = nullptr;
	class animation_component* animation_component_ = nullptr;
	class AudioComponent* audio_component_ = nullptr;
};

