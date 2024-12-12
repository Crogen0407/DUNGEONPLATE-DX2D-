#pragma once
#include "Component.h"

class Object;

class AttackCompo : public Component
{
public:
	AttackCompo();
	virtual ~AttackCompo();
public:
	void TryFireBullet(Vec2 dir, float speed);
	void TryFireMissile(Vec2 dir);
	void TryFireBounceBullet(Vec2 dir);
	void TryFireRazer(float lifeTime);

protected:
	// Component��(��) ���� ��ӵ�
	void LateUpdate() override;
	void Render(HDC _hdc) override;
};

