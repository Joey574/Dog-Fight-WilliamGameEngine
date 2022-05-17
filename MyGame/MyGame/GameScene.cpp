#include "GameScene.h"
#include "Ship.h"
#include "Enemy.h"

GameScene::GameScene()
{
	ShipPtr ship = std::make_shared<Ship>();
	addGameObject(ship);

	EnemyPtr enemy = std::make_shared<Enemy>();
	addGameObject(enemy);
}

int GameScene::getAmmo()
{
	return ammo_;
}

void GameScene::decreaseAmmo()
{
	ammo_--;
}