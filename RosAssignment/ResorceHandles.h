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
		EnemyHandle = MV1LoadModel("ufo.x");

		RadarPictureHandle = LoadGraph("radar.png");
		playerIconHandle = LoadGraph("red_icon.png");
		ufoIconHandle = LoadGraph("red_icon.png");
		pFontHandle = CreateFontToHandle(NULL, 10, 1);

		MagicSquareHandle = LoadGraph("magic_square.png");
		LoadDivGraph("exp.png", 40, 4, 10, 301, 247, ExplosionHandle);
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
	int EnemyHandle;

	int PlayerBulletHandle;
	int EnemyBulletHandle;
	int HormingBulletHandle;

	int RadarPictureHandle;
	int playerIconHandle;
	int ufoIconHandle;
	int pFontHandle;

	int MagicSquareHandle;
	int ExplosionHandle[40];
};