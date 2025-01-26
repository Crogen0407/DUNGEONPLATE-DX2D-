#include "pch.h"
#include <format>
#include "GameCanvas.h"
#include "Picture.h"
#include "Text.h"
#include "Button.h"
#include "Slider.h"
#include "Player.h"
#include "Action.h"
#include "PlayerHealthCompo.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SkillManager.h"
#include "XPManager.h"
#include "DashSkill.h"
#include "StageLoader.h"

GameCanvas::GameCanvas() :
	healthBar(nullptr),
	shieldBar(nullptr),
	attackCountBar(nullptr),
	floorText(nullptr),
	timeText(nullptr)
{
	SetName(L"GameCanvas");
	GET_SINGLE(XPManager)->Init();
	int offset = 30;
	Player* player = static_cast<Player*>(FindObject(L"Player", LAYER::PLAYER));
	PlayerHealthCompo* playerHealthCompo = player->GetComponent<PlayerHealthCompo>();

	//BottomHeathContainer
	{
		XMVECTOR size = { 400.f - offset/2, 125.f - offset };
		XMVECTOR pos = { (XMVectorGetX(size) / 2) + offset / 2, (SCREEN_HEIGHT - XMVectorGetY(size) / 2) - offset/2 };

		Picture* BottomHeathContainer = CreateUI<Picture>(pos, size);
		BottomHeathContainer->texture = LOADTEXTURE(L"UISprite4X1", L"Texture\\UISprite4X1.bmp");

		//HealthBar
		{
			//HealthText
			{
				healthText = CreateUI<Text>({ XMVectorGetX(pos), XMVectorGetY(pos) - offset / 2 }, { XMVectorGetX(size) - offset, 45 });

				healthText->LoadFont(L"PF스타더스트", 12, 15);
				healthText->SetText(L"HP : 100%");
				healthText->SetColor(RGB(15, 56, 15));
				healthText->SetPitchAndFamily(DT_LEFT);

				playerHealthCompo->ChangeHpEvent +=
					[ct = healthText](float value)
					{
						std::wstring wstr;
						ct->SetText(L"HP : " + std::to_wstring((int)(value * 100.f)) + L"%");
					};
			}

			healthBar = CreateUI<Slider>(healthText->GetPos(), { XMVectorGetX(size) - offset, 45.f - offset });

			player->GetComponent<HealthCompo>()->ChangeHpEvent += 
				[ct = healthBar](float value) 
				{ 
					ct->SetValue(value); 
				};
		}

		//ShieldBar
		{
			//ShieldText
			{
				shieldText = CreateUI<Text>({ XMVectorGetX(pos), XMVectorGetY(pos) + offset * 0.9f }, { XMVectorGetX(size) - offset, 45 });

				shieldText->LoadFont(L"PF스타더스트", 12, 15);
				shieldText->SetText(L"SHIELD : 100%");
				shieldText->SetColor(RGB(15, 56, 15));
				shieldText->SetPitchAndFamily(DT_LEFT);

				playerHealthCompo->ChangeSubHpEvent +=
					[ct = shieldText](float value)
					{
						std::wstring wstr;
						ct->SetText(L"SHIELD : " + std::to_wstring((int)(value * 100.f)) + L"%");
					};
			}

			shieldBar = CreateUI<Slider>(shieldText->GetPos(), { XMVectorGetX(size) - offset, 45.f - offset });

			player->GetComponent<PlayerHealthCompo>()->ChangeSubHpEvent +=
				[ct = shieldBar](float value)
				{
					ct->SetValue(value);
				};
		}
	}

	//BottomAttackCountContainer
	{
		XMVECTOR size = { 62.5f - offset / 2, 125.f - offset };
		XMVECTOR pos = { 400 + offset, (int)(SCREEN_HEIGHT - XMVectorGetY(size) / 2 - offset/2) };

		Picture* BottomHeathContainer = CreateUI<Picture>(pos, size);
		BottomHeathContainer->texture = LOADTEXTURE(L"UISprite1X2", L"Texture\\UISprite1X2.bmp");

		//AttackCountBar
		{
			attackCountBar = CreateUI<Slider>(pos, { XMVectorGetX(size)-offset, XMVectorGetY(size)-offset });

			attackCountBar->isVertical = true;
			attackCountBar->flip = true;

			player->ParryCoolTimeEvent +=
				[ct = attackCountBar](float value) 
				{
					ct->SetValue(value);
				};
		}
	}

	//BottomDashCoolTimeContainer
	{
		XMVECTOR size = { 62.5f - offset / 2, 125.f - offset };
		XMVECTOR pos = { 400 + offset + (int)XMVectorGetX(size) + offset / 4, (int)(SCREEN_HEIGHT - XMVectorGetY(size) / 2 - offset / 2) };

		bottomDashCoolTimeContainer = CreateUI<Picture>(pos, size);
		bottomDashCoolTimeContainer->texture = LOADTEXTURE(L"UISprite1X2", L"Texture\\UISprite1X2.bmp");


		//DashCoolTimeBar
		{
			dashCoolTimeBar = CreateUI<Slider>(pos, { XMVectorGetX(size) - offset, XMVectorGetY(size) - offset });

			dashCoolTimeBar->isVertical = true;
			dashCoolTimeBar->flip = true;

			DashSkill* dashSkill = static_cast<DashSkill*>(GET_SINGLE(SkillManager)->GetSkill(ESkillType::DashSkill));
			dashSkill->DelayTimeEvent +=
				[ct = dashCoolTimeBar](float value)
				{
					ct->SetValue(value);
				};
		}

		bottomDashCoolTimeContainer->SetActive(false);
		dashCoolTimeBar->SetActive(false);
	}

	//floorText
	{
		{
			XMVECTOR size = { 70, 70 };
			XMVECTOR pos = { SCREEN_WIDTH / 2, (int)XMVectorGetY(size) / 2 + 15 };
			Picture* floorText = CreateUI<Picture>(pos, size);
			floorText->texture = LOADTEXTURE(L"UISprite1X1", L"Texture\\UISprite1X1.bmp");
		}

		XMVECTOR size = { 50, 60 };
		XMVECTOR pos = { SCREEN_WIDTH / 2, (int)XMVectorGetY(size)/2 + 25 };

		floorText = CreateUI<Text>(pos, size);
		floorText->LoadFont(L"PF스타더스트 Bold", 40, 55);
		floorText->SetText(L"1");

		floorText->SetColor(RGB(15, 56, 15));
		floorText->SetPitchAndFamily(DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		StageLoader::StageLoadEvent.Clear();

		StageLoader::StageLoadEvent +=
			[ct = floorText](int stage)
			{
				ct->SetText(std::to_wstring(stage+1));
			};

	}

	//TimeText
	{
		XMVECTOR size = { 80, 30 };
		XMVECTOR pos = { SCREEN_WIDTH - (int)XMVectorGetX(size)/2,  offset };
		timeText = CreateUI<Text>(pos, size);

		timeText->LoadFont(L"PF스타더스트", 18, 24);
		timeText->SetText(L"00:00");
		timeText->SetColor(RGB(139, 172, 15));
		timeText->SetPitchAndFamily(DT_LEFT);
	}

	//XPBar
	{
		XMVECTOR size = {SCREEN_WIDTH, 10};
		XMVECTOR pos = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - XMVectorGetY(size) / 2 };
		xpBar = CreateUI<Slider>(pos, size);
		xpBar->offsetX = 0;
		xpBar->offsetY = 0;
		xpBar->SetValue(0.f);
		GET_SINGLE(XPManager)->IncreaseXPEvent +=
			[ct = xpBar](float value) {
				ct->SetValue(value);
			};
	}
}

GameCanvas::~GameCanvas()
{
}

void GameCanvas::Update()
{
	Canvas::Update();
	if (isMoveToNextStage)
	{
		int speed = 400;
		if (_isMoveToUp)
		{
			XMVECTOR delta = { 0.f,-fUNSCALEDDT * speed };
			AddPos(delta);
			if (GetPosY() <= _minOffset)
			{
				_isMoveToUp = false;
			}
		}
		else
		{
			XMVECTOR delta = { 0.f,fUNSCALEDDT * speed };
			AddPos(delta);
			if (GetPosY() >= 0)
			{
				_isMoveToUp = true;
				isMoveToNextStage = false;
				XMVECTOR origin = { 0, 0 };
				SetPos(origin);
			}
		}
	}

	int s = (int)TIME%60;
	int m = (TIME / 60);

	std::string finalStr = std::format("{0:02}:{1:02}", m, s);
	wstring message_w;
	timeText->SetText(message_w.assign(finalStr.begin(), finalStr.end()).c_str());
}

void GameCanvas::ShowDashUI()
{
	dashCoolTimeBar->SetActive(true);
	bottomDashCoolTimeContainer->SetActive(true);
}
