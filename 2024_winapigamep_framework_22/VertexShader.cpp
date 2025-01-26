#include "pch.h"
#include "VertexShader.h"

VertexShader::VertexShader(ComPtr<ID3D11Device> device)
	: Super(device)
{
}

VertexShader::~VertexShader()
{
}

void VertexShader::Create(const wstring& path, const string& name, const string& version)
{
	LoadShaderFromFile(path, name, version);
	HRESULT hr = _device->CreateVertexShader(_blob->GetBufferPointer(),
		_blob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
	CHECK(hr);
}
