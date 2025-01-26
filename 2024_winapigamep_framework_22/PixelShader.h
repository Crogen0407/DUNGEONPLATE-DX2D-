#pragma once
#include "Shader.h"

class PixelShader : public Shader
{
	using Super = Shader;
public:
	PixelShader(ComPtr<ID3D11Device> device);
	~PixelShader();

	ComPtr<ID3D11PixelShader> GetComPtr() { return _pixelShader; }

	virtual void Create(const wstring& path, const string& name, const string& version) override;

protected:
	ComPtr<ID3D11PixelShader> _pixelShader;
};

