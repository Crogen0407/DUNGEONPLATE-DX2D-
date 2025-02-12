#include "pch.h"
#include "Text.h"
#include "ResourceManager.h"
#include "Canvas.h"
#include "Core.h"

Text::Text()
{
	_iPitchAndFamily = TA_TOP | TA_LEFT;
	color = RGB(15, 56, 15);
}

Text::~Text()
{
}

void Text::LateUpdate()
{
}

void Text::Render(ComPtr<ID2D1RenderTarget> renderTarget)
{
	if (_owner == nullptr) return;
	Vec2 pos = GetPos() + _owner->GetPos();

	if (_parent != nullptr)
		pos += _parent->GetPos();

	Vec2 size = GetSize();

	RECT rect = { pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2 };  // 출력할 영역

	//renderTarget->DrawTextW(_text.c_str(), _text.size(), _owner->GetTextFormat(), D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom), _owner->GetBrush());

	//::DrawText(_hdc, text.c_str(), -1, &rect, iPitchAndFamily);

}

void Text::LoadFont(std::wstring fontName, int fontWidth, int fontHegith)
{
	GET_SINGLE(ResourceManager)->AddFont(fontName);
	pfont = CreateFont(fontHegith, fontWidth,
		0, 0, 0, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontName.c_str());
}
