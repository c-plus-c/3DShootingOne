#pragma once

#include "Object.h"

#define VELOCITY 1
#define PITCHACCELBAND 0.0003
#define PITCHACCELBANDLIMIT 0.03

#define ROLLACCELBAND 0.005
#define ROLLACCELBANDLIMIT 0.04
#define ROLLBACK 8

#define YAWTIME 0.03

#define ROLLLIMIT (DX_PI/6)
#define PITCHLIMIT (DX_PI/5)

#define BRAKEINCREMENTATION 0.1
#define BRAKEMIN 1
#define BRAKEMAX 3

#define BOOSTINCREMENTATION -0.1
#define BOOSTMAX 1
#define BOOSTMIN 0.4

#define BOOST_AMMO_COST 0.6

#define BLINK_COUNT 60
#define DYING_COUNT 120

#define FIREBALL_INTERVAL 1
#define FIREBALL_RELOAD_INTERVAL 4

#define HORMING_AMMO_COST 30
#define FIREBALL_AMMO_COST 1

#define ACTIVE_HIGHEST 500
#define ACTIVE_LOWEST 40
#define ACTIVE_RADIUS 200


class Player : Object
{
	float _pitch;
	float _roll;
	float _yaw;

	float _rollAccelerator;
	float _pitchAccelerator;
	float _brakeVariable;

	bool _sideOut;

	int _count;

	void _manualMove(char buf []);
	void _autoMove();

public:
	Player(VECTOR translation,float pitch,float roll,float yaw);

	virtual void Update(char input []);
	virtual void Draw();
};