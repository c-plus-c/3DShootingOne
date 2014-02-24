#pragma once

#include "DxLib.h"

class ResourceHandles
{
	ResourceHandles()
	{
		PlayerHandle = MV1LoadModel("plane3.x");
		SkyHandle = MV1LoadModel("sky.x");
		CloudHandle = MV1LoadModel("bottomcloud.x");
		PlayerBulletHandle = MV1LoadModel("playerBullet.x");
		EnemyBulletHandle = MV1LoadModel("enemyBullet.x");
		HormingBulletHandle = MV1LoadModel("hormingBullet.x");
	}
public:
	static ResourceHandles& getResourceHandles()
	{
		static ResourceHandles objectField;
		return objectField;
	}
	int PlayerHandle;
	int SkyHandle;
	int CloudHandle;

	int PlayerBulletHandle;
	int EnemyBulletHandle;
	int HormingBulletHandle;
};