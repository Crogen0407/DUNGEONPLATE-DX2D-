#include "pch.h"
#include "BounceBulletPattern.h"
#include "TimeManager.h"
#include "AttackCompo.h"
#include "Object.h"

BounceBulletPattern::BounceBulletPattern()
{
}

BounceBulletPattern::~BounceBulletPattern()
{
}

void BounceBulletPattern::Update()
{
	if (_isUsingSkill == false) return;
	
	if (_prevShootTime + _bulletDelay < TIME)
	{
		_prevShootTime = TIME;

		float rotation = rand() % 360;

		XMVECTOR dir = { cos(rotation * Deg2Rad), sin(rotation * Deg2Rad) };
		dir = XMVector2Normalize(dir);

		_owner->GetComponent<AttackCompo>()->TryFireBounceBullet(dir);
		_owner->GetComponent<AttackCompo>()->TryFireBounceBullet(dir * -1);

		if (++_curBullet >= _bulletCnt)
			_isUsingSkill = false;
	}
}

void BounceBulletPattern::UseSkill()
{
	_isUsingSkill = true;
	_prevShootTime = TIME;
	_curBullet = 0;
}
