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
		Vec2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		Image* background = CreateUI<Image>(pos, size);
		background->texture = LOADTEXTURE(L"OnePoint", L"Texture\\OnePoint.png");
	}

	//TitleText
	{
		Vec2 size = {1000, 100};
		Vec2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -40 };
		Text* text = CreateUI<Text>(pos, size);
		text->SetText(L"�Ͻ� ����");
		text->SetWeight(DWRITE_FONT_WEIGHT_BOLD);
		text->LoadFont(L"PF��Ÿ����Ʈ", 60);
		text->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
		text->SetColor(0x9bbc0f);
	}

	//DescriptionText
	{
		Vec2 size = { 1000, 100 };
		Vec2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 +40};
		Text* text = CreateUI<Text>(pos, size);
		text->SetText(L"Esc�� ���� �ٽ� ����...");
		text->LoadFont(L"PF��Ÿ����Ʈ", 40);
		text->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
		text->SetColor(0x9bbc0f);
	}
}

PauseCanvas::~PauseCanvas()
{
}

void PauseCanvas::Update()
{
}
