#include "GameScene.h"
#include "Ship.h"
#include "Enemy.h"
#include "Ammo.h"
#include "Ammo2.h"
#include "Background.h"

GameScene::GameScene()
{
	BackgroundPtr background = std::make_shared<Background>();
	addGameObject(background);

	ShipPtr ship = std::make_shared<Ship>();
	addGameObject(ship);

	EnemyPtr enemy = std::make_shared<Enemy>();
	addGameObject(enemy);

	AmmoPtr ammo = std::make_shared<Ammo>();
	addGameObject(ammo);

	Ammo2Ptr ammo2 = std::make_shared<Ammo2>();
	addGameObject(ammo2);
}

int GameScene::getAmmo1()
{
	return ammo1_;
}

void GameScene::decreaseAmmo1(int a)
{
	ammo1_ -= a;
}

int GameScene::getAmmo2()
{
	return ammo2_;
}

void GameScene::decreaseAmmo2(int a)
{
	ammo2_ -= a;
}

int GameScene::getHealth1()
{
	return health1_;
}

void GameScene::decreaseHealth1(int a)
{
	health1_ -= a;
}

int GameScene::getHealth2()
{
	return health2_;
}

void GameScene::decreaseHealth2(int a)
{
	health2_ -= a;
}