#pragma once

#include <DxLib.h>
#include <cmath>

class Object
{
protected:
	VECTOR _translation;
	VECTOR _direction;
public:
	Object(){}
	Object(VECTOR direction, VECTOR translation);

	virtual void Update(char input []) = 0;
	virtual void Draw() = 0;

	VECTOR GetTranslation();

	VECTOR GetDirection();

	virtual bool GetExpired() = 0;

	virtual bool Collide(VECTOR translation, float radius) = 0;
};