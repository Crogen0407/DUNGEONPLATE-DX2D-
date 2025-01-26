#pragma once
#include "Canvas.h"
class Slider;
class Picture;
class Button;
class Text;
class GameOverCanvas :
    public Canvas
{
public:
    GameOverCanvas();
    ~GameOverCanvas() override;
private:
    Text* titleText;
    Text* mentText;
    Button* retryButton;
    Button* gotoTitleSceneButton;
};

