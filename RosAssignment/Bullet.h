#pragma once

#include "Object.h"
#include "ResorceHandles.h"

enum BULLET_TYPE
{
	BULLET_TYPE_PLAYER,
	BULLET_TYPE_ENEMY,
	BULLET_TYPE_PLAYER_HORMING,
};

class Bullet:Object
{
	int _damage;
	float _speed;
	bool _horming;
	BULLET_TYPE _bulletType;
	int _count;
public:
	Bullet(VECTOR direction, VECTOR translation,int damage,float speed,bool horming,BULLET_TYPE bulletType);

	virtual void Update(char input []);
	virtual void Draw();
	virtual bool GetExpired();

	int GetDamage();
	float GetSpeed();
};

bool Bullet_Erase(Bullet bullet);