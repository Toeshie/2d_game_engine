#include "BackgroundParallax.h"
#include "Sprite.h"
#include "ParallaxComponent.h"

BackgroundParallax::BackgroundParallax() : game_object() {
	
	//background_layer1_ = add_component<Sprite>("png/bg1.png", -1);
	//add_component<parallax_component>()->set_speed(100.0f);

	
	background_layer2_ = add_component<Sprite>("png/bg2.png", 0); 
	add_component<parallax_component>()->set_speed(90.0f); 
}

BackgroundParallax::~BackgroundParallax() {
	//delete background_layer1_;
	delete background_layer2_;
}
