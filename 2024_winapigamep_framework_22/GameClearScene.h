#pragma once
#include "Scene.h"
class Canvas;
class GameClearScene :
    public Scene
{
public:
    void Init() override;
    void Release() override;
private:
    Canvas* _canvas;
};

