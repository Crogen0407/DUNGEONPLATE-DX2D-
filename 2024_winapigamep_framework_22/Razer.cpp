#include "pch.h"
#include "Razer.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Collider.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "HealthCompo.h"

Razer::Razer(float lifeTime)
{
	_damage = 10;
	SetSize({ 0,0 });
	_lifeTime = lifeTime;
	_startLifeTime = TIME;
	_texture = LOADTEXTURE(L"Razer", L"Texture\\Razer.bmp");

	AddComponent<Collider>();
	GetComponent<Collider>()->SetSize(GetSize());
}

Razer::~Razer()
{
}

void Razer::Update()
{
	if (_startLifeTime + _lifeTime < TIME)
		GET_SINGLE(EventManager)->DeleteObject(this);

	XMVECTOR vPos = _owner->GetPos();
	XMVECTOR vSize = GetSize();

	vSize = XMVectorSetX(vSize, 80.f + (sinf(TIME * 50) * 0.5f + 0.5f) * 20.f);

	if (XMVectorGetY(vSize) <= _targetSize)
		vSize = { XMVectorGetX(vSize), XMVectorGetY(vSize) + (1000 * fDT) };

	vPos = { XMVectorGetX(vPos), XMVectorGetY(vPos) + 50 + XMVectorGetY(vSize) / 2 };// XMVECTOR(0, 1)* (vSize.y * 2);
	GetComponent<Collider>()->SetSize(vSize);
	SetSize(vSize);
	SetPos(vPos);
}

void Razer::Render(std::shared_ptr<Pipeline> pipeline)
{
	Object::Render(pipeline);
	//ComponentRender();
	/*XMVECTOR vPos = GetPos();
	XMVECTOR vSize = GetSize();

	int width = _texture->GetWidth();
	int height = _texture->GetHeight();
	::TransparentBlt(_hdc
		, (int)(XMVectorGetX(vPos) - XMVectorGetX(vSize) / 2)
		, (int)(XMVectorGetY(vPos) - XMVectorGetY(vSize) / 2)
		, XMVectorGetX(vSize), XMVectorGetY(vSize),
		_texture->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));*/
}

void Razer::EnterCollision(Collider* _other)
{
}

void Razer::StayCollision(Collider* _other)
{

	if (_prevAttackTime + _attackDelay < TIME)
	{
		_prevAttackTime = TIME;
		LAYER layer =
			GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayer(_other->GetOwner());

		if (layer == LAYER::PLAYER)
		{
			HealthCompo* health = _other->GetOwner()->GetComponent<HealthCompo>();

			if (health != nullptr)
				health->ApplyDamage(_damage);
		}
	}
}
