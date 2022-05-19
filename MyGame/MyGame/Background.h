#pragma once

#include "Engine//GameEngine.h"

class Background : public GameObject
{
public:

	Background();

	void draw();

private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<Background> BackgroundPtr;