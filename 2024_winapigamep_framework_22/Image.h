#pragma once
#include "UI.h"
class Texture;
class Image : public UI
{
public:
	Image();
	~Image() override;

public:
	Texture* texture;
	bool useNineSlice = true;
	float borderSize = 5.f;
	ComPtr<ID2D1SolidColorBrush> _brush = nullptr;
public:
	void LateUpdate() override;
	void Render(ComPtr<ID2D1RenderTarget> renderTarget) override;
};

