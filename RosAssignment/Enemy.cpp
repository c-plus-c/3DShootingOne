#include "Enemy.h"
#include "ResorceHandles.h"
#include "ObjectField.h"
#include "Player.h"

Enemy::Enemy(VECTOR direction, VECTOR translation, ENEMY_TYPE enemyType, float radius, float speed, int shotRate)
:Object(direction, translation)
{
	_direction = VNorm(direction);
	_enemyType = enemyType;
	_count = 0;
	_radius = radius;
	_enemyState = ENEMY_STATE_APPEARANCE;
	_shotRate = shotRate;
	_speed = speed;
}

void Enemy::Update(char input [])
{

	switch (_enemyState)
	{
	case ENEMY_STATE_APPEARANCE:
		if (_count == 45)
		{
			_enemyState = ENEMY_STATE_NORMAL;
		}
		break;
	case ENEMY_STATE_NORMAL:

		if (_count%_shotRate == 0)
		{
			VECTOR target;
			VECTOR playerPos = ObjectField::getObjectField().player.GetTranslation();

			target.x = playerPos.x - 5 + rand() % 10;
			target.y = playerPos.y - 5 + rand() % 10;
			target.z = playerPos.z - 5 + rand() % 10;

			VECTOR v = VSub(target, _translation);
			v = VNorm(v);
			ObjectField::getObjectField().EnemyBullet.push_back(Bullet(v, _translation, 1, 2, BULLET_TYPE_ENEMY,2.0f));
		}

		_translation = VAdd(_translation, VScale(_direction, _speed));

		if ((_translation.x*_translation.x + _translation.z*_translation.z >= ACTIVE_RADIUS*ACTIVE_RADIUS) || _translation.y <= ACTIVE_LOWEST || _translation.y >= ACTIVE_HIGHEST)
		{
			_direction = VScale(_direction, -1);
		}
		break;
	case ENEMY_STATE_DYING:
		if (_count == 39) _enemyState = ENEMY_STATE_DIE;
		break;
	}
	++_count;
}

void Enemy::Draw()
{
	switch (_enemyState)
	{
	case ENEMY_STATE_APPEARANCE:
		DrawBillboard3D(_translation, 0.5f, 0.5f, _radius*3, _count*DX_PI / 180.0, ResourceHandles::getResourceHandles().MagicSquareHandle, TRUE);
		MV1SetScale(ResourceHandles::getResourceHandles().EnemyHandle, VScale(VGet(_radius, _radius, _radius), _count / 45.0));
		MV1SetRotationXYZ(ResourceHandles::getResourceHandles().EnemyHandle, VGet(0, _count * DX_PI / 180.0f, 0));
		MV1SetPosition(ResourceHandles::getResourceHandles().EnemyHandle, _translation);
		MV1DrawModel(ResourceHandles::getResourceHandles().EnemyHandle);
		break;
	case ENEMY_STATE_NORMAL:
		MV1SetScale(ResourceHandles::getResourceHandles().EnemyHandle, VGet(_radius, _radius, _radius));
		MV1SetRotationXYZ(ResourceHandles::getResourceHandles().EnemyHandle, VGet(0, _count * DX_PI / 180.0f, 0));
		MV1SetPosition(ResourceHandles::getResourceHandles().EnemyHandle, _translation);
		MV1DrawModel(ResourceHandles::getResourceHandles().EnemyHandle);
		break;
	case ENEMY_STATE_DYING:
		DrawBillboard3D(_translation, 0.5f, 0.5f, _radius*3, 0, ResourceHandles::getResourceHandles().ExplosionHandle[_count], TRUE);
		break;
	}
}

bool Enemy::GetExpired()
{
	return _enemyState == ENEMY_STATE_DIE;
}

void Enemy::SetDefeated()
{
	_enemyState = ENEMY_STATE_DYING;
	_count = 0;
}

bool Enemy::Collide(VECTOR translation, float radius)
{
	VECTOR sub = VSub(_translation, translation);
	float dist = VDot(sub, sub);
	return dist <= (radius + _radius)*(radius + _radius);
}

float Enemy::GetRadius()
{
	return _radius;
}

ENEMY_STATE Enemy::GetState()
{
	return _enemyState;
}

bool Enemy_Erase(Enemy enemy)
{
	return enemy.GetExpired();
}