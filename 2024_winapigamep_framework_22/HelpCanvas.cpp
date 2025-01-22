#include "pch.h"
#include "HelpCanvas.h"
#include "Picture.h"
#include "Text.h"
#include "Button.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "FadeManager.h"
#include <format>

HelpCanvas::HelpCanvas()
{
	slides.push_back(new Slide(L"<W>, <A>, <S>, <D>로 움직일 수 있습니다."));
	slides.push_back(new Slide(L"플레이어는 마우스 방향을 바라봅니다.\n클릭을 하면 공격할 수 있고요."));
	slides.push_back(new Slide(L"평범한 공격으론 던전의 적에게 흔집조차 낼 수 없습니다."));
	slides.push_back(new Slide(L"적들의 투사체를 튕겨내세요!\n그것이 공격할 수 있는 유일한 방법입니다."));
	slides.push_back(new Slide(L"적을 처치하면 경험치를 획득합니다."));
	slides.push_back(new Slide(L"레벨업하여 다양한 스킬들을 획득해보세요."));

	for (int i = 0; i < slides.size(); i++)
	{
		std::wstring flieName = std::format(L"Slide{0:02}", (i + 1));
		slides[i]->texture = LOADTEXTURE(flieName, L"Texture\\"+ flieName+ L".bmp");
	}

	//Background
	{
		XMVECTOR size = {SCREEN_WIDTH, SCREEN_HEIGHT};
		XMVECTOR pos = { XMVectorGetX(size) / 2, XMVectorGetY(size) / 2 };
		Picture* background = CreateUI<Picture>(pos, size);
		background->texture = LOADTEXTURE(L"OnePoint", L"Texture\\OnePoint.bmp");
	}

	//Slide
	{
		XMVECTOR size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		XMVECTOR pos = { XMVectorGetX(size) / 2, XMVectorGetY(size) / 2 };
		_slidePicture = CreateUI<Picture>(pos, size);
		_slidePicture->texture = slides[0]->texture;
	}

	//DescriptionText
	{
		XMVECTOR size = { SCREEN_WIDTH , (SCREEN_HEIGHT / 8) * 2 };
		XMVECTOR pos = { SCREEN_WIDTH/2.f, SCREEN_HEIGHT-(XMVectorGetY(size)/2)};
		_descriptionText = CreateUI<Text>(pos, size);
		_descriptionText->SetColor(RGB(155, 188, 15));
		_descriptionText->LoadFont(L"PF스타더스트 Bold", 28, 37);
		_descriptionText->SetPitchAndFamily(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		_descriptionText->SetText(slides[0]->description);
	}
}

HelpCanvas::~HelpCanvas()
{
	for (int i = 0; i < slides.size(); i++)
	{
		delete slides[i];
	}
}

void HelpCanvas::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		++_curSlide;
		if (_curSlide > slides.size()-1 && _isFading == false)
		{
			_isFading = true;
			GET_SINGLE(FadeManager)->LoadScene(L"TitleScene");
			return;
		}
		if (_isFading == true) return;
		_slidePicture->texture = slides[_curSlide]->texture;
		_descriptionText->SetText(slides[_curSlide]->description);
	}
}