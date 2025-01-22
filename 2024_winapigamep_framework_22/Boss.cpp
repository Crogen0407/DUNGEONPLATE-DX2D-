#include "pch.h"
#include "Boss.h"
#include "TimeManager.h"
#include "MissilePattern.h"
#include "HealthCompo.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "Texture.h"
#include "EnemyPatternA.h"
#include "AttackCompo.h"
#include "RazerPattern.h"
#include "BounceBulletPattern.h"
#include "EventManager.h"
#include "Movement.h"
#include "BombPattern.h"

Boss::Boss() : _currentSkill{ nullptr }
{
	SetSize({ 100,100 });
	texture = LOADTEXTURE(L"Boss", L"Texture\\Enemy03.bmp");
	_target = FindObject(L"Player", LAYER::PLAYER);
	XMVECTOR texSize = { (int)texture->GetWidth() / 6, (int)texture->GetHeight() };
	AddComponent< Collider>();
	AddComponent<Animator>();
	AddComponent<AttackCompo>();
	AddComponent<Movement>();

	GetComponent<Collider>()->SetSize({ 100,100 });
	GetComponent<HealthCompo>()->SetOffsetY(50);
	GetComponent<Animator>()->CreateAnimation(L"Boss", texture, { 0,0 }, texSize, { XMVectorGetX(texSize), 0 }, 6, 0.2f, false);
	GetComponent<Animator>()->PlayAnimation(L"Boss", true, 100);
	GetComponent<HealthCompo>()->SetHp(425, 425);

	_prevSkillTime = TIME;
	MissilePattern* mSkill = new MissilePattern();
	mSkill->SetOwner(this);
	EnemyPatternA* paternA = new EnemyPatternA();
	paternA->SetOwner(this);
	RazerPatern* razerSkill = new RazerPatern();
	razerSkill->SetOwner(this);
	BounceBulletPattern* bounceBulletSkill = new BounceBulletPattern();
	bounceBulletSkill->SetOwner(this);
	BombPattern* bombPattern = new BombPattern();
	bombPattern->SetOwner(this);

	_prevDash = TIME;
	_skills.push_back(mSkill);
	_skills.push_back(paternA);
	_skills.push_back(razerSkill);
	_skills.push_back(bounceBulletSkill);
	_skills.push_back(bombPattern);
}

Boss::~Boss()
{
	//스킬을 new로 할당해줬기 때문에 사라질 때 함께 사라지는
	for (auto skill : _skills)
		delete(skill);
}

void Boss::Update()
{
	if (_isDead)
	{
		XMVECTOR vSize = GetSize();
		XMVECTOR curPos = GetPos();
		curPos += _knockDir * 500 * fDT;
		_rotation += 420 * fDT;

		SetPos(curPos);
		//GetComponent<SpriteRenderer>()->SetAngle(_rotation, true);

		if (XMVectorGetX(curPos) < -XMVectorGetX(vSize) / 2 || XMVectorGetX(curPos) > SCREEN_WIDTH + XMVectorGetX(vSize) / 2
			|| XMVectorGetY(curPos) < -XMVectorGetY(vSize) / 2 || XMVectorGetY(curPos) > SCREEN_HEIGHT + XMVectorGetY(vSize) / 2)
		{
			GET_SINGLE(EventManager)->DeleteObject(this);
		}
		return;
	}

	if (_currentSkill != nullptr)
	{
		_currentSkill->Update();

		if (_currentSkill->IsUsingSkill() == false)
			_currentSkill = nullptr;
	}
	else
	{
		if (_prevSkillTime + _skillCoolTime < TIME)
		{
			_prevSkillTime = TIME;

			int idx = rand() % _skills.size();
			_skills[idx]->UseSkill();
			_currentSkill = _skills[idx];
		}
	}

	if (_prevDash + _dashDelay < TIME)
	{
		_prevDash = TIME;

		XMVECTOR dashDir = { rand() % 2 == 0 ? 1 : -1, 0 };
		if (GetPosX() < 100) dashDir = { 1,0 };
		else if (GetPosX() > SCREEN_WIDTH - 100) dashDir = { -1,0 };

		GetComponent<Movement>()->Dash(dashDir, 1000.f, 0.1f);
	}
}

void Boss::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}
