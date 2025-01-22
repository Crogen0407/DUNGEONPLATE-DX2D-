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
	slides.push_back(new Slide(L"<W>, <A>, <S>, <D>�� ������ �� �ֽ��ϴ�."));
	slides.push_back(new Slide(L"�÷��̾�� ���콺 ������ �ٶ󺾴ϴ�.\nŬ���� �ϸ� ������ �� �ְ��."));
	slides.push_back(new Slide(L"����� �������� ������ ������ �������� �� �� �����ϴ�."));
	slides.push_back(new Slide(L"������ ����ü�� ƨ�ܳ�����!\n�װ��� ������ �� �ִ� ������ ����Դϴ�."));
	slides.push_back(new Slide(L"���� óġ�ϸ� ����ġ�� ȹ���մϴ�."));
	slides.push_back(new Slide(L"�������Ͽ� �پ��� ��ų���� ȹ���غ�����."));

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
		_descriptionText->LoadFont(L"PF��Ÿ����Ʈ Bold", 28, 37);
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