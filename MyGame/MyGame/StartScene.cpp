#include "StartScene.h"
#include "StartMessage.h"

StartScene::StartScene()
{
	StartMessagePtr startMessage = std::make_shared<StartMessage>();
	addGameObject(startMessage);
}