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

	renderTarget->DrawBitmap(
		texture->GetBitmap().Get(),
		D2D1::RectF(pos.x - size.x / 2, 
			pos.y - size.y / 2, 
			pos.x + size.x / 2,
			pos.y + size.y / 2),
		1.f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
	);
}