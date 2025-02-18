#include "pch.h"
#include "FadeObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "SceneManager.h"

FadeObject::FadeObject()
{
	AddComponent<SpriteRenderer>();
	AddComponent<Animator>();

	_spriteRenderer = GetComponent<SpriteRenderer>();
	_animator = GetComponent<Animator>();

	_fadeInTexture = LOADTEXTURE(L"ScreenTransition_FadeIn", L"Texture\\Effect\\ScreenTransition_FadeIn.png");
	_fadeOutTexture = LOADTEXTURE(L"ScreenTransition_FadeOut", L"Texture\\Effect\\ScreenTransition_FadeOut.png");

	_spriteRenderer->SetTexture(L"OnePoint", L"Texture\\OnePoint.png");
	_spriteRenderer->enable = false;
	_spriteRenderer->SetAngle(20.f, true);
	_animator->CreateAnimation(
		L"FadeIn",
		_fadeInTexture,
		{ 0, 0 }, { 256, 256 },
		{ 256, 0 }, 20, 0.05f, false);

	_animator->CreateAnimation(
		L"FadeOut",
		_fadeOutTexture,
		{ 0, 0 }, { 256, 256 },
		{ 256, 0 }, 20, 0.05f, false);
}

FadeObject::~FadeObject()
{
}

void FadeObject::Update()
{
	float max;

	if (SCREEN_WIDTH > SCREEN_HEIGHT) max = SCREEN_WIDTH;
	else max = SCREEN_HEIGHT;

	SetSize({ max, max });
	SetPos({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

}

void FadeObject::LateUpdate()
{
	Object::LateUpdate();
}

void FadeObject::FadeIn()
{
	_animator->PlayAnimation(L"FadeIn", false, 1);
}

void FadeObject::FadeOut()
{
	_animator->PlayAnimation(L"FadeOut", false, 1);
}