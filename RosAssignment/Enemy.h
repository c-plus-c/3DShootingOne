#pragma once

#include "Object.h"

enum ENEMY_TYPE
{
	ENEMY_TYPE_EMISSION,
	ENEMY_TYPE_DIRECTIONAL,
};

class Enemy :public Object
{
	ENEMY_TYPE _enemyType;
	int _count;
public:
	Enemy(VECTOR direction, VECTOR translation, ENEMY_TYPE enemyType);
	virtual void Update(char input []);
	virtual void Draw();

	virtual bool GetExpired();
	virtual bool Collide(VECTOR translation, float radius);
};