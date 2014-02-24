#include "Player.h"
#include "ResorceHandles.h"
#include "ObjectField.h"

Player::Player(VECTOR translation, float pitch, float roll, float yaw)
:Object(VGet(0,0,0),translation)
{
	_pitch = pitch;
	_roll = roll;
	_yaw = yaw;

	_rollAccelerator = 0;
	_pitchAccelerator = 0;
	_brakeVariable = 1;

	_sideOut = false;
	_count = 0;

	_shotLockCount = SHOT_HANDI + 1;

	SetCameraNearFar(0.1, 10000);
}

void Player::_manualMove(char buf [])
{
	if (buf[KEY_INPUT_RIGHT] == 1){ //���ɐ���
		if (_rollAccelerator>0) _rollAccelerator = 0;
		_rollAccelerator -= ROLLACCELBAND;
		if (_rollAccelerator<-ROLLACCELBANDLIMIT) _rollAccelerator = -ROLLACCELBANDLIMIT;
		_roll += _rollAccelerator;
		if (_roll<-ROLLLIMIT){
			_roll = -ROLLLIMIT;
			_rollAccelerator = 0;
		}
		_yaw -= _roll*YAWTIME;
	}
	else if (buf[KEY_INPUT_LEFT] == 1){ //�E�ɐ���

		if (_rollAccelerator<0) _rollAccelerator = 0;
		_rollAccelerator += ROLLACCELBAND;
		if (_rollAccelerator>ROLLACCELBANDLIMIT) _rollAccelerator = ROLLACCELBANDLIMIT;
		_roll += _rollAccelerator;
		if (_roll>ROLLLIMIT){
			_roll = ROLLLIMIT;
			_rollAccelerator = 0;
		}
		_yaw -= _roll*YAWTIME;

	}
	else{ //�����������
		if (_roll<0)
		{
			_rollAccelerator += ROLLACCELBAND*ROLLBACK;
			if (_rollAccelerator>ROLLACCELBANDLIMIT*ROLLBACK) _rollAccelerator = ROLLACCELBANDLIMIT*ROLLBACK;
			_roll += _rollAccelerator;
			if (_roll<-ROLLLIMIT) _roll = -ROLLLIMIT;
			else if (_roll >= 0){
				_roll = 0;
				_rollAccelerator = 0;
			}
		}
		else if (_roll>0){
			_rollAccelerator -= ROLLACCELBAND*ROLLBACK;
			if (_rollAccelerator<-ROLLACCELBANDLIMIT*ROLLBACK) _rollAccelerator = -ROLLACCELBANDLIMIT*ROLLBACK;
			_roll += _rollAccelerator;
			if (_roll>ROLLLIMIT) _roll = ROLLLIMIT;
			else if (_roll <= 0){
				_roll = 0;
				_rollAccelerator = 0;
			}
		}
		else{
			_rollAccelerator = 0;
		}
		_yaw -= _roll*YAWTIME;
	}

	if (buf[KEY_INPUT_UP] == 1){ //�㏸
		if (_pitchAccelerator>0) _pitchAccelerator = 0;
		_pitchAccelerator -= PITCHACCELBAND;
		if (_pitchAccelerator<-PITCHACCELBANDLIMIT) _pitchAccelerator = -PITCHACCELBANDLIMIT;
		_pitch += _pitchAccelerator;
		if (_pitch<0)
		{
			_pitch += 2 * DX_PI;
		}
	}
	else if (buf[KEY_INPUT_DOWN] == 1){ //���~
		if (_pitchAccelerator<0) _pitchAccelerator = 0;
		_pitchAccelerator += PITCHACCELBAND;
		if (_pitchAccelerator>PITCHACCELBANDLIMIT) _pitchAccelerator = PITCHACCELBANDLIMIT;
		_pitch += _pitchAccelerator;
		if (_pitch>2 * DX_PI){
			_pitch -= 2 * DX_PI;
		}
	}
	else{
		_pitchAccelerator = 0;
	}

	//�u���[�L
	if (buf[KEY_INPUT_X] == 1)
	{
		_brakeVariable += BRAKEINCREMENTATION;
		_brakeVariable = min(BRAKEMAX, _brakeVariable);
	}
	else{
		_brakeVariable -= BRAKEINCREMENTATION;
		_brakeVariable = max(BRAKEMIN, _brakeVariable);
	}

	if (buf[KEY_INPUT_Z] == 1&&_shotLockCount>SHOT_HANDI)
	{
		ObjectField::getObjectField().PlayerBullet.push_back(Bullet(_direction, _translation, 1, 3, BULLET_TYPE_PLAYER_HORMING));
		_shotLockCount = 0;
	}
}

void Player::_autoMove()
{
	_yaw += 0.02;
}

void Player::Update(char input[])
{
	float cp, sp, cb, sb, ch, sh;
	float ty, tz;
	float nx, ny, nz;


	if (_sideOut == 1)
	{
		_autoMove();
	}
	else
	{
		_manualMove(input);
	}


	//�s�b�`���[�����[�p���玩�@�̕����x�N�g�����Z�o
	ch = cos(_yaw);
	sh = sin(_yaw);
	cp = cos(_pitch);
	sp = sin(_pitch);

	cb = 1;
	sb = 0;

	tz = -1;

	_direction.x = (sh*cp)*tz;
	_direction.y = -sp*tz;
	_direction.z = (ch*cp)*tz;

	//�ړ�
	_translation.x += _direction.x*VELOCITY / _brakeVariable;
	_translation.y += _direction.y*VELOCITY / _brakeVariable;
	_translation.z += _direction.z*VELOCITY / _brakeVariable;

	_sideOut = (_translation.x*_translation.x + _translation.z*_translation.z >= ACTIVE_RADIUS*ACTIVE_RADIUS) ? 1 : 0;

	if (_translation.y <= ACTIVE_LOWEST) _translation.y = ACTIVE_LOWEST;
	else if (_translation.y >= ACTIVE_HIGHEST) _translation.y = ACTIVE_HIGHEST;

	//�J�����ʒu�̌v�Z
	float fovy, f, cr, p1, p2;
	VECTOR c;
	VECTOR t;
	VECTOR u;
	ty = 1;
	nx = (-ch*sb + sh*sp*cb)*ty;
	ny = (cb*cp)*ty;
	nz = (sb*sh + ch*sp*cb)*ty;
	c.x = _translation.x - (10 + 3 / _brakeVariable)*_direction.x + 1.5*nx;
	c.y = _translation.y - (10 + 3 / _brakeVariable)*_direction.y + 1.5*ny;
	c.z = _translation.z - (10 + 3 / _brakeVariable)*_direction.z + 1.5*nz;

	t.x = _translation.x + nx;
	t.y = _translation.y + ny;
	t.z = _translation.z + nz;

	u.x = nx;
	u.y = ny;
	u.z = nz;

	cr = _roll*(PITCHLIMIT / ROLLLIMIT);

	p1 = 2 * DX_PI - _pitch;
	p2 = _pitch;

	p1 /= 1.5;
	p2 /= 1.5;

	f = abs(cr)*25.0 / DX_PI;
	fovy = 45.0 + f;

	SetupCamera_Perspective(fovy * DX_PI_F / 180.0f);
	SetCameraPositionAndTargetAndUpVec(c, t, u);
	//SetCameraPositionAndTargetAndUpVec(VGet(10, 10, 10), _translation, VGet(0, 1, 0));

	++_count;
	++_shotLockCount;
}


void Player::Draw()
{
	SetUseLighting(FALSE);
	//SetUseLighting(TRUE);

	MATRIX matrix;
	matrix = MGetRotAxis(VGet(1, 0, 0), _pitch);
	matrix = MMult(matrix, MGetRotAxis(VGet(0, 1, 0), _yaw));
	matrix = MMult(matrix, MGetRotAxis(_direction, _roll));
	matrix = MMult(matrix, MGetTranslate(_translation));

	MV1SetMatrix(ResourceHandles::getResourceHandles().PlayerHandle, matrix);

	MV1DrawModel(ResourceHandles::getResourceHandles().PlayerHandle);
}

bool Player::GetExpired()
{
	return false;
}

bool Player::Collide(VECTOR translation, float radius)
{
	return false;
}