#pragma once

#include "Object.h"

class Bullet:Object
{
	int _damage;
	float _speed;
	bool _horming;
public:
	Bullet(VECTOR direction, VECTOR translation,int damage,float speed,bool horming);

	virtual void Update(char input []);
	virtual void Draw();

	int GetDamage();
	float GetSpeed();
};