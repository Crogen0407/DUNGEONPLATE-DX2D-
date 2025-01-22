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
	cout << "주뇽쌤 사랑해요♡";

	_hWnd = _hwnd;
	_width = SCREEN_WIDTH;
	_height = SCREEN_HEIGHT;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();

	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();


	
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
	// 생성한순서 반대로 삭제
	::DeleteDC(_hBackDC);	//createdc한거
	::DeleteObject(_hBackBit); // createbitmap 한거
	::ReleaseDC(_hWnd, _hDC);
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_colorPens[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		// Hollow 제외하고
		DeleteObject(m_colorBrushs[i]);
	}

	GET_SINGLE(ResourceManager)->Release();
}

void Core::GameLoop()
{
	//static int callcount = 0;
	//++callcount;
	//static int prev = GetTickCount64();
	//int cur = GetTickCount64();
	//if (cur - prev > 1000)
	//{
	//	prev = cur;
	//	callcount = 0;
	//}
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
	RenderBegin();

	{
		UINT vertexSize = sizeof(Vertex);
		UINT offset = 0;

		// IA
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &vertexSize, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetInputLayout(_inputLayout.Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// VS
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);

		// RS

		// PS
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

		// OM

		_deviceContext->DrawIndexed(_indices.size(), 0, 0);

		/*GET_SINGLE(SceneManager)->Render(_hBackDC);
		GET_SINGLE(FadeManager)->Render(_hBackDC);*/
	}

	RenderEnd();
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

void Core::RenderBegin()
{
	// 후면 버퍼가 다그려졌으면 아웃풋으로 반환
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);

	// 후면 버퍼 색상을 단색으로 초기화
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);

	// 뷰포트 정보를 넣어야 한다
	_deviceContext->RSSetViewports(1, &_viewport);
}

void Core::RenderEnd()
{
	// 작업한 내용을 프레젠트(발표, 선보임)한다
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}

void Core::CreateDeviceAndSwapChain()
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

void Core::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	CHECK(hr);
}

void Core::SetViewport()
{
	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	// 선에 뷰포트의 width, heigth 설정 안해서 오브젝트 안그려진 거 아직도 눈에 선함
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;
}

void Core::CreateGeometry()
{
	// VertexData
	{
		_vertices.resize(4);

		_vertices[0].position = { -0.5f, -0.5f, 0 };
		_vertices[0].color = XMFLOAT4( 1, 0, 0, 1 );
		//_vertices[0].uv = { 0.f, 1.f };

		_vertices[1].position = { -0.5f, 0.5f, 0 };
		_vertices[1].color = XMFLOAT4(1, 1, 0, 1);
		//_vertices[1].uv = { 0.f, 0.f };

		_vertices[2].position = { 0.5f, -0.5f, 0 };
		_vertices[2].color = XMFLOAT4(1, 1, 1, 1);
		//_vertices[2].uv = { 1.f, 1.f };

		_vertices[3].position = { 0.5f, 0.5f, 0 };
		_vertices[3].color = XMFLOAT4(0, 0, 0, 1);
		//_vertices[3].uv = {1.f, 0.f};
	}

	// VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // 해당 버퍼를 CPU와 GPU가 접근할 수 있는지의 여부를 정해준다
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 버텍스 버퍼를 만드는 데 사용할 것이다
		desc.ByteWidth = (UINT)(sizeof(Vertex) * _vertices.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _vertices.data();

		HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
	}

	// Index
	{
		_indices = { 0, 1, 2, 2, 1, 3 };
	}

	// IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // 해당 버퍼를 CPU와 GPU가 접근할 수 있는지의 여부를 정해준다
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // 인덱스 버퍼를 만드는 데 사용할 것이다
		desc.ByteWidth = (UINT)(sizeof(UINT) * _indices.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _indices.data();

		HRESULT hr = _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
		CHECK(hr);
	}
}

void Core::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	const int count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	_device->CreateInputLayout(layout, count, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
}

void Core::CreateVS()
{
	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", _vsBlob);
	HRESULT hr = _device->CreateVertexShader(_vsBlob->GetBufferPointer(), 
		_vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
	CHECK(hr);
}

void Core::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);
	HRESULT hr = _device->CreatePixelShader(_psBlob->GetBufferPointer(), 
		_psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());
	CHECK(hr);
}

void Core::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	UINT compileFlag = 0;

#ifdef _DEBUG
	compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	
	HRESULT hr = ::D3DCompileFromFile(
		(L"Resource\\Shaders\\" + path).c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(),
		nullptr);

	CHECK(hr);
}
