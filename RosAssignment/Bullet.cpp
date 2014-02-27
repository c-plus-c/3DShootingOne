#include "Bullet.h"
#include "ObjectField.h"

Bullet::Bullet(VECTOR direction, VECTOR translation, int damage, float speed,  BULLET_TYPE bulletType,float size)
:Object(direction,translation)
{
	_damage = damage;
	_size = size;
	_speed = speed;
	_bulletType = bulletType;
	_count = 0;
	_targetEnemy = NULL;
	_hit = false;
	if (_bulletType == BULLET_TYPE_PLAYER_HORMING)
	{
		float mdist = FLT_MAX;
		auto &field = ObjectField::getObjectField().Enemies;

		for (int i = 0; i<(int)field.size();++i)
		{
			VECTOR v = VSub(_translation, field[i].GetTranslation());
			float dist = VDot(v, v);
			if (mdist > dist)
			{
				mdist = dist;
				_targetEnemy = &field[i];
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

	if (_bulletType == BULLET_TYPE_ENEMY)
	{
		if ((_translation.x*_translation.x + _translation.z*_translation.z >= ACTIVE_RADIUS*ACTIVE_RADIUS) || _translation.y <= ACTIVE_LOWEST || _translation.y >= ACTIVE_HIGHEST)
		{
			_direction = VScale(_direction, -1);
		}
	}

	++_count;
}

void Bullet::Draw()
{
	SetUseLighting(FALSE);
	//SetUseLighting(TRUE);

	switch (_bulletType)
	{
	case BULLET_TYPE_ENEMY:
		MV1SetScale(ResourceHandles::getResourceHandles().EnemyBulletHandle, VGet(_size, _size, _size));
		MV1SetPosition(ResourceHandles::getResourceHandles().EnemyBulletHandle, _translation);
		MV1DrawModel(ResourceHandles::getResourceHandles().EnemyBulletHandle);
		break;
	case BULLET_TYPE_PLAYER:
		MV1SetScale(ResourceHandles::getResourceHandles().PlayerBulletHandle, VGet(_size, _size, _size));
		MV1SetPosition(ResourceHandles::getResourceHandles().PlayerBulletHandle, _translation);
		MV1DrawModel(ResourceHandles::getResourceHandles().PlayerBulletHandle);
		break;
	case BULLET_TYPE_PLAYER_HORMING:
		MV1SetScale(ResourceHandles::getResourceHandles().HormingBulletHandle, VGet(_size, _size, _size));
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
	return dist <= (radius + _size)*(radius + _size);
}
