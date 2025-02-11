#pragma once
// GameManager
//SAFE_DELETE()
// ���� �̱���(���̳��� �̱���)
// ���� �̱���
#include "Define.h"
//#include "Object.h"
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
	void CreateGDI();
public:
	const HWND& GetHwnd() const { return _hWnd; }
	// �̸� �ٲٱ�
	const HDC& GetMainDC() const { return m_hDC; }
	const HBRUSH& GetBrush(BRUSH_TYPE _eType)
	{
		return m_colorBrushs[(UINT)_eType];
	}
	const HPEN& GetPen(PEN_TYPE _eType)
	{
		return m_colorPens[(UINT)_eType];
	}
	const ComPtr<ID2D1HwndRenderTarget> GetRenderTarget() { return _renderTarget; }
private:
	HBRUSH m_colorBrushs[(UINT)BRUSH_TYPE::END] = {};
	HPEN m_colorPens[(UINT)PEN_TYPE::END] = {};

	HWND _hWnd;
	HDC  m_hDC; // Main DC
	HDC  m_hBackDC; // ����� DC
	HBITMAP m_hBackBit; // ������� bitmap

	ComPtr<ID2D1Factory> _factory = nullptr;

	ComPtr<ID2D1HwndRenderTarget> _renderTarget = nullptr;
	ID2D1SolidColorBrush* _brush = nullptr;
	ComPtr<ID2D1BitmapRenderTarget> _backBuffer = nullptr;
};