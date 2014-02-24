#include "dxlib.h"

#include <algorithm>
#include "ObjectField.h"

extern void DrawBackground();

void UpdateField()
{
	auto &ebullets = ObjectField::getObjectField().EnemyBullet;
	for (auto ite = ebullets.begin(); ite != ebullets.end(); ++ite)
	{
		ite->Update(NULL);

		if (ObjectField::getObjectField().player.Collide(ite->GetTranslation(), 0.3))
		{
			ObjectField::getObjectField().player.Damage(1);
			ite->SetHit(true);
		}
	}

	auto &enemies = ObjectField::getObjectField().Enemies;
	for (auto ite = enemies.begin(); ite != enemies.end(); ++ite)
	{
		ite->Update(NULL);
		if (ObjectField::getObjectField().player.Collide(ite->GetTranslation(), 0.5))
		{
			ObjectField::getObjectField().player.Damage(1);
			ite->SetDefeated(true);
		}
	}

	auto &pbullets = ObjectField::getObjectField().PlayerBullet;
	for (auto ite = pbullets.begin(); ite != pbullets.end(); ++ite)
	{
		ite->Update(NULL);
		for (auto ite2 = enemies.begin(); ite2 != enemies.end(); ++ite2)
		{
			if (ite->Collide(ite2->GetTranslation(), 1))
			{
				ite2->SetDefeated(true);
				ite->SetHit(true);
			}
		}
	}
}

void DrawField()
{
	auto &ebullets = ObjectField::getObjectField().EnemyBullet;
	for (auto ite = ebullets.begin(); ite != ebullets.end(); ++ite)
	{
		ite->Draw();
	}

	auto &enemies = ObjectField::getObjectField().Enemies;
	for (auto ite = enemies.begin(); ite != enemies.end(); ++ite)
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
	ObjectField::getObjectField().player = Player(VGet(10, 100, 0), 0, 0, 0);

	SetLightEnable(TRUE);
	ChangeLightTypePoint(VGet(0, 100, 0), 10000, 1, 0, 0);
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	ObjectField::getObjectField().Enemies.push_back(Enemy(VGet(0, 0, 0), VGet(0, 100, 0), ENEMY_TYPE_EMISSION));


	while (ProcessMessage() == 0)
	{
		ClsDrawScreen();

		GetHitKeyStateAll(buf);

		DrawBox(0, 0, 800, 600, GetColor(0, 0, 0), 1);

		DrawBackground();

		ObjectField::getObjectField().player.Update(buf);
		UpdateField();

		ObjectField::getObjectField().player.Draw();
		DrawField();

		ObjectField &field = ObjectField::getObjectField();
		field.EnemyBullet.erase(remove_if(field.EnemyBullet.begin(), field.EnemyBullet.end(), Bullet_Erase), field.EnemyBullet.end());
		field.PlayerBullet.erase(remove_if(field.PlayerBullet.begin(), field.PlayerBullet.end(), Bullet_Erase), field.PlayerBullet.end());
		field.Enemies.erase(remove_if(field.Enemies.begin(), field.Enemies.end(), Enemy_Erase), field.Enemies.end());

		if (buf[KEY_INPUT_ESCAPE]) break;
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}
