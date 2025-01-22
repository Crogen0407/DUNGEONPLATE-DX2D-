#pragma once
#include "PoolableObject.h"
class Texture;
class Projectile : public PoolableObject
{
public:
	Projectile();
	virtual ~Projectile();
	void Update() abstract;
	void Render(HDC _hdc) abstract;
public:
	virtual void SetDir(XMVECTOR dir)
	{
		_dir = dir;
		_dir = XMVector2Normalize(_dir);
	}
	const XMVECTOR& GetDir() const
	{
		return _dir;
	}
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	void SetSpeed(float speed) { _speed = speed; }
	void SetOwner(Object* owner) { _owner = owner; }
	const Object* GetOwner() const { return _owner; }
	virtual void Parry(XMVECTOR dir);
	bool _hitEnemy = false;
protected:
	Object* _owner;
	wstring _poolName;
	XMVECTOR _dir = { 1.f, 1.f };
	Texture* _texture;
	float _speed = 500.f;
	int _damage;
public:
	virtual void OnPop() override;
	virtual void OnPush() override;
};

