#include "pch.h"
#include "AttackRange.h"
#include "SpriteRenderer.h"
#include "TimeManager.h"

AttackRange::AttackRange()
{
	AddComponent<SpriteRenderer>();
	_spriteRenderer = GetComponent<SpriteRenderer>();
	_spriteRenderer->SetTexture(L"AttackRange", L"Texture\\AttackRange.bmp");
	_spriteRenderer->enable = true;
	SetSize({ 110, 110 });
}

AttackRange::~AttackRange()
{
}

void AttackRange::Update()
{
	if (TIMESCALE <= 0.1f) return;
	SetPos(parent->GetPos());
}

void AttackRange::SetDir(XMVECTOR dir)
{
	if (TIMESCALE <= 0.1f) return;
	_spriteRenderer->LookAt(dir);
}
