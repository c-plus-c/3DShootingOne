#pragma once

#include "Object.h"
#include "ResorceHandles.h"
#include "Enemy.h"

#define BULLET_EXPIRE_COUNT 300

enum BULLET_TYPE
{
	BULLET_TYPE_PLAYER,
	BULLET_TYPE_ENEMY,
	BULLET_TYPE_PLAYER_HORMING,
};

class Bullet:public Object
{
	int _damage;
	float _speed;
	BULLET_TYPE _bulletType;
	int _count;
	Enemy *_targetEnemy;
	bool _hit;
	float _size;
public:
	Bullet(VECTOR direction, VECTOR translation,int damage,float speed,BULLET_TYPE bulletType,float size=0.3);

	virtual void Update(char input []);
	virtual void Draw();
	virtual bool GetExpired();
	
	void SetHit(bool hit);
	int GetDamage();
	float GetSpeed();
	virtual bool Collide(VECTOR translation, float radius);
};

bool Bullet_Erase(Bullet bullet);