#include "pch.h"
#include "PixelShader.h"

PixelShader::PixelShader(ComPtr<ID3D11Device> device)
	: Super(device)
{
}

PixelShader::~PixelShader()
{
}

void PixelShader::Create(const wstring& path, const string& name, const string& version)
{
	LoadShaderFromFile(path, name, version);
	HRESULT hr = _device->CreatePixelShader(_blob->GetBufferPointer(),
		_blob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());
	CHECK(hr);
}
