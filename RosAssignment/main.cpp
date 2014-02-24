#include "dxlib.h"

#include <algorithm>
#include "ObjectField.h"
#include "Player.h"

extern void DrawBackground();

void UpdateField()
{
	auto &ebullets = ObjectField::getObjectField().EnemyBullet;
	for (auto ite = ebullets.begin(); ite != ebullets.end(); ++ite)
	{
		ite->Update(NULL);
	}

	auto &pbullets = ObjectField::getObjectField().PlayerBullet;
	for (auto ite = pbullets.begin(); ite != pbullets.end(); ++ite)
	{
		ite->Update(NULL);
	}
}

void DrawField()
{
	auto &ebullets = ObjectField::getObjectField().EnemyBullet;
	for (auto ite = ebullets.begin(); ite != ebullets.end(); ++ite)
	{
		ite->Draw();
	}

	auto &pbullets = ObjectField::getObjectField().PlayerBullet;
	for (auto ite = pbullets.begin(); ite != pbullets.end(); ++ite)
	{
		ite->Draw();
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	
	
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 32);
	if (DxLib_Init()<0) return -1;

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);

	char buf[256];
	Player player = Player(VGet(0, 100, 0), 0, 0, 0);

	SetLightEnable(TRUE);
	ChangeLightTypePoint(VGet(0, 100, 0), 10000, 1, 0, 0);
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
	while (ProcessMessage() == 0)
	{
		ClsDrawScreen();

		GetHitKeyStateAll(buf);

		DrawBox(0, 0, 800, 600, GetColor(0, 0, 0), 1);

		DrawBackground();

		player.Update(buf);
		UpdateField();

		player.Draw();
		DrawField();

		ObjectField &field = ObjectField::getObjectField();
		field.EnemyBullet.erase(remove_if(field.EnemyBullet.begin(), field.EnemyBullet.end(), Bullet_Erase), field.EnemyBullet.end());
		field.PlayerBullet.erase(remove_if(field.PlayerBullet.begin(), field.PlayerBullet.end(), Bullet_Erase), field.PlayerBullet.end());

		if (buf[KEY_INPUT_ESCAPE]) break;
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}
