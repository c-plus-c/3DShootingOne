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
	_count = 0;
	_waitCount = 0;
}

void Frame::DrawBackground()
{
	SetUseLighting(FALSE);
	MV1SetScale(ResourceHandles::getResourceHandles().SkyHandle, VGet(ACTIVE_RADIUS * 5, ACTIVE_HIGHEST+15, ACTIVE_RADIUS * 5));
	MV1DrawModel(ResourceHandles::getResourceHandles().SkyHandle);

	SetUseLighting(FALSE);
	MV1SetScale(ResourceHandles::getResourceHandles().CloudHandle, VGet(550, 40, 550));
	MV1DrawModel(ResourceHandles::getResourceHandles().CloudHandle);
}

void Frame::Top()
{
	DrawGraph(0, 0, ResourceHandles::getResourceHandles().TopPicture, 0);

	++_waitCount;
	if (_waitCount <= 90) return;
	if (buf[KEY_INPUT_Z])
	{
		InitializeGame();
		_scene = SCENE_PLAY;
		PlaySoundMem(ResourceHandles::getResourceHandles().BGM, DX_PLAYTYPE_LOOP);
	}
	else if (buf[KEY_INPUT_X])
	{
		_scene = SCENE_MANUAL;
		_waitCount = 0;
	}
	else if (buf[KEY_INPUT_ESCAPE])
	{
		_end = true;
	}
}

void Frame::Play()
{
	if (_count%ADDITION_CYCLE == 0) AddNewObjects();

	_level = _score / LEVELUP_SCORE + 1;

	ObjectField::getObjectField().player.Update(buf);
	UpdateField();


	DrawBox(0, 0, 800, 600, GetColor(0, 0, 0), 1);
	DrawBackground();

	ObjectField::getObjectField().player.Draw();
	DrawField();

	DrawRadar();
	DrawStatus();

	ObjectField &field = ObjectField::getObjectField();
	field.EnemyBullet.erase(remove_if(field.EnemyBullet.begin(), field.EnemyBullet.end(), Bullet_Erase), field.EnemyBullet.end());
	field.PlayerBullet.erase(remove_if(field.PlayerBullet.begin(), field.PlayerBullet.end(), Bullet_Erase), field.PlayerBullet.end());
	field.Enemies.erase(remove_if(field.Enemies.begin(), field.Enemies.end(), Enemy_Erase), field.Enemies.end());

	++_count;

	if (ObjectField::getObjectField().player.GetExpired())
	{
		DrawGraph(0, 0, ResourceHandles::getResourceHandles().GameOverMask, 1);
		++_waitCount;
		if (_waitCount >= 90 && buf[KEY_INPUT_Z] == 1)
		{
			StopSoundMem(ResourceHandles::getResourceHandles().BGM);
			_waitCount = 0;
			_scene = SCENE_TOP;
		}
	}
	else if (buf[KEY_INPUT_ESCAPE] == 1)
	{
		_scene = SCENE_PAUSE;
		_waitCount = 0;

		_pausePicture = MakeGraph(800, 600);
		// âÊñ ÉfÅ[É^ÇÃéÊÇËÇ±Ç›
		GetDrawScreenGraph(0, 0, 800, 600, _pausePicture);
	}
}

void Frame::Manual()
{
	DrawGraph(0, 0, ResourceHandles::getResourceHandles().ManualPicture, 0);

	++_waitCount;
	if (_waitCount <= 90) return;
	if (buf[KEY_INPUT_Z])
	{
		_scene = SCENE_TOP;
		_waitCount = 0;
	}
}

void Frame::Pause()
{
	SetDrawBright(128, 128, 128);
	DrawGraph(0, 0, _pausePicture, 0);
	SetDrawBright(255, 255, 255);
	DrawGraph(0, 0, ResourceHandles::getResourceHandles().PauseMask, 1);

	++_waitCount;
	if (_waitCount <= 90) return;

	if (buf[KEY_INPUT_Q] == 1)
	{
		_scene = SCENE_TOP;
		_waitCount = 0;
		StopSoundMem(ResourceHandles::getResourceHandles().BGM);
	}
	else if (buf[KEY_INPUT_C] == 1)
	{
		_waitCount = 0;
		_scene = SCENE_PLAY;
	}
	else if (buf[KEY_INPUT_R] == 1)
	{
		_waitCount = 0;
		InitializeGame();
		_scene = SCENE_PLAY;
	}
}

void Frame::AddNewObjects()
{

	int enemySum = 30 * (1 - 1 / exp(_level / 10.0));

	int addSum = enemySum - (int)ObjectField::getObjectField().Enemies.size();

	for (int i = 0; i < addSum; ++i)
	{
		float r = rand() % ACTIVE_RADIUS;
		float theta = (rand() % 360)*DX_PI / 180.0;
		float x = r*cos(theta);
		float y = ACTIVE_LOWEST + (rand() % (ACTIVE_HIGHEST - ACTIVE_LOWEST));
		float z = r*sin(theta);
		float size = 10.0 + (rand() % 10);

		float dx = rand() % 10;
		float dy = rand() % 10;
		float dz = rand() % 10;

		float speed = (1.5*min(10, _level - 1) / 10)*(rand() / 32768.0);

		int rateraw = max(-20 * _level + 320, 20);

		rateraw = rateraw - 4 * (rand() % 10);

		ObjectField::getObjectField().Enemies.push_back(Enemy(VGet(dx, dy, dz), VGet(x, y, z), ENEMY_TYPE_EMISSION, size, speed, rateraw));
	}
}

void Frame::UpdateField()
{
	auto &ebullets = ObjectField::getObjectField().EnemyBullet;
	for (auto ite = ebullets.begin(); ite != ebullets.end(); ++ite)
	{
		ite->Update(NULL);

		if (ite->Collide(ObjectField::getObjectField().player.GetTranslation(),1))
		{
			ObjectField::getObjectField().player.Damage(1);
			ite->SetHit(true);
			PlaySoundMem(ResourceHandles::getResourceHandles().PlayerHitSound, DX_PLAYTYPE_BACK);
		}
	}

	auto &enemies = ObjectField::getObjectField().Enemies;
	for (auto ite = enemies.begin(); ite != enemies.end(); ++ite)
	{
		ite->Update(NULL);

		if (ite->GetState() == ENEMY_STATE_NORMAL&& ObjectField::getObjectField().player.Collide(ite->GetTranslation(), ite->GetRadius()*0.5))
		{
			ObjectField::getObjectField().player.Damage(1);
			ite->SetDefeated();
			PlaySoundMem(ResourceHandles::getResourceHandles().PlayerHitSound, DX_PLAYTYPE_BACK);
			PlaySoundMem(ResourceHandles::getResourceHandles().EnemyHitSound, DX_PLAYTYPE_BACK);
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
				_score += DEFEAT_SCORE;
				PlaySoundMem(ResourceHandles::getResourceHandles().EnemyHitSound, DX_PLAYTYPE_BACK);
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

void Frame::DrawRadar()
{
	DrawExtendGraph(601, 401, 601 + 184, 401 + 184, ResourceHandles::getResourceHandles().RadarPictureHandle, 1);

	{
		VECTOR ptrans = ObjectField::getObjectField().player.GetTranslation();
		VECTOR pdir = ObjectField::getObjectField().player.GetDirection();

		DrawRotaGraph(692 + 92 * (ptrans.x / ACTIVE_RADIUS), 493 - 92 * (ptrans.z / ACTIVE_RADIUS), 0.45, atan2(-pdir.z, pdir.x) + DX_PI / 2, ResourceHandles::getResourceHandles().playerIconHandle, 1);
		DrawFormatString(692 + 92 * (ptrans.x / ACTIVE_RADIUS) - 25, 493 - 92 * (ptrans.z / ACTIVE_RADIUS) - 25, GetColor(255, 255, 255), "%d", (int) ptrans.y);
	}

	auto &enemies = ObjectField::getObjectField().Enemies;
	for (auto ite = enemies.begin(); ite != enemies.end(); ++ite)
	{
		VECTOR ptrans = ite->GetTranslation();
		DrawRotaGraph(692 + 92 * (ptrans.x / ACTIVE_RADIUS), 493 - 92 * (ptrans.z / ACTIVE_RADIUS), 0.45, 0, ResourceHandles::getResourceHandles().ufoIconHandle, 1);
		DrawFormatString(692 + 92 * (ptrans.x / ACTIVE_RADIUS) - 25, 493 - 92 * (ptrans.z / ACTIVE_RADIUS) - 25, GetColor(255, 255, 255), "%d", (int) ptrans.y);
	}

	auto &ebullets = ObjectField::getObjectField().EnemyBullet;
	for (auto ite = ebullets.begin(); ite != ebullets.end(); ++ite)
	{
		VECTOR ptrans = ite->GetTranslation();
		DrawRotaGraph(692 + 92 * (ptrans.x / ACTIVE_RADIUS), 493 - 92 * (ptrans.z / ACTIVE_RADIUS), 0.45, 0, ResourceHandles::getResourceHandles().BulletIconHandle, 1);
		DrawFormatString(692 + 92 * (ptrans.x / ACTIVE_RADIUS) - 25, 493 - 92 * (ptrans.z / ACTIVE_RADIUS) - 25, GetColor(255, 255, 255), "%d", (int) ptrans.y);
	}
}

void Frame::InitializeGame()
{
	_count = 0;
	_score = 0;
	_level = 1;

	ObjectField::getObjectField().Enemies.clear();
	ObjectField::getObjectField().EnemyBullet.clear();
	ObjectField::getObjectField().PlayerBullet.clear();

	ObjectField::getObjectField().player = Player(VGet(10, 100, 0), 0, 0, 0);
}

bool Frame::End()
{
	return _end;
}

void Frame::DrawStatus()
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Life : %d/%d", ObjectField::getObjectField().player.GetLife(),FIRST_LIFE);
	DrawFormatString(150, 10, GetColor(255, 255, 255), "Level : %d", _level);
	DrawFormatString(650, 10, GetColor(255, 255, 255), "Score : %08d", _score);

	DrawBox(10, 550, 10 + (290 * (float) SHOT_HANDI / (float) HORMINGSHOT_HANDI), 590, GetColor(255, 0, 255), 0);
	DrawBox(10, 550, 300, 590, GetColor(255, 255, 255), 0);
	float shotlockcount = (float) ObjectField::getObjectField().player.GetShotLockCount();
	DrawBox(10, 550, 10 + (290 * min(1, shotlockcount / (float) HORMINGSHOT_HANDI)), 590, (shotlockcount >= HORMINGSHOT_HANDI) ? GetColor(255, 0, 0) : (shotlockcount >= SHOT_HANDI) ? GetColor(255, 0, 255) : GetColor(255, 255, 255), 1);

	DrawString(310, 550, (shotlockcount >= SHOT_HANDI) ? "Normal Bullet  :  Ready" : "Normal Bullet  :  Charging...", GetColor(255, 0, 255),1);
	DrawString(310, 570, (shotlockcount >= HORMINGSHOT_HANDI) ? "Horming Bullet :  Ready" : "Horming Bullet :  Charging...", GetColor(255, 0, 0),1);

	float pitch = ObjectField::getObjectField().player.GetPitch();

	DrawRotaGraph(595, 570, 1, pitch, ResourceHandles::getResourceHandles().PlaneSideIcon, 1);

	if (ObjectField::getObjectField().player.GetSideOut())
	{
		DrawGraph(300, 10, ResourceHandles::getResourceHandles().AutoPilotNoticeHandle, 0);
	}
}