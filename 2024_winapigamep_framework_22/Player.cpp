#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Projectile.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "SpriteRenderer.h"
#include "PlayerHealthCompo.h"
#include "Action.h"
#include "SceneManager.h"
#include "AttackDirArrow.h"
#include "AttackRange.h"
#include "GameManager.h"
#include "SkillManager.h"
#include "PoolManager.h"
#include "SlashEffect.h"
#include "PlayerCast.h"
#include "DashSkill.h"

Player::Player()
{
	this->AddComponent<SpriteRenderer>();
	this->AddComponent<PlayerHealthCompo>();
	this->AddComponent<Collider>();

	_spriteRenderer = GetComponent<SpriteRenderer>();
	healthCompo = GetComponent<PlayerHealthCompo>();
	collider = GetComponent<Collider>();

	_playerCasts.push_back(new PlayerCast(30.f));
	_playerCasts.push_back(new PlayerCast);
	_playerCasts.push_back(new PlayerCast(-30.f));

	_spriteRenderer->SetTexture(L"Player", L"Texture\\Player.bmp");
	_spriteRenderer->isRotatable = false;
	collider->SetSize({ 25, 25 });

	//나중에 밸패하기
	SetSize({ 45, 45 });
	speed = 400;
	parryCoolTime = 0.87f;

	AttackDirArrow* arrow = new AttackDirArrow;
	arrow->SetParent(this);

	attackRange = new AttackRange;
	attackRange->SetParent(this);

	ADDOBJECT(attackRange, LAYER::DEFAULT);
	ADDOBJECT(arrow, LAYER::DEFAULT);

	for (auto playerCast : _playerCasts)
	{
		ADDOBJECT(playerCast, LAYER::PLAYERCAST);
	}


	GET_SINGLE(SkillManager)->player = this;
	GET_SINGLE(GameManager)->player = this;
	LOADSOUND(L"Parry", L"Sound\\Parry.wav", SOUND_CHANNEL::EFFECT0);
	LOADSOUND(L"Sword", L"Sound\\sword.wav", SOUND_CHANNEL::EFFECT1);

}
Player::~Player()
{
}

void Player::Update()
{
	XMVECTOR dir = {};
	if (GET_KEY(KEY_TYPE::W))
		dir += {0, -1};
	if (GET_KEY(KEY_TYPE::S))
		dir += {0, 1};
	if (GET_KEY(KEY_TYPE::A))
		dir += {-1, 0};
	if (GET_KEY(KEY_TYPE::D))
		dir += {1, 0};
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		if (TIMESCALE <= 0.01f) return;
		Parry();
	}

	bool isTrigger = false;

	for (auto playerCast : _playerCasts)
	{
		playerCast->SetPos(GetPos());
	
		if (XMVectorGetX(XMVector2LengthSq(dir)) > 0.1f)
			_lastDir = dir;
		playerCast->SetMoveDir(_lastDir);
		dir = XMVector2Normalize(dir);
	}
	for (auto playerCast : _playerCasts)
	{
		if (playerCast->IsCast())
		{
			isTrigger = true;
			break;
		}
	}

	if (isTrigger)
	{
		Move(dir * speed * fDT);
		lastPos = GetPos();
	}
	else
	{
		DashSkill* dashSkill = dynamic_cast<DashSkill*>(GET_SINGLE(SkillManager)->GetSkill(ESkillType::DashSkill));
		dashSkill->StopDash();
		SetPos(lastPos);
	}

	attackDir = ((XMVECTOR)GET_MOUSEPOS - GetPos());
	attackDir = XMVector2Normalize(attackDir);
	attackRange->SetDir(attackDir);
	Parrying();

	if (GET_KEYDOWN(KEY_TYPE::CTRL))
		healthCompo->ApplyDamage(55);

	_spriteRenderer->LookAt(attackDir);
}

void Player::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Player::Parry()
{
	if (isParrying == true) return;
	if (curParryTime < parryCoolTime)
	{
		return;
	}
	curParryTime = 0;
	AttackEvent.Invoke(NULL);

	{
		XMVECTOR effectPos = GetPos();
		effectPos += attackDir * 50.f;
		SlashEffect* slashEffect = static_cast<SlashEffect*>(POP(L"SlashEffect", effectPos));
		slashEffect->LookAt(attackDir);
	}

	isParrying = true;
}

void Player::Parrying()
{
	if (curParryTime < parryCoolTime)
	{
		curParryTime += fDT;
		ParryCoolTimeEvent.Invoke(curParryTime / parryCoolTime);
	}

	if (curParryTime > parryingTime || isParrying == false)
	{
		isParrying = false;
		return;
	}

	XMVECTOR vPos = GetPos();
	bool parried = false;
	vector<Object*> projectiles = FindObjects(LAYER::PROJECTILE);

	for (Object* projObj : projectiles)
	{
		XMVECTOR dist = projObj->GetPos();
		dist -= vPos;
		if (XMVectorGetX(XMVector2Length(dist)) > parryDist) continue;

		attackDir = XMVector2Normalize(attackDir);
		dist = XMVector2Normalize(dist);

		//반격 로직(총알이 어떻게 튕기는지)
		float rotation = acos(XMVectorGetX(XMVector2Dot(attackDir, dist))) * Rad2Deg;
		if (abs(rotation) < 45)
		{
			Projectile* proj = dynamic_cast<Projectile*>(projObj);
			if (proj == nullptr) continue;
			XMVECTOR dir = proj->GetOwner()->GetPos();
			dir -= proj->GetPos();
			dir = XMVector2Normalize(dir);
			proj->Parry(dir);
			parried = true;
		}
	}

	PLAY(L"Sword");

	if (parried)
		isParrying = false;
}

void Player::EnterCollision(Collider* _other)
{
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
}