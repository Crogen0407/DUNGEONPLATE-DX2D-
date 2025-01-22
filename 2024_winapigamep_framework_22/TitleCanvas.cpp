#include "pch.h"
#include "TitleCanvas.h"
#include "Picture.h"
#include "Text.h"
#include "Button.h"
#include "Slider.h"
#include "Player.h"
#include "Action.h"
#include "ResourceManager.h"
#include "FadeManager.h"

TitleCanvas::TitleCanvas()
{
	//Fill
	{
		XMVECTOR size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		XMVECTOR pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
		Picture* fill = CreateUI<Picture>(pos, size);
		fill->texture = LOADTEXTURE(L"OnePoint", L"Texture\\OnePoint.bmp");
	}

	//BackGround
	{
		XMVECTOR size = { SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
		XMVECTOR pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.55f };
		Picture* background = CreateUI<Picture>(pos, size);
		background->texture = LOADTEXTURE(L"Background", L"Texture\\Background.bmp");
	}

	//TitleText
	{
		XMVECTOR size = { 844, 153 };
		XMVECTOR pos = {SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT* 0.26f };
		Picture* titleText = CreateUI<Picture>(pos, size);
		titleText->texture = LOADTEXTURE(L"Title", L"Texture\\Title.bmp");
	}

	//StartButton
	{
		XMVECTOR size = { 250, 32 };
		XMVECTOR pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.47f };
		_startButton = CreateUI<Button>(pos, size);
		_startButton->texture = LOADTEXTURE(L"UISprite8X1", L"Texture\\UISprite8X1.bmp");
		_startButton->onlyOneCountClick = true;
		_startButton->OnClickEvent +=
			[](int _)
			{
				GET_SINGLE(FadeManager)->LoadScene(L"GameScene");
			};
		_startButton->OnSelectEnterEvent +=
			[ct = _startButton](int _)
			{
				ct->AddPos({ 0, -2 });
				ct->SetSize({ 260, 36 });
			};
		_startButton->OnSelectExitEvent +=
			[ct = _startButton](int _)
			{
				ct->AddPos({ 0, 2 });
				ct->SetSize({ 250, 32 });
			};
		//StartButtonText
		{
			Text* startButtonText = CreateUI<Text>({ 0, 0 }, size);
			startButtonText->SetParent(_startButton);
			startButtonText->SetText(L"START");
			startButtonText->LoadFont(L"PF스타더스트 Bold", 18, 21);
			startButtonText->SetPitchAndFamily(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			startButtonText->SetColor(RGB(15, 56, 15));
		}
	}

	//HelpButton
	{
		XMVECTOR size = { 250, 32 };
		XMVECTOR pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.55f };
		_helpButton = CreateUI<Button>(pos, size);
		_helpButton->texture = LOADTEXTURE(L"UISprite8X1", L"Texture\\UISprite8X1.bmp");
		_helpButton->onlyOneCountClick = true;
		_helpButton->OnClickEvent +=
			[](int _)
			{
				GET_SINGLE(FadeManager)->LoadScene(L"HelpScene");
			};
		_helpButton->OnSelectEnterEvent +=
			[ct = _helpButton](int _)
			{
				ct->AddPos({ 0, -2 });
				ct->SetSize({ 260, 36 });
			};
		_helpButton->OnSelectExitEvent +=
			[ct = _helpButton](int _)
			{
				ct->AddPos({ 0, 2 });
				ct->SetSize({ 250, 32 });
			};

		//HelpButtonText
		{
			Text* helpButtonText = CreateUI<Text>({0, 0}, size);
			helpButtonText->SetParent(_helpButton);
			helpButtonText->SetText(L"HELP");
			helpButtonText->LoadFont(L"PF스타더스트 Bold", 18, 21);
			helpButtonText->SetPitchAndFamily(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			helpButtonText->SetColor(RGB(15, 56, 15));
		}
	}

	//QuitButton
	{
		XMVECTOR size = { 250, 32 };
		XMVECTOR pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.63f };
		_quitButton = CreateUI<Button>(pos, size);
		_quitButton->texture = LOADTEXTURE(L"UISprite8X1", L"Texture\\UISprite8X1.bmp");
		_quitButton->onlyOneCountClick = true;
		_quitButton->OnClickEvent +=
			[](int _)
			{
				PostQuitMessage(NULL);
			};
		_quitButton->OnSelectEnterEvent +=
			[ct = _quitButton](int _)
			{
				ct->AddPos({ 0, -2 });
				ct->SetSize({ 260, 36 });
			};
		_quitButton->OnSelectExitEvent +=
			[ct = _quitButton](int _)
			{
				ct->AddPos({ 0, 2 });
				ct->SetSize({ 250, 32 });
			};
		//QuitButtonText
		{
			Text* quitButtonText = CreateUI<Text>({0, 0}, size);
			quitButtonText->SetParent(_quitButton);
			quitButtonText->SetText(L"QUIT");
			quitButtonText->LoadFont(L"PF스타더스트 Bold", 18, 21);
			quitButtonText->SetPitchAndFamily(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			quitButtonText->SetColor(RGB(15, 56, 15));
		}
	}

	//DevText
	{
		XMVECTOR size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		XMVECTOR pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };

		Text* devText = CreateUI<Text>(pos, size);
		devText->SetText(L"김진후, 정윤찬, 최영환");
		devText->LoadFont(L"PF스타더스트 Bold", 18, 21);
		devText->SetPitchAndFamily(DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
		devText->SetColor(RGB(155, 188, 15));
	}
}

TitleCanvas::~TitleCanvas()
{
}

void TitleCanvas::Update()
{
	Canvas::Update();
}

void TitleCanvas::LateUpdate()
{
	Canvas::LateUpdate();
}

void TitleCanvas::Render(HDC hdc)
{
	Canvas::Render(hdc);
}
