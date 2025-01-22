#include "pch.h"
#include "MissilePattern.h"
#include "GuidedMissile.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"

MissilePattern::MissilePattern()
{

}

MissilePattern::~MissilePattern()
{
}

void MissilePattern::Update()
{
	if (_isUsingSkill == false) return;

	if (_prevShootTime + 0.1f < TIME)
	{
		_prevShootTime = TIME;
		_currentIdx++;

		XMVECTOR dir[2]{ {-1,-1}, {1,-1} };
		XMVECTOR pos = _owner->GetPos();
		pos += {0, -50};

		XMVECTOR curDir = dir[_currentIdx % 2];
		curDir = XMVector2Normalize(curDir);
		GuidedMissile* missile = new GuidedMissile();
		missile->SetPos(pos);
		missile->SetDir(curDir);

		GET_SINGLE(SceneManager)->GetCurrentScene()
			->AddObject(missile, LAYER::PROJECTILE);

		if (_currentIdx == 6)
			_isUsingSkill = false;
	}
}

void MissilePattern::UseSkill()
{
	_isUsingSkill = true;
	_currentIdx = 0;
	_prevShootTime = TIME;
}
