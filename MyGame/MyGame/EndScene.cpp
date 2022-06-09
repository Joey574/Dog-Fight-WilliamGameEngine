#include "EndScene.h"
#include "EndMessage.h"

EndScene::EndScene(int player_, float health1_, float health2_)
{
	EndMessagePtr endMessage = std::make_shared<EndMessage>(player_, health1_, health2_);
	addGameObject(endMessage);
}