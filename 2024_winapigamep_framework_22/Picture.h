#pragma once
#include "UI.h"
class Texture;
class Picture : public UI
{
public:
	Picture();
	~Picture() override;
public:
	Texture* texture;
public:
	void LateUpdate() override;
	void Render(HDC _hdc) override;
};

