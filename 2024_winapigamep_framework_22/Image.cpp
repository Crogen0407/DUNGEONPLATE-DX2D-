#include "pch.h"
#include "Image.h"
#include "Canvas.h"
#include "Texture.h"

Image::Image() :
	texture(nullptr)
{
}

Image::~Image()
{
}

void Image::LateUpdate()
{
}

void Image::Render(ComPtr<ID2D1RenderTarget> renderTarget)
{
	if (texture == nullptr) return;

	if (_owner == nullptr) return;
	Vec2 pos = GetPos() + _owner->GetPos();
	if (_parent != nullptr)
		pos += _parent->GetPos();

	Vec2 size = GetSize();

	D2D1_RECT_F destRect = D2D1::RectF(
			pos.x - size.x / 2,
			pos.y - size.y / 2,
			pos.x + size.x / 2,
			pos.y + size.y / 2
		);

	if (useNineSlice == false)
	{
		renderTarget->DrawBitmap(
			texture->GetBitmap().Get(),
			destRect,
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
		);
		return;
	}

	Vec2 textureSize = { (float)texture->GetWidth(), (float)texture->GetHeight() };

	D2D1_RECT_F srcRects[9] = 
	{
		{ 0, 0, borderSize, borderSize }, // TL
		{ borderSize, 0, textureSize.x - borderSize, borderSize }, // T
		{ textureSize.x - borderSize, 0, textureSize.x, borderSize }, // TR

		{ 0, borderSize, borderSize, textureSize.y - borderSize }, // L
		{ borderSize, borderSize, textureSize.x - borderSize, textureSize.y - borderSize}, // C
		{ textureSize.x - borderSize, borderSize, textureSize.x, textureSize.y - borderSize }, // R

		{ 0, textureSize.y - borderSize, borderSize, textureSize.y }, // BL
		{ borderSize, textureSize.y - borderSize, textureSize.x - borderSize, textureSize.y }, // B
		{ textureSize.x - borderSize, textureSize.y - borderSize, textureSize.x, textureSize.y }, // BR
	};

	D2D1_RECT_F destRects[9] = {
		{ destRect.left, destRect.top, destRect.left + borderSize, destRect.top + borderSize },  // TL
		{ destRect.left + borderSize-1, destRect.top, destRect.right - borderSize + 1, destRect.top + borderSize },  // T
		{ destRect.right - borderSize, destRect.top, destRect.right, destRect.top + borderSize }, // TR

		{ destRect.left, destRect.top + borderSize - 1, destRect.left + borderSize, destRect.bottom - borderSize + 1 }, // L
		{ destRect.left + borderSize - 1, destRect.top + borderSize - 1, destRect.right - borderSize + 1, destRect.bottom - borderSize + 1}, // C (*�þ)
		{ destRect.right - borderSize, destRect.top + borderSize - 1, destRect.right, destRect.bottom - borderSize + 1 }, // R

		{ destRect.left, destRect.bottom - borderSize, destRect.left + borderSize, destRect.bottom },  // BL
		{ destRect.left + borderSize - 1, destRect.bottom - borderSize, destRect.right - borderSize + 1, destRect.bottom },  // B
		{ destRect.right - borderSize, destRect.bottom - borderSize, destRect.right, destRect.bottom } // BR
	};

	for (int i = 0; i < 9; i++){
		renderTarget->DrawBitmap(
			texture->GetBitmap().Get(),
			destRects[i],
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			srcRects[i]);
	}

	/*if(_brush == nullptr)
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(0xff0000), _brush.GetAddressOf());

	renderTarget->DrawRectangle(destRect, _brush.Get(), 1.f);*/
}