#include "pch.h"
#include "HealthCompo.h"
#include "Object.h"
#include "ResourceManager.h"
#include "PoolManager.h"

HealthCompo::HealthCompo() :
	hp(100),
	maxHp(100)
{

	GET_SINGLE(ResourceManager)->LoadSound(L"Hit", L"Sound\\Hit.wav", SOUND_CHANNEL::EFFECT2);
	GET_SINGLE(ResourceManager)->LoadSound(L"Heal", L"Sound\\Heal.wav", SOUND_CHANNEL::EFFECT2);
}

HealthCompo::~HealthCompo()
{
}

void HealthCompo::ApplyDamage(int value)
{
	Vec2 pos = GetOwner()->GetPos();
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
	Vec2 pos = GetOwner()->GetPos();
	POP(L"HealEffect", pos);
	GET_SINGLE(ResourceManager)->Play(L"Heal");
	SetHp(hp + value);
}

void HealthCompo::LateUpdate()
{
	
}

void HealthCompo::Render(ComPtr<ID2D1RenderTarget> renderTarget)
{
	if (hpBarActive == false) return;

	Vec2 pos = GetOwner()->GetPos();
	pos.y += offsetY;
	Vec2 size = { GetOwner()->GetSize().x, 12.f};

	// TODO
	if (_fillBrush == nullptr)
	{
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(48, 98, 48), _backBrush.GetAddressOf());
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(139, 172, 15), _fillBrush.GetAddressOf());
	}

	//Back
	renderTarget->DrawRectangle(D2D1::RectF(
		pos.x - size.x / 2, 
		pos.y - size.y / 2, 
		pos.x + size.x / 2, 
		pos.y + size.y / 2), 
		_backBrush.Get());

	//Fill
	renderTarget->DrawRectangle(D2D1::RectF(
		pos.x - size.x / 2,
		pos.y - size.y / 2, 
		pos.x + (size.x / 2) * (std::clamp(hp / maxHp, 0.f, 1.f)),
		pos.y + size.y / 2), 
		_fillBrush.Get());
}
