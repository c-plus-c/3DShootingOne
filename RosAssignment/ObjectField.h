#pragma once

#include <vector>
#include "Player.h"
#include "Bullet.h"

class ObjectField
{
	ObjectField(){}
public:
	static ObjectField& getInstance()
	{
		static ObjectField objectField;
		return objectField;
	}

	std::vector<Bullet> PlayerBullet;
	std::vector<Bullet> EnemyBullet;

	int PlayerHandle;
	int SkyHandle;
	int CloudHandle;
};