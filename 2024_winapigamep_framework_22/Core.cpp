#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "SkillManager.h"
#include "FadeManager.h"
#include "GameManager.h"
#include "Object.h"

bool Core::Init(HWND _hwnd)
{
	cout << "ÁÖ´¨½Ü »ç¶ûÇØ¿ä¢½";

	_hWnd = _hwnd;

	_graphics = std::make_shared<Graphics>(_hWnd);
	_pipeline = std::make_shared<Pipeline>(_graphics->GetDeviceContext());
	_object = std::make_shared<Object>();

	// === Manager Init === 
	/*GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init();
	GET_SINGLE(ResourceManager)->Init();
	GET_SINGLE(SkillManager)->Init();
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(FadeManager)->Init();
	GET_SINGLE(GameManager)->Init();*/

	return true;
}

void Core::CleanUp()
{
	//GET_SINGLE(ResourceManager)->Release();
}

void Core::GameLoop()
{
	MainUpdate();
	MainRender();
	//GET_SINGLE(EventManager)->Update();
}

void Core::MainUpdate()
{
	// === Manager Update === 
	/*GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SkillManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(CollisionManager)->Update();
	GET_SINGLE(FadeManager)->Update();
	GET_SINGLE(GameManager)->Update();*/

	_object->Update();
}

void Core::MainRender()
{
	_graphics->RenderBegin();
	{
		_object->Render(_pipeline);
	}
	_graphics->RenderEnd();
}