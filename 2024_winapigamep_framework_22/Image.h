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
public:
	void LateUpdate() override;
	void Render(ComPtr<ID2D1RenderTarget> renderTarget) override;
};

