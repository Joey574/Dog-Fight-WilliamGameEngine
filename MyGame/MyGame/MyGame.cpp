#include "Engine/GameEngine.h"
#include "GameScene.h"
#include "StartScene.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const std::string WINDOW_TITLE = "tWO mANS sKY";

int main()
{
	// Seed the random number generator.
	srand((int)time(NULL));

	// Initialize the game.
	GAME.initialize(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// Create our scene.
	StartScenePtr start = std::make_shared<StartScene>();
	GAME.setScene(start);

	// Run the game loop.
	GAME.run();

	return 0;
}