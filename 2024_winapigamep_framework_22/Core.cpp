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

bool Core::Init(HWND _hwnd)
{
	cout << "�ִ��� ����ؿ䢽";
	// ���� �ʱ�ȭ
	_hWnd = _hwnd;
	m_hDC = ::GetDC(_hWnd);
	m_hBackDC = 0;
	m_hBackBit = 0;

	// ���� ���۸�
	// 1. ����(����)
	m_hBackBit = ::CreateCompatibleBitmap(m_hDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_hBackDC =::CreateCompatibleDC(m_hDC);

	// Direct2D ����
	{
		::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, _factory.GetAddressOf());

		// ���� Ÿ�� �Ӽ� ����
		D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			0, 0
		);

		// â �ڵ��� �����ͼ� ����
		D2D1_HWND_RENDER_TARGET_PROPERTIES hwndRTProps = D2D1::HwndRenderTargetProperties(
			_hWnd, D2D1::SizeU(SCREEN_WIDTH, SCREEN_HEIGHT)
		);
		_factory->CreateHwndRenderTarget(&rtProps, &hwndRTProps, _renderTarget.GetAddressOf());
		_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &_brush);

		// AA ����
		_renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	}

	// 2. ����
	::SelectObject(m_hBackDC,m_hBackBit);
	
	CreateGDI();
	// === Manager Init === 
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init();
	GET_SINGLE(ResourceManager)->Init();
	GET_SINGLE(SkillManager)->Init();
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(FadeManager)->Init();
	GET_SINGLE(GameManager)->Init();

	return true;
}
void Core::CleanUp()
{
	// �����Ѽ��� �ݴ�� ����
	::DeleteDC(m_hBackDC);	//createdc�Ѱ�
	::DeleteObject(m_hBackBit); // createbitmap �Ѱ�
	::ReleaseDC(_hWnd, m_hDC);
	_backBuffer->Release();

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_colorPens[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		// Hollow �����ϰ�
		DeleteObject(m_colorBrushs[i]);
	}

	GET_SINGLE(ResourceManager)->Release();
}

void Core::GameLoop()
{
	MainUpdate();
	MainRender();
	GET_SINGLE(EventManager)->Update();
}

void Core::MainUpdate()
{
	// === Manager Update === 
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SkillManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(CollisionManager)->Update();
	GET_SINGLE(FadeManager)->Update();
	GET_SINGLE(GameManager)->Update();
}

void Core::MainRender()
{
	//// 1. clear
	//::PatBlt(m_hBackDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);
	//// 2. Render
	//GET_SINGLE(SceneManager)->Render(m_hBackDC);
	//GET_SINGLE(FadeManager)->Render(m_hBackDC);
	//// 3. display	
	//::BitBlt(m_hDC, 0,0, SCREEN_WIDTH,SCREEN_HEIGHT,
	//		m_hBackDC,0,0, SRCCOPY);

	_renderTarget->CreateCompatibleRenderTarget(_backBuffer.GetAddressOf());
	{
		_backBuffer->BeginDraw();
		_backBuffer->Clear(D2D1::ColorF(D2D1::ColorF::Blue));
		{
			// Render
			GET_SINGLE(SceneManager)->Render(_backBuffer);
			GET_SINGLE(FadeManager)->Render(_backBuffer);
		}
		_backBuffer->EndDraw();

		ID2D1Bitmap* pBitmap = nullptr;
		_backBuffer->GetBitmap(&pBitmap);
		_renderTarget->BeginDraw();
		_renderTarget->DrawBitmap(pBitmap);
		_renderTarget->EndDraw();
		pBitmap->Release();
	}
 }
void Core::CreateGDI()
{
	// HOLLOW
	m_colorBrushs[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_colorBrushs[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	m_colorBrushs[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	m_colorBrushs[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	m_colorBrushs[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));

	//RED GREEN BLUE PEN
	m_colorPens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_colorPens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_colorPens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_colorPens[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_colorPens[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}
