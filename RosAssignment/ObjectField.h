#pragma once

#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class ObjectField
{
	ObjectField()
	{
	}
public:
	static ObjectField& getObjectField()
	{
		static ObjectField objectField;
		return objectField;
	}
	Player player;
	std::vector<Bullet> PlayerBullet;
	std::vector<Bullet> EnemyBullet;
	std::vector<Enemy> Enemies;
};