#include "pch.h"
#include "Text.h"
#include "ResourceManager.h"
#include "Canvas.h"
#include "Core.h"

Text::Text() :
	_style(DWRITE_FONT_STYLE_NORMAL),
	_color(D2D1::ColorF(0x0f380f)),
	_weight(DWRITE_FONT_WEIGHT_NORMAL),
	_stretch(DWRITE_FONT_STRETCH_NORMAL)
{
	GET_SINGLE(Core)->GetRenderTarget()->CreateSolidColorBrush(_color, _brush.GetAddressOf());
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

	D2D1_RECT_F rect = { pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2 };  // 출력할 영역

	if (_brush == nullptr) return;

	renderTarget->DrawTextW(
		_text.c_str(),
		_text.size(),
		_textFormat.Get(),
		rect,
		_brush.Get()
	);

}

void Text::LoadFont(std::wstring fontName, float fontSize)
{
	GET_SINGLE(ResourceManager)->GetWriteFactory()->CreateTextFormat(
		fontName.c_str(),
		nullptr,
		_weight,
		_style,
		_stretch,
		fontSize,
		L"ko-KR",
		&_textFormat
	);
}

void Text::SetColor(D2D1::ColorF color)
{
	_color = color;

	ZeroMemory(_brush.GetAddressOf(), sizeof(_brush));

	GET_SINGLE(Core)->GetRenderTarget()->CreateSolidColorBrush(_color, _brush.GetAddressOf());
}