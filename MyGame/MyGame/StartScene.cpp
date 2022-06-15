#include "StartScene.h"
#include "StartMessage.h"
#include "StartMusic.h"

StartScene::StartScene()
{
	StartMusicPtr startMusic = std::make_shared<StartMusic>();
	addGameObject(startMusic);

	StartMessagePtr startMessage = std::make_shared<StartMessage>();
	addGameObject(startMessage);
}