#pragma once
#include "Component.h"
#include "ResourceManager.h"
#include "Geometry.h"

class VertexTextureData;

class Texture;
class SpriteRenderer :
    public Component
{
public:
    SpriteRenderer();
    ~SpriteRenderer() override;
private:
    Texture* texture;
public:
    void LateUpdate() override;
    void Render() override;
public:
    void SetTexture(std::wstring name, std::wstring path);
    void SetTexture(Texture* texture);
    void SetAngle(float angle, bool isDeg = false)
    {
        if (isDeg)
        {
            this->angle = angle * Deg2Rad;
            angle -= PI / 2;
        }
        else
            this->angle = angle;
    }
    void LookAt(const XMVECTOR& dir)
    {
        this->angle = std::atan2(XMVectorGetY(dir), XMVectorGetX(dir));
    }

public:
    bool enable = true;
    bool isRotatable = true;

private:
    float angle;


};

