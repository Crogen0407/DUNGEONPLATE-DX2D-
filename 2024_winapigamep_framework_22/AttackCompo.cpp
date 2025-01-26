#include "pch.h"
#include "TimeManager.h"
#include "AttackCompo.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Object.h"
#include "Scene.h"
#include "GuidedMissile.h"
#include "EnemyBullet.h"
#include "EnemyBounceBullet.h"
#include "Razer.h"
#include "PoolManager.h"
#include "PoolableObject.h"

AttackCompo::AttackCompo()
{
}

AttackCompo::~AttackCompo()
{
}

void AttackCompo::TryFireBullet(XMVECTOR dir, float speed)
{
	EnemyBullet* projectile 
		= dynamic_cast<EnemyBullet*>(POP(L"EnemyBullet", GetOwner()->GetPos()));
	projectile->SetOwner(GetOwner());
	projectile->SetDir(dir);
	projectile->SetSpeed(speed);
}

void AttackCompo::TryFireBounceBullet(XMVECTOR dir)
{
	EnemyBounceBullet* projectile
		= dynamic_cast<EnemyBounceBullet*>(POP(L"EnemyBounceBullet", GetOwner()->GetPos()));
	projectile->SetOwner(GetOwner());
	projectile->SetDir(dir);
	projectile->SetSpeed(700);
}

void AttackCompo::TryFireRazer(float lifeTime)
{
	Razer* razer = new Razer(lifeTime);
	razer->SetOwner(GetOwner());

	GET_SINGLE(SceneManager)->GetCurrentScene()
		->AddObject(razer, LAYER::PROJECTILE);
}

void AttackCompo::TryFireMissile(XMVECTOR dir)
{
	GuidedMissile* projectile
		= dynamic_cast<GuidedMissile*>(POP(L"GuidedMissile", GetOwner()->GetPos()));
	projectile->SetOwner(GetOwner());
	projectile->SetDir(dir);
}

void AttackCompo::LateUpdate()
{
}

void AttackCompo::Render()
{
}
