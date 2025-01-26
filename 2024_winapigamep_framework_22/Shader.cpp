#include "pch.h"
#include "Shader.h"

Shader::Shader(ComPtr<ID3D11Device> device)
	: _device(device)
{
}

Shader::~Shader()
{
}

void Shader::LoadShaderFromFile(const wstring& path, const string& name, const string& version)
{
	_path = path;
	_name = name;

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
		_blob.GetAddressOf(),
		nullptr);

	CHECK(hr);
}
