#pragma once
#include "GameObject.h"

class Sprite;

class BackgroundParallax : public game_object
{
private:
	Sprite* background_layer1_ = nullptr;
	Sprite* background_layer2_ = nullptr;
public:
	BackgroundParallax();
	~BackgroundParallax();
};

