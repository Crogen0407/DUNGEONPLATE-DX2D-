#include "pch.h"
#include "PauseCanvas.h"
#include "Text.h"
#include "Picture.h"
#include "ResourceManager.h"

PauseCanvas::PauseCanvas()
{
	SetName(L"PauseCanvas");

	//Background
	{
		XMVECTOR size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		XMVECTOR pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20 };
		Picture* background = CreateUI<Picture>(pos, size);
		background->texture = LOADTEXTURE(L"OnePoint", L"Texture\\OnePoint.bmp");
	}

	//TitleText
	{
		XMVECTOR size = {1000, 100};
		XMVECTOR pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -40 };
		Text* text = CreateUI<Text>(pos, size);
		text->SetText(L"일시 정지");
		text->LoadFont(L"PF스타더스트 Bold", 60, 72);
		text->SetPitchAndFamily(DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		text->SetColor(RGB(155, 188, 15));
	}

	//DescriptionText
	{
		XMVECTOR size = { 1000, 100 };
		XMVECTOR pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 +40};
		Text* text = CreateUI<Text>(pos, size);
		text->SetText(L"Esc를 눌러 다시 시작...");
		text->LoadFont(L"PF스타더스트", 40, 51);
		text->SetPitchAndFamily(DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		text->SetColor(RGB(155, 188, 15));
	}
}

PauseCanvas::~PauseCanvas()
{
}