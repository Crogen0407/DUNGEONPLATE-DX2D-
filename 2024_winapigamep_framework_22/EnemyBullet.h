#pragma once
#include "Projectile.h"

class EnemyBullet : public Projectile
{
public:
	EnemyBullet();
	~EnemyBullet() override;
	void Update() override;

	// Projectile��(��) ���� ��ӵ�
	void OnPop() override;
	void OnPush() override;
};

