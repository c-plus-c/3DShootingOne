#include "Bullet.h"

Bullet::Bullet(VECTOR direction, VECTOR translation, int damage, float speed,  bool horming)
:Object(direction,translation)
{
	_damage = damage;
	_speed = speed;
	_horming = horming;
}

void Bullet::Update(char input[])
{

	_translation = VAdd(_translation, VScale(_direction, _speed));
}

void Bullet::Draw()
{

}

int Bullet::GetDamage()
{
	return _damage;
}

float Bullet::GetSpeed()
{
	return _speed;
}