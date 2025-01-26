#include "pch.h"
#include "PlayerCast.h"
#include "Collider.h"

PlayerCast::PlayerCast()
{
	AddComponent<Collider>();
	_collider = GetComponent<Collider>();
	_collider->SetSize({ 5, 5 });
}

PlayerCast::PlayerCast(float startAngle)
{
	AddComponent<Collider>();
	_startAngle = startAngle;
	_collider = GetComponent<Collider>();
	_collider->SetSize({ 5, 5 });
}

PlayerCast::~PlayerCast()
{
}

void PlayerCast::Update()
{
}

void PlayerCast::LateUpdate()
{
	Object::LateUpdate();
}

void PlayerCast::EnterCollision(Collider* _other)
{    
	other = _other;
	_isCast = true;
}

void PlayerCast::StayCollision(Collider* _other)
{
	_isCast = true;
}

void PlayerCast::ExitCollision(Collider* _other)
{
	_isCast = false;
}

void PlayerCast::SetMoveDir(XMVECTOR dir)
{
	_dir = dir;
	float angle = (_startAngle * Deg2Rad);

	_dir = XMVectorSet(XMVectorGetX(_dir) * cosf(angle) - XMVectorGetY(_dir) * sinf(angle),
		XMVectorGetX(_dir) * sinf(angle) + XMVectorGetY(_dir) * cosf(angle), 0, 0);

	_collider->SetOffSetPos(_dir * _distance);
}
