#include "pch.h"
#include "GameClearCanvas.h"
#include "Button.h"
#include "Text.h"
#include "Slider.h"
#include "Image.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "FadeManager.h"
#include "GameManager.h"
#include <format>

GameClearCanvas::GameClearCanvas()
{
	SetName(L"GameClearCanvas");

	//Background
	{
		Vec2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		Vec2 pos = { size.x * 0.5f, size.y * 0.5f };
		Image* background = CreateUI<Image>(pos, size);
		background->texture = LOADTEXTURE(L"GameClear", L"Texture\\GameClear.png");
	}

	//TitleText
	{
		Vec2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		Vec2 pos = { size.x * 0.5f, size.y * 0.3f };
		titleText = CreateUI<Text>(pos, size);
		titleText->SetText(L"CLEAR!");
		titleText->SetWeight(DWRITE_FONT_WEIGHT_BOLD);
		titleText->LoadFont(L"PF��Ÿ����Ʈ", 60);
		titleText->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
		titleText->SetColor(0x9bbc0f);
	}

	//MentText
	{
		Vec2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		Vec2 pos = { size.x * 0.5f, size.y * 0.4f };
		mentText = CreateUI<Text>(pos, size);
		mentText->SetText(L"���ϵ帳�ϴ�!");
		mentText->LoadFont(L"PF��Ÿ����Ʈ", 20);
		mentText->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
		mentText->SetColor(0x9bbc0f);
	}

	//GotoTitleSceneButton
	{
		Vec2 size = { 400, 50 };
		Vec2 pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.585f };
		gotoTitleSceneButton = CreateUI<Button>(pos, size);
		gotoTitleSceneButton->texture = LOADTEXTURE(L"UISprite1X1", L"Texture\\UISprite1X1.png");
		gotoTitleSceneButton->onlyOneCountClick = true;
		gotoTitleSceneButton->OnClickEvent +=
			[](int _)
			{
				GET_SINGLE(FadeManager)->LoadScene(L"TitleScene");
			};
		//GotoTitleButtonText
		{
			Text* retryButtonText = CreateUI<Text>(pos, size);
			retryButtonText->SetText(L"GOTOTITLE");
			retryButtonText->SetWeight(DWRITE_FONT_WEIGHT_BOLD);
			retryButtonText->LoadFont(L"PF��Ÿ����Ʈ", 18);
			retryButtonText->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
		}
	}

	//InfoText
	{
		Vec2 size = { 300, 100 };
		Vec2 pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.506f };

		Text* infoText = CreateUI<Text>(pos, size);
		wstring str;
		//�������� ���� ������ ����
		str += L"TIME";
		infoText->SetText(str);
		infoText->SetWeight(DWRITE_FONT_WEIGHT_BOLD);
		infoText->LoadFont(L"PF��Ÿ����Ʈ", 17);
		infoText->SetPitchAndFamily();
		infoText->SetColor(0x9bbc0f);
	}

	//InfoValueText
	{
		Vec2 size = { 300, 100 };
		Vec2 pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.506f };

		Text* infoValueText = CreateUI<Text>(pos, size);
		wstring str;

		//�������� ���� ������ ����
		str += std::format(L"{0:02} : {1:02}", (int)TIME/60, (int)TIME%60);
		infoValueText->SetText(str);
		infoValueText->SetWeight(DWRITE_FONT_WEIGHT_BOLD);
		infoValueText->LoadFont(L"PF��Ÿ����Ʈ", 17);
		infoValueText->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_TRAILING);
		infoValueText->SetColor(0x9bbc0f);
	}
}

GameClearCanvas::~GameClearCanvas()
{
}
