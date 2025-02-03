#include "CompanionPickup.h"
#include "IUpgradableShip.h"
#include "Sprite.h"
#include "AnimationComponent.h"

CompanionPickup::CompanionPickup()
{
	setup("png/PUClone.png",4 ,4,25);
}
void CompanionPickup::start()
{
	animation_component_->play_animation(0,0 ,1 ,3 , true);

}
void CompanionPickup::call_pickup(IUpgradableShip* other)
{
	other->add_companion();
}
