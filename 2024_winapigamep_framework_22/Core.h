#pragma once
#include "Define.h"
class Object;
class Core
{
	DECLARE_SINGLE(Core);
public:
	bool Init(HWND _hwnd);
	void GameLoop();
	void CleanUp();
private:
	void MainUpdate();
	void MainRender();
public:
	const HWND& GetHwnd() const { return _hWnd; }
	std::shared_ptr<Graphics> GetGraphics() { return _graphics; }
private:
	HWND _hWnd;
	std::shared_ptr<Graphics> _graphics;
	std::shared_ptr<Pipeline> _pipeline;
	
private:
	std::shared_ptr<Object> _object;
};