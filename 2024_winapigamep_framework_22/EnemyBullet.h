#pragma once
#include "Projectile.h"

class EnemyBullet : public Projectile
{
public:
	EnemyBullet();
	~EnemyBullet() override;
	void Update() override;
	void Render(ComPtr<ID2D1RenderTarget> renderTarget) override;

	// Projectile��(��) ���� ��ӵ�
	void OnPop() override;
	void OnPush() override;
};

