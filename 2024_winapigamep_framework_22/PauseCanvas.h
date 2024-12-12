#pragma once
#include "Canvas.h"
class PauseCanvas : public Canvas
{
public:
    PauseCanvas();
    ~PauseCanvas() override;
public:
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hdc) override;
};

