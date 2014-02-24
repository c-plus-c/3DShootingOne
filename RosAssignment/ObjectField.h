#pragma once

#include <vector>
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

	std::vector<Bullet> PlayerBullet;
	std::vector<Bullet> EnemyBullet;
	std::vector<Enemy> Enemies;
};