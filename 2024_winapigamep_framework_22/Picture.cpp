#include "pch.h"
#include "Picture.h"
#include "Canvas.h"
#include "Texture.h"

Picture::Picture() :
	texture(nullptr)
{
}

Picture::~Picture()
{
}

void Picture::LateUpdate()
{
}

void Picture::Render(HDC _hdc)
{
	if (texture == nullptr) return;

	if (_owner == nullptr) return;
	XMVECTOR pos = GetPos() + _owner->GetPos();
	if (_parent != nullptr)
		pos += _parent->GetPos();

	XMVECTOR size = GetSize();

	TransparentBlt(_hdc,
		(int)XMVectorGetX(pos) - XMVectorGetX(size) / 2,
		(int)XMVectorGetY(pos) - XMVectorGetY(size) / 2,
		(int)XMVectorGetX(size),
		(int)XMVectorGetY(size),
		texture->GetTexDC(),
		0,
		0,
		texture->GetWidth(),
		texture->GetHeight(),
		RGB(255, 0, 255));
}