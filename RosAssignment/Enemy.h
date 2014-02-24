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
	bool _defeated;
public:
	Enemy(VECTOR direction, VECTOR translation, ENEMY_TYPE enemyType);
	virtual void Update(char input []);
	virtual void Draw();

	virtual bool GetExpired();
	virtual bool Collide(VECTOR translation, float radius);

	void SetDefeated(bool defeated);
};

bool Enemy_Erase(Enemy enemy);