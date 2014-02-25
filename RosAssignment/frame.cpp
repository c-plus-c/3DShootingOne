#include "Frame.h"
#include <algorithm>
#include "ObjectField.h"

Frame& Frame::getFrame()
{
	static Frame frame;
	return frame;
}

Frame::Frame()
{
	_scene = SCENE_TOP;
	_end = false;
}

void Frame::DrawBackground()
{
	SetUseLighting(FALSE);
	MV1SetScale(ResourceHandles::getResourceHandles().SkyHandle, VGet(500, 500, 500));
	MV1DrawModel(ResourceHandles::getResourceHandles().SkyHandle);

	SetUseLighting(FALSE);
	MV1SetScale(ResourceHandles::getResourceHandles().CloudHandle, VGet(550, 40, 550));
	MV1DrawModel(ResourceHandles::getResourceHandles().CloudHandle);
}

void Frame::Top()
{
	DrawGraph(0, 0, ResourceHandles::getResourceHandles().TopPicture, 0);
	if (buf[KEY_INPUT_Z])
	{
		ObjectField::getObjectField().player = Player(VGet(10, 100, 0), 0, 0, 0);
		_scene = SCENE_PLAY;
	}
	else if (buf[KEY_INPUT_ESCAPE])
	{
		_end = true;
	}
}

void Frame::Play()
{
	DrawBox(0, 0, 800, 600, GetColor(0, 0, 0), 1);

	DrawBackground();

	ObjectField::getObjectField().player.Update(buf);
	UpdateField();

	ObjectField::getObjectField().player.Draw();
	DrawField();

	DrawRadar();

	ObjectField &field = ObjectField::getObjectField();
	field.EnemyBullet.erase(remove_if(field.EnemyBullet.begin(), field.EnemyBullet.end(), Bullet_Erase), field.EnemyBullet.end());
	field.PlayerBullet.erase(remove_if(field.PlayerBullet.begin(), field.PlayerBullet.end(), Bullet_Erase), field.PlayerBullet.end());
	field.Enemies.erase(remove_if(field.Enemies.begin(), field.Enemies.end(), Enemy_Erase), field.Enemies.end());
}

void Frame::Manual()
{

}

void Frame::Pause()
{

}

void Frame::UpdateField()
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

		if (ObjectField::getObjectField().player.Collide(ite->GetTranslation(), ite->GetRadius()*0.5))
		{
			ObjectField::getObjectField().player.Damage(1);
			ite->SetDefeated();
		}
	}

	auto &pbullets = ObjectField::getObjectField().PlayerBullet;
	for (auto ite = pbullets.begin(); ite != pbullets.end(); ++ite)
	{
		ite->Update(NULL);
		for (auto ite2 = enemies.begin(); ite2 != enemies.end(); ++ite2)
		{
			if (ite->Collide(ite2->GetTranslation(), ite2->GetRadius()))
			{
				ite2->SetDefeated();
				ite->SetHit(true);
			}
		}
	}
}

void Frame::DrawField()
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

void Frame::Run()
{
	GetHitKeyStateAll(buf);
	switch (_scene)
	{
	case SCENE_TOP:
		Top();
		break;
	case SCENE_PLAY:
		Play();
		break;
	case SCENE_PAUSE:
		Pause();
		break;
	case SCENE_MANUAL:
		Manual();
		break;
	}
}

bool Frame::End()
{
	return _end;
}