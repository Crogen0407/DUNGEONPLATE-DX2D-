#include "pch.h"
#include "SkillCanvas.h"
#include "Button.h"
#include "Text.h"
#include "ResourceManager.h"
#include "SkillManager.h"
#include "TimeManager.h"
#include "XPManager.h"
#include "InputManager.h"
#include "Skill.h"

SkillCanvas::SkillCanvas()
{
	SetName(L"SkillCanvas");
	_skillSlots.clear();

	GET_SINGLE(ResourceManager)->LoadSound(L"LevelUp", L"Sound\\LevelUp.wav", false);
	/*XMVECTOR center = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	int xDeltaPos = 300;

	{
		XMVECTOR size = { SCREEN_WIDTH * 2, 420};
		XMVECTOR pos = center;
		Picture* backPicture = CreateUI<Picture>(pos, size);
		backPicture->texture = LOADTEXTURE(L"UISprite2X2", L"Texture\\UISprite2X2.bmp");
	}

	CreateSlot(center - XMVECTOR(xDeltaPos, 0));
	CreateSlot(center);
	CreateSlot(center + XMVECTOR(xDeltaPos, 0));*/

	GET_SINGLE(XPManager)->LevelUpEvent +=
		[ct = this](int level)
		{
			ct->ShowSlots();
		};
}

SkillCanvas::~SkillCanvas()
{
	_skillSlots.clear();
}

void SkillCanvas::Update()
{
	Canvas::Update();
}

void SkillCanvas::LateUpdate()
{
	if (showSkillSlots == false) return;
	Canvas::LateUpdate();
}

void SkillCanvas::Render(std::shared_ptr<Pipeline> pipeline)
{
	if (showSkillSlots == false) return;
	Canvas::Render(pipeline);
}

void SkillCanvas::CreateSlot(XMVECTOR slotPos)
{
	SkillSlot* skillSlot = CreateUI<SkillSlot>(slotPos, { 250, 320 });

	XMVECTOR namePos = { 0, -110 };
	XMVECTOR nameSize = { skillSlot->GetSizeX() - 30, 30.f };

	XMVECTOR levelPos = { 0, -64 };
	XMVECTOR levelSize = { skillSlot->GetSizeX() - 30, 30.f };

	XMVECTOR descriptionPos = { 0, 110 };
	XMVECTOR descriptionSize = skillSlot->GetSize();
	descriptionSize -= { 30.f, 30.f };

	skillSlot->name =			CreateUI<Text>(namePos, nameSize);
	skillSlot->level =			CreateUI<Text>(levelPos, levelSize);
	skillSlot->description =	CreateUI<Text>(descriptionPos, descriptionSize);
	skillSlot->level->SetText(L"New!");
	skillSlot->texture = LOADTEXTURE(L"UISpriteSlot", L"Texture\\UISpriteSlot.bmp");

	skillSlot->name->LoadFont(L"PF스타더스트 Bold", 25, 30);
	skillSlot->name->SetPitchAndFamily(DT_VCENTER);
	skillSlot->name->SetParent(skillSlot);

	skillSlot->level->LoadFont(L"PF스타더스트", 18, 24);
	skillSlot->level->SetPitchAndFamily(DT_VCENTER);
	skillSlot->level->SetParent(skillSlot);

	skillSlot->description->LoadFont(L"PF스타더스트", 15, 18);
	skillSlot->description->SetPitchAndFamily(DT_LEFT | DT_TOP);
	skillSlot->description->SetParent(skillSlot);

	//Button Events
	skillSlot->OnClickEvent +=
		[ct = this, skillSlot, player = GET_SINGLE(SkillManager)->player](int _)
		{
			skillSlot->skill->OnLevelUp(player);
			ct->CloseSlot();
		};

	skillSlot->OnSelectEnterEvent +=
		[skillSlot](int _)
		{
			XMVECTOR posDelta = { 0, -10 };
			skillSlot->SetSize({250 * 1.05f, 320 * 1.05f });
			skillSlot->AddPos(posDelta);
		};

	skillSlot->OnSelectExitEvent +=
		[skillSlot](int _)
		{
			XMVECTOR posDelta = { 0, 10 };
			skillSlot->SetSize({ 250, 320 });
			skillSlot->AddPos(posDelta);
		};


	_skillSlots.push_back(skillSlot);
}

void SkillCanvas::ShowSlots()
{
	GET_SINGLE(ResourceManager)->Play(L"LevelUp");

	vector<Skill*> selectedSkills = GET_SINGLE(SkillManager)->GetRandomSkills();
	showSkillSlots = true;

	if (_skillSlots.size() == 0)
	{
		_skillSlots.clear();
		XMVECTOR center = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		int xDeltaPos = 300;

		{
			XMVECTOR size = { SCREEN_WIDTH * 2, 420 };
			XMVECTOR pos = center;
			Picture* backPicture = CreateUI<Picture>(pos, size);
			backPicture->texture = LOADTEXTURE(L"UISprite2X2", L"Texture\\UISprite2X2.bmp");
		}

		CreateSlot(XMVectorSubtract(center, {-(float)xDeltaPos, 0}));
		CreateSlot(center);
		CreateSlot(XMVectorSubtract(center, {(float)xDeltaPos, 0 }));

		GET_SINGLE(XPManager)->LevelUpEvent +=
			[ct = this](int level)
			{
				ct->ShowSlots();
			};
	}


	int i = 0;
	for (auto skillSlot : _skillSlots)
	{
		skillSlot->Init(selectedSkills[i]);
		i++;
	}

	TIMESCALE = 0;
}

void SkillCanvas::CloseSlot()
{
	TIMESCALE = 1;

	showSkillSlots = false;
}
