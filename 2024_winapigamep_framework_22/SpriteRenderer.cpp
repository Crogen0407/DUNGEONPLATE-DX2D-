#include "pch.h"
#include "SpriteRenderer.h"
#include "Object.h"
#include "Texture.h"
#include<algorithm>

SpriteRenderer::SpriteRenderer():
	texture(nullptr)
{

}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::LateUpdate()
{
	if (texture == nullptr) return;
}

void SpriteRenderer::Render()
{
	if (texture == nullptr) return;
	if (enable == false) return;
	XMVECTOR pos = GetOwner()->GetPos();
	XMVECTOR size = GetOwner()->GetSize();
	XMVECTOR texSize = { (float)texture->GetWidth(), (float)texture->GetHeight() };
	if (isRotatable)
	{
		float sinA = sinf(angle - PI / 2);
		float cosA = cosf(angle - PI / 2);

		float halfWidth = XMVectorGetX(size) / 2;
		float halfHeight = XMVectorGetY(size) / 2;

		POINT vertices[4];

		vertices[0].x = (-halfWidth * cosA + (-halfHeight) * sinA);
		vertices[0].y = (-halfWidth * sinA - (-halfHeight) * cosA);

		vertices[1].x = (halfWidth * cosA + (-halfHeight) * sinA);
		vertices[1].y = (halfWidth * sinA - (-halfHeight) * cosA);

		vertices[2].x = (-halfWidth * cosA + (halfHeight)*sinA);
		vertices[2].y = (-halfWidth * sinA - (halfHeight)*cosA);

		vertices[3].x = (halfWidth * cosA + (halfHeight)*sinA);
		vertices[3].y = (halfWidth * sinA - (halfHeight)*cosA);

		float maxX = vertices[0].x;
		float maxY = vertices[0].y;
		float minX = vertices[0].x;
		float minY = vertices[0].y;

		for (int i = 1; i < 4; i++)
		{
			if (vertices[i].x > maxX)
				maxX = vertices[i].x;
			if (vertices[i].y > maxY)
				maxY = vertices[i].y;
			if (vertices[i].x < minX)
				minX = vertices[i].x;
			if (vertices[i].y < minY)
				minY = vertices[i].y;
		}

		/*hBmap = CreateCompatibleBitmap(texture->GetTexDC(), maxX - minX, maxY - minY);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBmap);

		RECT rect = { 0, 0, maxX - minX, maxY - minY };
		FillRect(memDC, &rect, brush);*/
		POINT verticesSubset[3] = { vertices[0], vertices[1], vertices[2] };

		for (int i = 0; i < 4; ++i) {
			if (minX < 0)
			{
				vertices[i].x -= minX;
				if (vertices[i].x > maxX)
				{
					maxX = vertices[i].x;
				}
			}
			if (minY < 0)
			{
				vertices[i].y -= minY;
				if (vertices[i].y > maxY)
				{
					maxY = vertices[i].y;
				}
			}

			if (i != 3)
			{
				verticesSubset[i] = vertices[i];
			}
		}

		if (minX < 0)
			minX = 0;
		if (minY < 0)
			minY = 0;

		//PlgBlt(memDC,
		//	verticesSubset,
		//	texture->GetTexDC(),
		//	0, 0,
		//	texture->GetWidth(),
		//	texture->GetHeight(),
		//	nullptr, 0, 0);

		//float xPercent = (maxX - minX) / XMVectorGetX(texSize);
		//float yPercent = (maxY - minY) / XMVectorGetY(texSize);

		//size = XMVectorSet(xPercent * XMVectorGetX(size), 
		//	yPercent * XMVectorGetY(size), 0, 0);

		//TransparentBlt(_hdc,
		//	(int)(XMVectorGetX(pos) - XMVectorGetX(size) / 2),
		//	(int)(XMVectorGetY(pos) - XMVectorGetY(size) / 2),
		//	(int)XMVectorGetX(size),
		//	(int)XMVectorGetY(size),
		//	memDC,
		//	minX, minY, // 회전 이후 영역 좌상단
		//	maxX - minX, // 회전 이후 영역 W
		//	maxY - minY, // 회전 이후 영역 H
		//	RGB(255, 0, 255)); // 흰색 영역 투명화

		//SelectObject(memDC, oldBitmap);
		//DeleteObject(hBmap);
	}
	else
	{
		//TransparentBlt(_hdc,
		//	(int)(XMVectorGetX(pos) - XMVectorGetX(size) / 2),
		//	(int)(XMVectorGetY(pos) - XMVectorGetY(size) / 2),
		//	(int)XMVectorGetX(size),
		//	(int)XMVectorGetY(size),
		//	texture->GetTexDC(),
		//	0, 0, // 회전 이후 영역 좌상단
		//	XMVectorGetX(texSize),
		//	XMVectorGetY(texSize),
		//	RGB(255, 0, 255)); // 흰색 영역 투명화
	}
}

void SpriteRenderer::SetTexture(std::wstring name, std::wstring path)
{
	//texture = LOADTEXTURE(name, path);
	//if (isRotatable == false) return;
	//if(memDC != nullptr)
	//	DeleteDC(memDC);
	//memDC = CreateCompatibleDC();
}

void SpriteRenderer::SetTexture(Texture* texture)
{
	/*this->texture = texture;
	if (isRotatable == false) return;
	if (memDC != nullptr)
		DeleteDC(memDC);
	memDC = CreateCompatibleDC(texture->GetTexDC());*/
}
