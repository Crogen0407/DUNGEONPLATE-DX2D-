#pragma once
#include "Component.h"
class Collider : public Component
{
public:
    Collider();
    ~Collider();
public:
    // Component��(��) ���� ��ӵ�
    void LateUpdate() override;
    void Render() override;
public:
    void EnterCollision(Collider* _other); // �浹����
    void StayCollision(Collider* _other); // �浹��
    void ExitCollision(Collider* _other); // �浹����
    const UINT& GetID() const { return m_ID; }
public:
    void SetSize(XMVECTOR _vSize) { m_vSize = _vSize; }
    const XMVECTOR& GetSize() const { return m_vSize; }
    void SetOffSetPos(XMVECTOR _vOffsetPos)
    {
        m_vOffsetPos = _vOffsetPos;
    }
    const XMVECTOR& GetOffSetPos() const { return m_vOffsetPos; }
    const XMVECTOR& GetLatedUpatedPos() const
    {
        return m_vLatePos;
    }
private:
    bool m_showDebug = false;
    UINT m_ID; // �浹ü ���� ID��
    static UINT m_sNextID;

    XMVECTOR m_vSize; // �ݶ��̴� ũ��
    // Object�κ��� ������� ��ġ
    XMVECTOR m_vOffsetPos;
    // LateUpdate���� �� �����Ӹ��� ������Ʈ�κ��� ���Ǵ� ��ġ
    XMVECTOR m_vLatePos;

};

