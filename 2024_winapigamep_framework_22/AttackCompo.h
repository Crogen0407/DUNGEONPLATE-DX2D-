#pragma once
#include "Component.h"

class Object;

class AttackCompo : public Component
{
public:
	AttackCompo();
	virtual ~AttackCompo();
public:
	void TryFireBullet(XMVECTOR dir, float speed);
	void TryFireMissile(XMVECTOR dir);
	void TryFireBounceBullet(XMVECTOR dir);
	void TryFireRazer(float lifeTime);

protected:
	// Component을(를) 통해 상속됨
	void LateUpdate() override;
	void Render() override;
};

