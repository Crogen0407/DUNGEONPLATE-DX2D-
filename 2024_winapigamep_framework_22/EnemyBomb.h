#pragma once
#include "Projectile.h"
class EnemyBomb :
    public Projectile
{
public:
    EnemyBomb();
    ~EnemyBomb() override;
public:
    void Update() override;
    void Parry(XMVECTOR pos) override;
    void OnPush()override;
public:
    void SetMoveDirection(XMVECTOR dir)
    {
        _dir = dir;
    }
};

