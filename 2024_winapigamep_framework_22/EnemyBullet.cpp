#include "pch.h"
#include "EnemyBullet.h"
#include "ResourceManager.h"
#include "PoolManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Texture.h"
#include "SpriteRenderer.h"

EnemyBullet::EnemyBullet()
{
	_damage = 10;
	_poolName = L"EnemyBullet";
	_texture = LOADTEXTURE(L"EnemyBullet", L"Texture\\EnemyBullet.bmp");
	AddComponent<SpriteRenderer>();
	AddComponent<Collider>();
	SetSize({ 20,20 });

	GetComponent<Collider>()->SetSize({ 20.f,20.f });
	GetComponent<SpriteRenderer>()->SetTexture(_texture);
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update()
{
	XMVECTOR vPos = GetPos();
	XMVECTOR vSize = GetSize();
	_dir = XMVector2Normalize(_dir);

	vPos += {XMVectorGetX(_dir)* _speed* fDT, XMVectorGetY(_dir)* _speed* fDT};

	SetPos(vPos);
	if (XMVectorGetY(vPos) < -XMVectorGetY(vSize) / 2 || XMVectorGetX(vPos) < -XMVectorGetX(vSize) / 2
		|| XMVectorGetY(vPos) > SCREEN_HEIGHT + XMVectorGetY(vSize) || XMVectorGetX(vPos) > SCREEN_WIDTH)
	{
		PUSH(_poolName, this);
	}
}

void EnemyBullet::OnPop()
{
	_hitEnemy = false;
	_speed = 0;
}

void EnemyBullet::OnPush()
{
}
