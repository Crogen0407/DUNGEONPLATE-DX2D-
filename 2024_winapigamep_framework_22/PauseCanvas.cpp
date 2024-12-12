#include "pch.h"
#include "PauseCanvas.h"
#include "Text.h"
#include "Image.h"
#include "ResourceManager.h"

PauseCanvas::PauseCanvas()
{
	SetName(L"PauseCanvas");

	//Background
	{
		Vec2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		Vec2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20 };
		Image* background = CreateUI<Image>(pos, size);
		background->texture = LOADTEXTURE(L"OnePoint", L"Texture\\OnePoint.bmp");
	}

	//TitleText
	{
		Vec2 size = {1000, 100};
		Vec2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -40 };
		Text* text = CreateUI<Text>(pos, size);
		text->SetText(L"�Ͻ� ����");
		text->LoadFont(L"PF��Ÿ����Ʈ Bold", 60, 72);
		text->SetPitchAndFamily(DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		text->SetColor(RGB(155, 188, 15));
	}

	//DescriptionText
	{
		Vec2 size = { 1000, 100 };
		Vec2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 +40};
		Text* text = CreateUI<Text>(pos, size);
		text->SetText(L"Esc�� ���� �ٽ� ����...");
		text->LoadFont(L"PF��Ÿ����Ʈ", 40, 51);
		text->SetPitchAndFamily(DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		text->SetColor(RGB(155, 188, 15));
	}
}

PauseCanvas::~PauseCanvas()
{
}

void PauseCanvas::Update()
{
}

void PauseCanvas::LateUpdate()
{
}

void PauseCanvas::Render(HDC hdc)
{
	Canvas::Render(hdc);
}
