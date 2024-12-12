#pragma once
#include "Projectile.h"

class EnemyBullet : public Projectile
{
public:
	EnemyBullet();
	~EnemyBullet() override;
	void Update() override;
	void Render(HDC _hdc) override;

	// Projectile��(��) ���� ��ӵ�
	void OnPop() override;
	void OnPush() override;
};

