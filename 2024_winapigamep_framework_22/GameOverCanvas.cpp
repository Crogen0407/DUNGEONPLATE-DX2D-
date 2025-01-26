#include "pch.h"
#include "GameOverCanvas.h"
#include "Picture.h"
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
		XMVECTOR size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		XMVECTOR pos = { XMVectorGetX(size) * 0.5f, XMVectorGetY(size) * 0.5f };
		Picture* background = CreateUI<Picture>(pos, size);
		background->texture = LOADTEXTURE(L"GameOver", L"Texture\\GameOver.bmp");
	}

	//TitleText
	{
		XMVECTOR size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		XMVECTOR pos = { XMVectorGetX(size) * 0.5f,XMVectorGetY(size)* 0.3f };
		titleText = CreateUI<Text>(pos, size);
		titleText->SetText(L"FAIL...");
		titleText->LoadFont(L"PF��Ÿ����Ʈ Bold", 60, 72);
		titleText->SetPitchAndFamily(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		titleText->SetColor(RGB(155, 188, 15));
	}

	//MentText
	{
		XMVECTOR size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		XMVECTOR pos = { XMVectorGetX(size) * 0.5f, XMVectorGetY(size) * 0.4f };
		mentText = CreateUI<Text>(pos, size);
		mentText->SetText(L"������ ������ ���� �ִ� �̴ϴ�");
		mentText->LoadFont(L"PF��Ÿ����Ʈ", 20, 25);
		mentText->SetPitchAndFamily(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		mentText->SetColor(RGB(155, 188, 15));
	}

	//RetryButton
	{
		XMVECTOR size = { 400, 50 };
		XMVECTOR pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
		retryButton = CreateUI<Button>(pos, size);
		retryButton->texture = LOADTEXTURE(L"UISprite8X1", L"Texture\\UISprite8X1.bmp");
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
			retryButtonText->LoadFont(L"PF��Ÿ����Ʈ Bold", 18, 21);
			retryButtonText->SetPitchAndFamily(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			retryButtonText->SetColor(RGB(15, 56, 15));
		}
	}

	//GotoTitleSceneButton
	{
		XMVECTOR size = { 400, 50 };
		XMVECTOR pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.57f };
		gotoTitleSceneButton = CreateUI<Button>(pos, size);
		gotoTitleSceneButton->texture = LOADTEXTURE(L"UISprite8X1", L"Texture\\UISprite8X1.bmp");
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
			retryButtonText->LoadFont(L"PF��Ÿ����Ʈ Bold", 18, 21);
			retryButtonText->SetPitchAndFamily(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			retryButtonText->SetColor(RGB(15, 56, 15));
		}
	}
}

GameOverCanvas::~GameOverCanvas()
{
}