#include "pch.h"
#include "Movement.h"
#include "TimeManager.h"
#include "Object.h"

Movement::Movement()
{
}

Movement::~Movement()
{
}

void Movement::Move(XMVECTOR dir)
{
	if (isDashing) return;

	XMVECTOR position = GetOwner()->GetPos();
	position += dir;

	GetOwner()->SetPos(position);
}

void Movement::Dash(XMVECTOR dir, float speed, float time)
{
	dashStartTime = TIME;
	dashSpeed = speed;
	isDashing = true;
	dashTime = time;
	dashDir = dir;
	dashDir = XMVector2Normalize(dashDir);
}

void Movement::LateUpdate()
{
	if (isDashing)
	{
		XMVECTOR position = GetOwner()->GetPos();
		XMVECTOR size = GetOwner()->GetSize();
		position += dashDir * dashSpeed * fDT;

		if (dashStartTime + dashTime < TIME || XMVectorGetX(position) < (XMVectorGetX(size) / 2) || XMVectorGetX(position)  > SCREEN_WIDTH - (XMVectorGetX(size) / 2)
			|| XMVectorGetY(position) < (XMVectorGetY(size) / 2) || XMVectorGetY(position)  > SCREEN_WIDTH - (XMVectorGetY(size) / 2))
			isDashing = false;


		GetOwner()->SetPos(position);
	}
}

void Movement::Render(HDC _hdc)
{
}
