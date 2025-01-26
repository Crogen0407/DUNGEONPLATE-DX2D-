#pragma once
#include "Object.h"
class SpriteRenderer;
class AttackRange :
    public Object
{
public:
    AttackRange();
    ~AttackRange() override;
public:
    void Update() override;
    void SetParent(Object* parent)
    {
        this->parent = parent;
    }
    void SetDir(XMVECTOR dir);
private:
    SpriteRenderer* _spriteRenderer;
    Object* parent;
};