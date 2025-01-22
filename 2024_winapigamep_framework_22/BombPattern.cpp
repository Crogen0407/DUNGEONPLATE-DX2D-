#include "pch.h"
#include "BombPattern.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "Player.h"
#include "EnemyBomb.h"
#include "PoolManager.h"

BombPattern::BombPattern()
{
	_player = GET_SINGLE(GameManager)->player;
}

BombPattern::~BombPattern()
{
}

void BombPattern::Update()
{
	if (_isUsingSkill == false) return;

	_curDelayTime += fDT;
	XMVECTOR playerDir =
	{

		_player->GetPosX() - _owner->GetPosX(),
		_player->GetPosY() - _owner->GetPosY()
	};

	if (_curDelayTime > _bombMaxCount)
	{
		_curDelayTime = 0.f;

		float angleRange = 120.f * Deg2Rad;
		int count = 10;
		for (int i = 0; i < count; i++)
		{
			float halfAngle = angleRange * ((float)i/count);

			XMVECTOR dir = playerDir;
			float finalAngle = halfAngle - angleRange / 2;
			dir = XMVectorSet(
					XMVectorGetX(dir) * cosf(finalAngle) - XMVectorGetY(dir) * sinf(finalAngle),
					XMVectorGetX(dir) * sinf(finalAngle) + XMVectorGetY(dir) * cosf(finalAngle), 0, 0);
			dir = XMVector2Normalize(dir);
			XMVECTOR pos = _owner->GetPos();
			pos += dir * 30;
			auto enemyBomb = static_cast<EnemyBomb*>(POP(L"EnemyBomb", pos));

			enemyBomb->SetMoveDirection(dir);
		}

		if (++_curBombMaxCount >= _bombMaxCount)
			_isUsingSkill = false;
	}
}

void BombPattern::UseSkill()
{
	_isUsingSkill = true;
	_curBombMaxCount = 0.f;
}
