#include "pch.h"
#include "Slider.h"
#include "Canvas.h"
#include "Texture.h"

Slider::Slider()
{
	fillColor = RGB(139, 172, 15);
	backColor = RGB(48, 98, 48);
	value = 1.f;
}

Slider::~Slider()
{
}

void Slider::LateUpdate()
{
}

void Slider::Render(std::shared_ptr<Pipeline> pipeline)
{
	//if (_owner == nullptr) return;
	//XMVECTOR pos = GetPos() + _owner->GetPos();
	//if (_parent != nullptr)
	//	pos += _parent->GetPos();

	//XMVECTOR size = GetSize();
	//backBrush = ::CreateSolidBrush(backColor);

	//HPEN myPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
	//HPEN oldPen = static_cast<HPEN>(::SelectObject(_hdc, myPen));
	//HBRUSH oldBackBrush = static_cast<HBRUSH>(::SelectObject(_hdc, backBrush));

	////BackTexture
	//::Rectangle(_hdc,
	//	(int)XMVectorGetX(pos) - XMVectorGetX(size) / 2,
	//	(int)XMVectorGetY(pos) - XMVectorGetY(size) / 2,
	//	(int)XMVectorGetX(pos) + XMVectorGetX(size) / 2,
	//	(int)XMVectorGetY(pos) + XMVectorGetY(size) / 2);

	//::SelectObject(_hdc, oldBackBrush);
	//::DeleteObject(backBrush);

	//fillBrush = ::CreateSolidBrush(fillColor);
	//HBRUSH oldFillBrush = static_cast<HBRUSH>(::SelectObject(_hdc, fillBrush));

	//if (isVertical)
	//{
	//	valueVec = XMVectorSet(1, value * 2 - 1, 0, 0);
	//}
	//else
	//{
	//	valueVec = XMVectorSet(value * 2 - 1, 1, 0, 0);
	//}

	//if (flip)
	//{
	//	//FillTexture
	//	::Rectangle(_hdc,
	//		(int)XMVectorGetX(pos) - (XMVectorGetX(size) * XMVectorGetX(valueVec)) / 2 + offsetX / 2,
	//		(int)XMVectorGetY(pos) - (XMVectorGetY(size) * XMVectorGetY(valueVec)) / 2 + offsetY / 2,
	//		(int)XMVectorGetX(pos) + (XMVectorGetX(size) / 2) - offsetX / 2,
	//		(int)XMVectorGetY(pos) + (XMVectorGetY(size) / 2) - offsetY / 2);
	//}
	//else
	//{
	//	//FillTexture
	//	::Rectangle(_hdc,
	//		(int)XMVectorGetX(pos) - (XMVectorGetX(size) / 2) + offsetX / 2,
	//		(int)XMVectorGetY(pos) - (XMVectorGetY(size) / 2) + offsetY / 2,
	//		(int)XMVectorGetX(pos) + (XMVectorGetX(size) * XMVectorGetX(valueVec)) / 2 - offsetX / 2,
	//		(int)XMVectorGetY(pos) + (XMVectorGetY(size) * XMVectorGetY(valueVec)) / 2 - offsetY / 2);
	//}

	//::SelectObject(_hdc, oldPen);
	//::SelectObject(_hdc, oldFillBrush);
	//::DeleteObject(myPen);
	//::DeleteObject(oldBackBrush);
	//::DeleteObject(fillBrush);
}
