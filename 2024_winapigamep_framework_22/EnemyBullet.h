#pragma once
#include "Projectile.h"

class EnemyBullet : public Projectile
{
public:
	EnemyBullet();
	~EnemyBullet() override;
	void Update() override;

	// Projectile을(를) 통해 상속됨
	void OnPop() override;
	void OnPush() override;
};

