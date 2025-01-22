#include "pch.h"
#include "EnemyBounceBullet.h"
#include "TimeManager.h"
#include "PoolManager.h"
#include "Collider.h"
#include "SpriteRenderer.h"

EnemyBounceBullet::EnemyBounceBullet()
{
	_damage = 10;
	_poolName = L"EnemyBounceBullet";
	_texture = LOADTEXTURE(L"EnemyBounceBullet", L"Texture\\EnemyBounceBullet.bmp");

	SetSize({ 20.f,20.f });
	AddComponent<SpriteRenderer>();
	AddComponent<Collider>();

	GetComponent<Collider>()->SetSize({ 20.f,20.f });
	GetComponent<SpriteRenderer>()->SetTexture(_texture);
}

EnemyBounceBullet::~EnemyBounceBullet()
{
}

void EnemyBounceBullet::Update()
{
	float vPosX = GetPosX();
	float vPosY = GetPosY();
	float vSizeX = GetSizeX();
	float vSizeY = GetSizeY();

	vPosX += XMVectorGetX(_dir) * _speed * fDT;
	vPosY += XMVectorGetY(_dir) * _speed * fDT;
	SetPos(GetPos());

	if (vPosX < vSizeX / 2 || vPosX > SCREEN_WIDTH - vSizeX / 2)
	{
		_dir += {-2, 0};
		_dir *= -XMVectorGetX(XMVector2Dot(_dir, { -1, 0 }));
		remainBounce--;
	}

	if (vPosY < vSizeY / 2 || vPosY > SCREEN_HEIGHT - vSizeY / 2)
	{
		_dir += {0, -2};
		_dir *= -XMVectorGetX(XMVector2Dot(_dir, { 0, -1 }));
		remainBounce--;
	}


	if (remainBounce <= 0)
		PUSH(_poolName, this);
}

void EnemyBounceBullet::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void EnemyBounceBullet::OnPop()
{
	_hitEnemy = false;
	remainBounce = bounceCnt;
}

void EnemyBounceBullet::OnPush()
{
}
