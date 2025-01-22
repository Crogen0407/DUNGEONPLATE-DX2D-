#include "pch.h"
#include "GuidedMissile.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "TimeManager.h"
#include "Collider.h"
#include "ExplosionEffect.h"
#include "SceneManager.h"
#include "Scene.h"
#include "AttackCompo.h"
#include "HealthCompo.h"
#include "PoolManager.h"

GuidedMissile::GuidedMissile()
{
	_poolName = L"GuidedMissile";
	_damage = 7;
	SetSize({ 20,20 });
	_texture = LOADTEXTURE(L"EnemyMissile", L"Texture\\EnemyMissile.bmp");
	AddComponent<Collider>();
	AddComponent<SpriteRenderer>();
	AddComponent<AttackCompo>();

	GetComponent<Collider>()->SetSize({ 20.f,20.f });
	GetComponent<SpriteRenderer>()->SetTexture(_texture);

	target = FindObject(L"Player", LAYER::PLAYER);
	_speed = 400;

	/*_dir = target->GetPos();
	_dir -= GetPos();
	_dir.Normalize();
	_rotation = atan2f(_dir.y, _dir.x) * Rad2Deg;*/
}

GuidedMissile::~GuidedMissile()
{
}

void GuidedMissile::Update()
{
	XMVECTOR vPos = GetPos();
	XMVECTOR targetDir = (vPos * -1) + target->GetPos();
	targetDir = XMVector2Normalize(targetDir);

	_curTime += fDT;

	if (_isParry)
	{
		//_dir = targetDir;
	}
	else
	{
		XMVECTOR cross = XMVectorScale(XMVector3Cross(targetDir, _dir), 1);
		float crossScalar = XMVectorGetZ(cross);
		if (crossScalar > 0)
			_rotation -= 3.f * fDT;
		else if (crossScalar < 0)
			_rotation += 3.f * fDT;

		_dir = { cos(_rotation), sin(_rotation) };
	}

	if (_prevAttack + _attackDelay < TIME)
	{
		_prevAttack = TIME;

		XMVECTOR dir1 = { cos(_rotation + 150 * Deg2Rad), sin(_rotation + 150 * Deg2Rad) };
		XMVECTOR dir2 = { cos(_rotation - 150 * Deg2Rad), sin(_rotation - 150 * Deg2Rad) };

		GetComponent<AttackCompo>()->TryFireBullet(dir1, 200);
		GetComponent<AttackCompo>()->TryFireBullet(dir2, 200);
	}
	
	vPos = XMVectorAdd(_dir * _speed * fDT, vPos);
	SetPos(vPos);

	if (_lifetime < _curTime)
	{
		ExplosionEffect* explosion = new ExplosionEffect(L"ExplosionEffect02");
		explosion->SetPos(GetPos());
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(explosion, LAYER::SCREENEFFECT);

		PUSH(_poolName, this);
	}
}

void GuidedMissile::Render(HDC _hdc)
{
	ComponentRender(_hdc);
	GetComponent<SpriteRenderer>()->LookAt(_dir);
}

void GuidedMissile::SetDir(XMVECTOR dir)
{
	_dir = dir;
	_dir = XMVector2Normalize(_dir);
	_rotation = atan2f(XMVectorGetY(dir), XMVectorGetX(dir)) * Rad2Deg;
}

void GuidedMissile::Parry(XMVECTOR dir)
{
	XMVECTOR parriedDir = (_dir * -1) + GetPos();
	parriedDir = XMVector2Normalize(parriedDir);

	SetDir(parriedDir);
	_hitEnemy = true;
	_isParry = true;
}

void GuidedMissile::EnterCollision(Collider* _other)
{
	LAYER layer =
		GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayer(_other->GetOwner());

	if (layer == LAYER::PLAYER /*|| (layer == LAYER::ENEMY && _hitEnemy)*/)
	{
		HealthCompo* health = _other->GetOwner()->GetComponent<HealthCompo>();

		if (health != nullptr)
			health->ApplyDamage(_damage); 
		
		ExplosionEffect* explosion = new ExplosionEffect(L"ExplosionEffect02");
		explosion->SetPos(GetPos());
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(explosion, LAYER::SCREENEFFECT);

		Object* pOtherObj = _other->GetOwner();
		PUSH(_poolName, this);
	}
}

void GuidedMissile::OnPop()
{
	_hitEnemy = false;
	_isParry = false;
}

void GuidedMissile::OnPush()
{
	_curTime = 0.f;
}
