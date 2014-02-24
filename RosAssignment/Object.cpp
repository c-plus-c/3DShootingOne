#include "Object.h"

Object::Object(VECTOR direction, VECTOR translation)
{
	_translation = translation;
	_direction = direction;
}

VECTOR Object::GetTranslation()
{
	return _translation;
}

VECTOR Object::GetDirection()
{
	return _direction;
}