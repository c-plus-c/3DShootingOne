#pragma once

#include "Object.h"

#define VELOCITY 1.2
#define PITCHACCELBAND 0.0003
#define PITCHACCELBANDLIMIT 0.02

#define ROLLACCELBAND 0.005
#define ROLLACCELBANDLIMIT 0.04
#define ROLLBACK 8

#define YAWTIME 0.03

#define ROLLLIMIT (DX_PI/6)
#define PITCHLIMIT (DX_PI/5)

#define BRAKEINCREMENTATION 0.1
#define BRAKEMIN 1
#define BRAKEMAX 3

#define BLINK_COUNT 60
#define DYING_COUNT 120

#define FIREBALL_INTERVAL 1
#define FIREBALL_RELOAD_INTERVAL 4

#define HORMING_AMMO_COST 30
#define FIREBALL_AMMO_COST 1

#define ACTIVE_HIGHEST 500
#define ACTIVE_LOWEST 40
#define ACTIVE_RADIUS 300

#define SHOT_HANDI 150
#define HORMINGSHOT_HANDI (SHOT_HANDI*3)
#define INCIVIBLE_TERM 150
#define FIRST_LIFE 1

enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_INCIVIBLE,
	PLAYER_STATE_DYING,
	PLAYER_STATE_DIE
};

class Player : public Object
{
	int _life;

	float _pitch;
	float _roll;
	float _yaw;

	float _rollAccelerator;
	float _pitchAccelerator;
	float _brakeVariable;

	bool _sideOut;

	int _count;

	int _shotLockCount;

	void _manualMove(char buf []);
	void _autoMove();

	PLAYER_STATE _playerState;
	int _incivibleCount;
	

public:
	Player(){}
	Player(VECTOR translation,float pitch,float roll,float yaw);

	virtual void Update(char input []);
	virtual void Draw();
	virtual bool GetExpired();
	virtual bool Collide(VECTOR translation, float radius);

	int GetShotLockCount();
	int GetLife();

	void Damage(int damage);
};