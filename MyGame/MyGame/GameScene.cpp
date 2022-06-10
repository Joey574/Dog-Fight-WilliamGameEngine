#include "GameScene.h"
#include "AI.h"
#include "Ammo.h"
#include "Ammo2.h"
#include "Background.h"
#include "Health1.h"
#include "Health2.h"
#include "BuffSpawner.h"
#include "Music.h"
#include "Ships(plural).h"
#include "EndScene.h"

GameScene::GameScene(int player_)
{
	BackgroundPtr background = std::make_shared<Background>();
	addGameObject(background);

	MusicPtr music = std::make_shared<Music>();
	addGameObject(music);

	ShipsPtr ships = std::make_shared<Ships>(0);
	addGameObject(ships);


	if (player_ == 1)
	{
		ships = std::make_shared<Ships>(2);
		addGameObject(ships);
	}
	else if (player_ == 2)
	{
		ships = std::make_shared<Ships>(1);
		addGameObject(ships);
	}

	AmmoPtr ammo = std::make_shared<Ammo>();
	addGameObject(ammo);

	Ammo2Ptr ammo2 = std::make_shared<Ammo2>();
	addGameObject(ammo2);

	Health1Ptr health1 = std::make_shared<Health1>();
	addGameObject(health1);

	Health2Ptr health2 = std::make_shared<Health2>();
	addGameObject(health2);

	BuffSpawnerPtr buffspawner = std::make_shared<BuffSpawner>();
	addGameObject(buffspawner);

	players(player_);
}

void GameScene::players(int player_)
{
	player = player_;
}


void GameScene::setAmmo1(int a)
{
	ammo1_ = a;
}

void GameScene::setAmmo2(int a)
{
	ammo2_ = a;
}

int GameScene::getAmmo1()
{
	return ammo1_;
}

int GameScene::getAmmo2()
{
	return ammo2_;
}

float GameScene::getHealth1()
{
	return health1_;
}

void GameScene::decreaseHealth1(float b)
{
	health1_ -= b;
	if (health1_ < 0)
	{
		health1_ = 0;
	}
	if (health1_ <= 0 || health2_ <= 0)
	{
		EndScenePtr end = std::make_shared<EndScene>(player, health1_, health2_);
		GAME.setScene(end);
	}
}

void GameScene::increaseHealth1()
{
	health1_ += 5;
	if (health1_ > 10)
	{
		health1_ = 10;
	}
}

float GameScene::getHealth2()
{
	return health2_;
}

void GameScene::decreaseHealth2(float b)
{
	health2_ -= b;
	if (health2_ < 0)
	{
		health2_ = 0;
	}
	if (health1_ <= 0 || health2_ <= 0)
	{
		EndScenePtr end = std::make_shared<EndScene>(player, health1_, health2_);
		GAME.setScene(end);
	}
}

void GameScene::increaseHealth2()
{
	health2_ += 5;
	if (health2_ > 10)
	{
		health2_ = 10;
	}
}

void GameScene::setShipPos(sf::Vector2f ship)
{
	shipPos = ship;
}

void GameScene::setEnemyPos(sf::Vector2f enemy)
{
	enemyPos = enemy;
}

sf::Vector2f GameScene::getShipPos()
{
	return shipPos;
}

sf::Vector2f GameScene::getEnemyPos()
{
	return enemyPos;
}

