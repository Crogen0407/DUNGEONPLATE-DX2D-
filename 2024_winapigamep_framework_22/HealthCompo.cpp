#include "pch.h"
#include "HealthCompo.h"
#include "Object.h"
#include "ResourceManager.h"
#include "PoolManager.h"

HealthCompo::HealthCompo() :
	hp(100),
	maxHp(100),
	fillBrush(NULL),
	backBrush(NULL)
{
	fillBrush = ::CreateSolidBrush(RGB(139, 172, 15));
	backBrush = ::CreateSolidBrush(RGB(48, 98, 48));
	GET_SINGLE(ResourceManager)->LoadSound(L"Hit", L"Sound\\Hit.wav", SOUND_CHANNEL::EFFECT2);
	GET_SINGLE(ResourceManager)->LoadSound(L"Heal", L"Sound\\Heal.wav", SOUND_CHANNEL::EFFECT2);
}

HealthCompo::~HealthCompo()
{
	DeleteObject(fillBrush);
	DeleteObject(backBrush);
}

void HealthCompo::ApplyDamage(int value)
{
	XMVECTOR pos = GetOwner()->GetPos();
	GET_SINGLE(ResourceManager)->Play(L"Hit");
	POP(L"HitEffect", pos);
	SetHp(hp - value);
	DamagedEvent.Invoke(NULL);
	if (hp <= 0)
	{
		OnDie();
	}
}

void HealthCompo::ApplyHeal(int value)
{
	XMVECTOR pos = GetOwner()->GetPos();
	POP(L"HealEffect", pos);
	GET_SINGLE(ResourceManager)->Play(L"Heal");
	SetHp(hp + value);
}

void HealthCompo::LateUpdate()
{
	
}

void HealthCompo::Render()
{
	if (hpBarActive == false) return;

	XMVECTOR pos = GetOwner()->GetPos();
	pos += {0, offsetY};
	XMVECTOR size = { GetOwner()->GetSizeX(), 12.f};

	//Back
	//HBRUSH oldBrush = static_cast<HBRUSH>(::SelectObject(hdc, backBrush));
	//::Rectangle(hdc,
	//	XMVectorGetX(pos) - XMVectorGetX(size) / 2,
	//	XMVectorGetY(pos) - XMVectorGetY(size) / 2,
	//	XMVectorGetX(pos) + XMVectorGetX(size) / 2,
	//	XMVectorGetY(pos) + XMVectorGetY(size) / 2);

	////Fill
	//static_cast<HBRUSH>(::SelectObject(hdc, fillBrush));

	//::Rectangle(hdc,
	//	XMVectorGetX(pos) - XMVectorGetX(size) / 2,
	//	XMVectorGetY(pos) - XMVectorGetY(size) / 2,
	//	XMVectorGetX(pos) + (XMVectorGetX(size) / 2)*(std::clamp(hp / maxHp, 0.f, 1.f)*2-1),
	//	XMVectorGetY(pos) + XMVectorGetY(size) / 2);

	//::SelectObject(hdc, oldBrush);
}
