#include "pch.h"
#include "EnemyBomb.h"
#include "TimeManager.h"
#include "Collider.h"
#include "SpriteRenderer.h"
#include "PoolManager.h"

EnemyBomb::EnemyBomb()
{
	SetSize({ 50, 50 });
	AddComponent<Collider>();
	AddComponent<SpriteRenderer>();

	Collider* collider = GetComponent<Collider>();
	SpriteRenderer* spriteRenderer = GetComponent<SpriteRenderer>();

	collider->SetSize(GetSize());
	spriteRenderer->SetTexture(L"EnemyBomb", L"Texture\\EnemyBomb.bmp");
	spriteRenderer->isRotatable = false;
	_poolName = L"EnemyBomb";
	_speed = 300.f;
	_damage = 100.f;
}

EnemyBomb::~EnemyBomb()
{
}

void EnemyBomb::Update()
{
	AddPos(_dir * _speed * fDT);

	float posX = GetPosX();
	float posY = GetPosY();

	if (posY < -posY / 2 || posX < -posX / 2
		|| posY > SCREEN_HEIGHT + posY || posX > SCREEN_WIDTH)
	{
		PUSH(_poolName, this);
	}
}

void EnemyBomb::Parry(XMVECTOR pos)
{
	XMVECTOR dir = (pos * -1) + GetPos();
	dir = XMVector2Normalize(dir);

	_damage = 10.f;
	SetSpeed(_speed * 6.f);
	SetDir(GetDir() * -1);
	POP(L"ParrySparkEffect", GetPos());
	GET_SINGLE(ResourceManager)->Play(L"Parry");
	_hitEnemy = true;
}

void EnemyBomb::OnPush()
{
	_hitEnemy = false;
	_damage = 100.f;
	_speed = 300.f;
}
