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
	const HDC& GetMainDC() const { return _hDC; }
	const HBRUSH& GetBrush(BRUSH_TYPE _eType)
	{
		return m_colorBrushs[(UINT)_eType];
	}
	const HPEN& GetPen(PEN_TYPE _eType)
	{
		return m_colorPens[(UINT)_eType];
	}

private:
	HBRUSH m_colorBrushs[(UINT)BRUSH_TYPE::END] = {};
	HPEN m_colorPens[(UINT)PEN_TYPE::END] = {};

	HWND _hWnd;
	HDC  _hDC; // Main DC
	HDC  _hBackDC; // ����� DC
	HBITMAP _hBackBit; // ������� bitmap
	UINT _width = 0;
	UINT _height = 0;

private:
	ComPtr<ID3D11Device> _device = nullptr; // ���ҽ��� ����� �Ҵ��Ű�� �������̽�
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr; // ���Ҹ��� ���������� ���ο� �����ϴ� �������̽�
	ComPtr<IDXGISwapChain> _swapChain = nullptr; // ���� ���۸��� ���� �������̽�

	// RTV(�ĸ� ���۸� �׸��� View)
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc
	D3D11_VIEWPORT _viewport = { };
	float _clearColor[4] = {15.f/255.f, 56.f / 255.f, 15.f / 255.f, 1.f};

	// Geometry
	vector<Vertex> _vertices;
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	vector<UINT> _indices;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;

	// RAS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;

	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;

private:
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;

private:
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	void CreateGeometry();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();

	void CreateSRV();
	
	void CreateConstantBuffer();

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);
};