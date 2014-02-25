#include "Enemy.h"
#include "ResorceHandles.h"

Enemy::Enemy(VECTOR direction, VECTOR translation, ENEMY_TYPE enemyType, float radius)
:Object(direction, translation)
{
	_enemyType = enemyType;
	_count = 0;
	_radius = radius;
	_enemyState = ENEMY_STATE_APPEARANCE;
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

bool Enemy_Erase(Enemy enemy)
{
	return enemy.GetExpired();
}