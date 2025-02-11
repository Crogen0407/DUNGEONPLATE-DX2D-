#pragma once
#include "Enemy.h"
class Texture;
class EnemyC : public Enemy
{
public:
	EnemyC();
	~EnemyC() override;

	// Enemy��(��) ���� ��ӵ�
	void Update() override;
	void OnDie() override;
private:
	float _shootDelay = 1;
	float _prevShootTime = 0;
	Texture* _texture;
};

