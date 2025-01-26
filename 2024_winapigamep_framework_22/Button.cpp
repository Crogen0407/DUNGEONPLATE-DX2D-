#include "pch.h"
#include "Button.h"
#include "Texture.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Canvas.h"

Button::Button() :
	m_defaultTex(nullptr),
	m_selectedTex(nullptr),
	m_pressedTex(nullptr)
	
{
}

Button::~Button()
{
}

void Button::Init(Texture* defultTex, Texture* selectedTex, Texture* pressedTex)
{
	m_defaultTex = defultTex;
	m_selectedTex = selectedTex;
	m_pressedTex = pressedTex;
}

void Button::OnClick()
{
	if (onlyOneCountClick)
	{
		if (_isClicked == true) return;
		_isClicked = true;
	}
	if(m_pressedTex != nullptr)
		texture = m_pressedTex;
	OnClickEvent.Invoke(NULL);
}

void Button::OnSelectEnter()
{
	if (m_selectedTex != nullptr)
		texture = m_selectedTex;

	GET_SINGLE(ResourceManager)->LoadSound(L"ButtonSelect", L"Sound\\ButtonSelect.wav", false);
	GET_SINGLE(ResourceManager)->Play(L"ButtonSelect");
	OnSelectEnterEvent.Invoke(NULL);
}

void Button::OnSelectExit()
{
	if (m_defaultTex != nullptr)
		texture = m_defaultTex;
	OnSelectExitEvent.Invoke(NULL);
}

void Button::LateUpdate()
{
	if (_owner == nullptr) return;
	XMVECTOR pos = GetPos() + _owner->GetPos();
	if (_parent != nullptr)
		pos += _parent->GetPos();

	XMVECTOR size = GetSize();

	XMVECTOR mousePos = GET_MOUSEPOS;

	if (XMVectorGetY(pos) + (XMVectorGetY(size) / 2) > XMVectorGetY(mousePos) &&
		XMVectorGetX(pos) + (XMVectorGetX(size) / 2) > XMVectorGetX(mousePos) &&
		XMVectorGetY(pos) - (XMVectorGetY(size) / 2) < XMVectorGetY(mousePos) &&
		XMVectorGetX(pos) - (XMVectorGetX(size) / 2) < XMVectorGetX(mousePos)) //마우스가 닿았는지
	{
		if (m_isSelected == false)
		{
			m_isSelected = true;
			OnSelectEnter();
		}
		if (GET_KEYDOWN(KEY_TYPE::LBUTTON) || GET_KEYDOWN(KEY_TYPE::RBUTTON))
		{
			OnClick();
		}
	}
	else
	{
		if (m_isSelected == true)
		{
			m_isSelected = false;
			OnSelectExit();
		}
	}
}

void Button::Render(std::shared_ptr<Pipeline> pipeline)
{
	/*Picture::Render();

	if(_owner == nullptr) return;
	XMVECTOR pos = GetPos() + _owner->GetPos();
	if (_parent != nullptr)
		pos += _parent->GetPos();

	XMVECTOR size = GetSize();

	if (m_showDebug)
	{
		PEN_TYPE ePen = PEN_TYPE::RED;
		GDISelector pen(_hdc, ePen);
		GDISelector brush(_hdc, BRUSH_TYPE::HOLLOW);
		RECT_RENDER(_hdc, XMVectorGetX(pos), XMVectorGetY(pos),
			XMVectorGetX(size), XMVectorGetY(size));
	}*/
}