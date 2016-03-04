#pragma once

#include "Object.h"

enum ENEMY_TYPE
{
	ENEMY_TYPE_EMISSION,
	ENEMY_TYPE_DIRECTIONAL,
};

enum ENEMY_STATE
{
	ENEMY_STATE_APPEARANCE,
	ENEMY_STATE_NORMAL,
	ENEMY_STATE_DYING,
	ENEMY_STATE_DIE
};

class Enemy :public Object
{
	ENEMY_TYPE _enemyType;
	ENEMY_STATE _enemyState;
	int _count;
	float _radius;
	int _shotRate;
	float _speed;
	int _shotOffset;
public:
	Enemy(VECTOR direction, VECTOR translation, ENEMY_TYPE enemyType,float radius,float speed,int shotRate);
	virtual void Update(char input []);
	virtual void Draw();

	virtual bool GetExpired();
	virtual bool Collide(VECTOR translation, float radius);

	void SetDefeated();
	float GetRadius();
	ENEMY_STATE GetState();
};