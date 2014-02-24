#include "Bullet.h"

Bullet::Bullet(VECTOR direction, VECTOR translation, int damage, float speed,  bool horming,BULLET_TYPE bulletType)
:Object(direction,translation)
{
	_damage = damage;
	_speed = speed;
	_horming = horming;
	_bulletType = bulletType;
	_count = 0;
}

void Bullet::Update(char input[])
{
	_translation = VAdd(_translation, VScale(_direction, _speed));
	_count;
}

void Bullet::Draw()
{
	SetUseLighting(FALSE);
	//SetUseLighting(TRUE);

	switch (_bulletType)
	{
	case BULLET_TYPE_ENEMY:
		MV1SetScale(ResourceHandles::getResourceHandles().EnemyBulletHandle, VGet(0.3, 0.3, 0.3));
		MV1SetPosition(ResourceHandles::getResourceHandles().EnemyBulletHandle, _translation);
		MV1DrawModel(ResourceHandles::getResourceHandles().EnemyBulletHandle);
		break;
	case BULLET_TYPE_PLAYER:
		MV1SetScale(ResourceHandles::getResourceHandles().PlayerBulletHandle, VGet(0.3, 0.3, 0.3));
		MV1SetPosition(ResourceHandles::getResourceHandles().PlayerBulletHandle, _translation);
		MV1DrawModel(ResourceHandles::getResourceHandles().PlayerBulletHandle);
		break;
	case BULLET_TYPE_PLAYER_HORMING:
		MV1SetScale(ResourceHandles::getResourceHandles().HormingBulletHandle, VGet(0.3, 0.3, 0.3));
		MV1SetPosition(ResourceHandles::getResourceHandles().HormingBulletHandle, _translation);
		MV1DrawModel(ResourceHandles::getResourceHandles().HormingBulletHandle);
		break;
	default:
		break;
	}
}

int Bullet::GetDamage()
{
	return _damage;
}

float Bullet::GetSpeed()
{
	return _speed;
}

bool Bullet::GetExpired()
{
	return (_count >= 300);
}

bool Bullet_Erase(Bullet bullet)
{
	return bullet.GetExpired();
}