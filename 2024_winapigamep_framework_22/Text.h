#pragma once
#include "UI.h"
class Text : public UI
{
public:
	Text();
	~Text() override;

public:
	void LateUpdate() override;
	void Render(ComPtr<ID2D1RenderTarget> renderTarget) override;

public:
	void LoadFont(std::wstring fontName, int fontWidth, int fontHegith);

public:
	void SetPitchAndFamily(UINT iPitchAndFamily)
	{
		_iPitchAndFamily = iPitchAndFamily;
	}
	void SetText(wstring str)
	{
		_text = str;
	}
	const wstring& GetText()
	{
		return _text;
	}
	void SetColor(COLORREF color)
	{
		this->color = color;
	}

private:
	UINT _iPitchAndFamily;
	HFONT pfont;
	wstring _text;
	COLORREF color;

	ComPtr<IDWriteTextFormat> _textFormat;
};

