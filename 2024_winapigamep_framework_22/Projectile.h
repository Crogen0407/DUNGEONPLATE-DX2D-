#pragma once
#include "PoolableObject.h"
#include "AttackCompo.h"
class Texture;
class AttackCompo;
class Projectile : public PoolableObject
{
	friend AttackCompo;
public:
	Projectile();
	virtual ~Projectile();
	void Update() abstract;
public:
	virtual void SetDir(Vec2 dir)
	{
		_dir = dir;
		_dir.Normalize();
	}
	Vec2 GetDir()
	{
		return _dir;
	}
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	void SetSpeed(float speed) { _speed = speed; }
	virtual void Parry();
	bool _hitEnemy = false;
protected:
	//float m_dir;
	wstring _poolName;
	Vec2 _dir;
	Texture* _texture;
	float _speed = 500.f;
	int _damage;
public:
	virtual void OnPop() override;
	virtual void OnPush() override;
};

