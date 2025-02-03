#pragma once
#include "GameObject.h"

class Sprite;

class BackgroundStatic : public game_object
{
protected:
	Sprite* sprite_component_ = nullptr;
public:
	virtual void start() override;
	BackgroundStatic();
	~BackgroundStatic();
};