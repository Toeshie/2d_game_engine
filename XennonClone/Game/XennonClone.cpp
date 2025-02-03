#include "XennonGameWorld.h"
#include "GameEngine.h"

int main(int argc, char** argv)
{
	// Create game engine and game world instances
	GameEngine game_engine;
	XennonGameWorld game_world;

	// Initialize game engine with configuration
	const char* WINDOW_TITLE = "XennonClone";
	const int WINDOW_WIDTH = 540;
	const int WINDOW_HEIGHT = 720;
	
	game_engine.init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, &game_world);
	
	// Start game loop
	game_engine.start_and_run();
	
	return 0;
}

