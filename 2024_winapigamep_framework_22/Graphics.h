#pragma once
class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

public:
	void RenderBegin();
	void RenderEnd();

private:
	HWND _hWnd;
	UINT _width = 0;
	UINT _height = 0;

private:
	ComPtr<ID3D11Device> _device = nullptr; // 리소스를 만들고 할당시키는 인터페이스
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr; // 리소르를 렌더파이프 라인에 연결하는 인터페이스
	ComPtr<IDXGISwapChain> _swapChain = nullptr; // 더블 버퍼링을 위한 인터페이스

	// RTV(후면 버퍼를 그리는 View)
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc
	D3D11_VIEWPORT _viewport = { };
	float _clearColor[4] = { 1, 1, 1, 1 };
	//float _clearColor[4] = { 15.f / 255.f, 56.f / 255.f, 15.f / 255.f, 1.f };

};

