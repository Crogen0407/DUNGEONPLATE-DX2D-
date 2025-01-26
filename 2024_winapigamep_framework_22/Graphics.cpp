#include "pch.h"
#include "Graphics.h"

Graphics::Graphics(HWND hWnd)
{
	_hWnd = hWnd;
	_width = SCREEN_WIDTH;
	_height = SCREEN_HEIGHT;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();
}

Graphics::~Graphics()
{
}

void Graphics::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc; // SwapChain를 만들기 위한 사전 설정을 '설명'한다
	ZeroMemory(&desc, sizeof(desc));
	{
		// 스크린의 크기를 넣는다(버퍼의 크기를 화면 픽셀에 맞추어 설정하기 위해)
		desc.BufferDesc.Width = SCREEN_WIDTH;
		desc.BufferDesc.Height = SCREEN_HEIGHT;

		// 화면 주사율
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;

		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		// 멀티샘플링
		desc.SampleDesc.Count = 1,
			desc.SampleDesc.Quality = 0;

		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;

		// 현재 윈도우 핸들을 설정한다
		desc.OutputWindow = _hWnd;

		// 현재 창모드인가
		desc.Windowed = true;

		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE, // 렌더링 하드웨어로 GPU를 사용하겠다는 뜻
		nullptr,
		0,
		nullptr, // DX 버전 중 어떤 기능을 지원할지 (nullptr 넣으면 사용할 수 있는 가장 최신 버전을 사용함)
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr);
}

void Graphics::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	CHECK(hr);
}

void Graphics::SetViewport()
{
	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	// 선에 뷰포트의 width, heigth 설정 안해서 오브젝트 안그려진 거 아직도 눈에 선함
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;
}

void Graphics::RenderBegin()
{
	// 후면 버퍼가 다그려졌으면 아웃풋으로 반환
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);

	// 후면 버퍼 색상을 단색으로 초기화
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);

	// 뷰포트 정보를 넣어야 한다
	_deviceContext->RSSetViewports(1, &_viewport);
}

void Graphics::RenderEnd()
{
	// 작업한 내용을 프레젠트(발표, 선보임)한다
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}
