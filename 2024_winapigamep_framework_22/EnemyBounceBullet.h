#pragma once
#include "Projectile.h"

class EnemyBounceBullet : public Projectile
{
public:
	EnemyBounceBullet();
	~EnemyBounceBullet() override;
	void Update() override;
	void Render(ComPtr<ID2D1RenderTarget> renderTarget) override;
private:
	int bounceCnt = 5;
	int remainBounce;

	// Projectile을(를) 통해 상속됨
	void OnPop() override;
	void OnPush() override;
};

