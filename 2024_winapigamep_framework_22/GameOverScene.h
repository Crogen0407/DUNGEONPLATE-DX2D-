#pragma once
#include "Scene.h"
class Canvas;
class GameOverScene :
    public Scene
{
public:
    void Init() override;
private:
    Canvas* _canvas;
};

