#include "pch.h"
#include "GameOverCanvas.h"
#include "Image.h"
#include "Text.h"
#include "Button.h"
#include "Slider.h"
#include "Player.h"
#include "Action.h"
#include "ResourceManager.h"
#include "FadeManager.h"

GameOverCanvas::GameOverCanvas()
{
	//BackGround
	{
		Vec2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		Vec2 pos = { size.x * 0.5f, size.y * 0.5f };
		Image* background = CreateUI<Image>(pos, size);
		background->texture = LOADTEXTURE(L"GameOver", L"Texture\\GameOver.png");
	}

	//TitleText
	{
		Vec2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		Vec2 pos = { size.x*0.5f, size.y * 0.3f };
		titleText = CreateUI<Text>(pos, size);
		titleText->SetText(L"FAIL...");
		titleText->SetWeight(DWRITE_FONT_WEIGHT_BOLD);
		titleText->LoadFont(L"PF스타더스트", 60);
		titleText->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
		titleText->SetColor(0x9bbc0f);
	}

	//MentText
	{
		Vec2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		Vec2 pos = { size.x * 0.5f, size.y * 0.4f };
		mentText = CreateUI<Text>(pos, size);
		mentText->SetText(L"가끔은 실패할 수도 있는 겁니다");
		mentText->LoadFont(L"PF스타더스트", 20);
		mentText->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
		mentText->SetColor(0x9bbc0f);
	}

	//RetryButton
	{
		Vec2 size = { 400, 50 };
		Vec2 pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
		retryButton = CreateUI<Button>(pos, size);
		retryButton->texture = LOADTEXTURE(L"UISprite8X1", L"Texture\\UISprite8X1.png");
		retryButton->onlyOneCountClick = true;
		retryButton->OnClickEvent +=
			[](int _)
			{
				GET_SINGLE(FadeManager)->LoadScene(L"GameScene");
			};
		//RetryButtonText
		{
			Text* retryButtonText = CreateUI<Text>(pos, size);
			retryButtonText->SetText(L"RETRY");
			retryButtonText->SetWeight(DWRITE_FONT_WEIGHT_BOLD);
			retryButtonText->LoadFont(L"PF스타더스트", 18);
			retryButtonText->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
			retryButtonText->SetColor(RGB(15, 56, 15));
		}
	}

	//GotoTitleSceneButton
	{
		Vec2 size = { 400, 50 };
		Vec2 pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.57f };
		gotoTitleSceneButton = CreateUI<Button>(pos, size);
		gotoTitleSceneButton->texture = LOADTEXTURE(L"UISprite8X1", L"Texture\\UISprite8X1.png");
		gotoTitleSceneButton->onlyOneCountClick = true;
		gotoTitleSceneButton->OnClickEvent +=
			[](int _)
			{
				GET_SINGLE(FadeManager)->LoadScene(L"TitleScene");
			};
		//GotoTitleButtonText
		{
			Text* gotoTitleButtonText = CreateUI<Text>(pos, size);
			gotoTitleButtonText->SetText(L"GOTOTITLE");
			gotoTitleButtonText->SetWeight(DWRITE_FONT_WEIGHT_BOLD);
			gotoTitleButtonText->LoadFont(L"PF스타더스트", 18);
			gotoTitleButtonText->SetPitchAndFamily(DWRITE_TEXT_ALIGNMENT_CENTER);
			gotoTitleButtonText->SetColor(RGB(15, 56, 15));
		}
	}
}

GameOverCanvas::~GameOverCanvas()
{
}

void GameOverCanvas::Update()
{

}
