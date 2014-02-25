#pragma once

#include "DxLib.h"

class ResourceHandles
{
	ResourceHandles()
	{
		PlayerHandle = MV1LoadModel("resource/plane3.x");
		SkyHandle = MV1LoadModel("resource/sky.x");
		CloudHandle = MV1LoadModel("resource/bottomcloud.x");
		PlayerBulletHandle = MV1LoadModel("resource/playerBullet.x");
		EnemyBulletHandle = MV1LoadModel("resource/enemyBullet.x");
		HormingBulletHandle = MV1LoadModel("resource/hormingBullet.x");
		EnemyHandle = MV1LoadModel("resource/ufo.x");

		RadarPictureHandle = LoadGraph("resource/radar.png");
		playerIconHandle = LoadGraph("resource/red_icon.png");
		ufoIconHandle = LoadGraph("resource/ufo_icon.png");
		pFontHandle = CreateFontToHandle(NULL, 10, 1);

		MagicSquareHandle = LoadGraph("resource/magic_square.png");
		LoadDivGraph("resource/exp.png", 40, 4, 10, 301, 247, ExplosionHandle);

		BulletIconHandle = LoadGraph("resource/bullet_icon.png");

		TopPicture = LoadGraph("resource/top.png");

		PauseMask = LoadGraph("resource/pause_back.png");
		GameOverMask = LoadGraph("resource/gameover_mask.png");

		PlaneSideIcon = LoadGraph("resource/plane_side_50.png");

		AutoPilotNoticeHandle = LoadGraph("resource/autopilotnotice.jpg");

		ManualPicture = LoadGraph("resource/manual.png");

		PlayerHitSound = LoadSoundMem("resource/playerhit.ogg");
		EnemyHitSound = LoadSoundMem("resource/enemyhit.ogg");
		PlayerDieSound = LoadSoundMem("resource/die.ogg");
		NormalBulletSound = LoadSoundMem("resource/normalbullet.ogg");
		HormingBulletSound = LoadSoundMem("resource/hormingbullet.ogg");

		SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
		BGM = LoadBGM("resource/BGM.ogg");
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
	int BulletIconHandle;

	int MagicSquareHandle;
	int ExplosionHandle[40];
	int TopPicture;
	int ManualPicture;

	int PauseMask;
	int GameOverMask;
	int AutoPilotNoticeHandle;

	int PlaneSideIcon;

	int PlayerHitSound;
	int EnemyHitSound;
	int PlayerDieSound;
	int NormalBulletSound;
	int HormingBulletSound;

	int BGM;
};