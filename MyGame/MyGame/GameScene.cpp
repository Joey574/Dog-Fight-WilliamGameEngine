#include "GameScene.h"
#include "Ship.h"
#include "Enemy.h"
#include "AI.h"
#include "Ammo.h"
#include "Ammo2.h"
#include "Background.h"
#include "Health1.h"
#include "Health2.h"

GameScene::GameScene()
{
	BackgroundPtr background = std::make_shared<Background>();
	addGameObject(background);

	ShipPtr ship = std::make_shared<Ship>();
	addGameObject(ship);

	EnemyPtr enemy = std::make_shared<Enemy>();
	addGameObject(enemy);

	/*AIPtr ai = std::make_shared<AI>();
	addGameObject(ai);*/

	AmmoPtr ammo = std::make_shared<Ammo>();
	addGameObject(ammo);

	Ammo2Ptr ammo2 = std::make_shared<Ammo2>();
	addGameObject(ammo2);

	Health1Ptr health1 = std::make_shared<Health1>();
	addGameObject(health1);

	Health2Ptr health2 = std::make_shared<Health2>();
	addGameObject(health2);
}

int GameScene::getAmmo1()
{
	return ammo1_;
}

void GameScene::decreaseAmmo1(int a)
{
	ammo1_ -= a;
}

void GameScene::increaseAmmo1()
{
	ammo1_ = 200;
}

int GameScene::getAmmo2()
{
	return ammo2_;
}

void GameScene::decreaseAmmo2(int a)
{
	ammo2_ -= a;
}

void GameScene::increaseAmmo2()
{
	ammo2_ = 200;
}

int GameScene::getHealth1()
{
	return health1_;
}

void GameScene::decreaseHealth1()
{
	health1_ --;
}

void GameScene::increaseHealth1()
{
	health1_ += 5;
}

int GameScene::getHealth2()
{
	return health2_;
}

void GameScene::decreaseHealth2()
{
	health2_ --;
}

void GameScene::increaseHealth2()
{
	health2_ += 5;
}

//sf::Vector2f getShipCords()
//{
//	Ship::
//}