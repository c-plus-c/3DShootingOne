#include "Bullet.h"
#include "ObjectField.h"

Bullet::Bullet(VECTOR direction, VECTOR translation, int damage, float speed,  BULLET_TYPE bulletType)
:Object(direction,translation)
{
	_damage = damage;
	_speed = speed;
	_bulletType = bulletType;
	_count = 0;
	_targetEnemy = NULL;
	_hit = false;
	if (_bulletType == BULLET_TYPE_PLAYER_HORMING)
	{
		float mdist = 10000000;
		auto &field = ObjectField::getObjectField().Enemies;

		for (auto f = field.begin(); f != field.end(); ++f)
		{
			VECTOR v = VSub(_translation, f->GetTranslation());
			float dist = VDot(v, v);
			if (mdist > dist)
			{
				mdist = dist;
				_targetEnemy = &(*f);
			}
		}
	}
}

void Bullet::Update(char input[])
{
	if (_bulletType == BULLET_TYPE_PLAYER_HORMING&&_targetEnemy!=NULL)
	{
		VECTOR c;
		c = VSub(_targetEnemy->GetTranslation(), _translation);
		c = VNorm(c);
		c = VScale(c, _count*(5.0 / 180.0));
		_direction = VAdd(c, _direction);
		_direction = VNorm(_direction);
	}

	_translation = VAdd(_translation, VScale(_direction, _speed));
	++_count;
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
	return ((_bulletType == BULLET_TYPE_PLAYER_HORMING&&_targetEnemy == NULL) || (_count >= BULLET_EXPIRE_COUNT) || _hit);
}

bool Bullet_Erase(Bullet bullet)
{
	return bullet.GetExpired();
}

void Bullet::SetHit(bool hit)
{
	_hit = hit;
}

bool Bullet::Collide(VECTOR translation, float radius)
{
	VECTOR sub = VSub(_translation, translation);
	float dist = VDot(sub, sub);
	return dist <= (radius + 0.3)*(radius + 0.3);
}