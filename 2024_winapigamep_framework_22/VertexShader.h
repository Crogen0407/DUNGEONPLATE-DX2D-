#pragma once
#include "Shader.h"

class VertexShader : public Shader
{
	using Super = Shader;
public:
	VertexShader(ComPtr<ID3D11Device> device);
	~VertexShader();

	ComPtr<ID3D11VertexShader> GetComPtr() { return _vertexShader; }

	virtual void Create(const wstring& path, const string& name, const string& version) override;

protected:
	ComPtr<ID3D11VertexShader> _vertexShader;
};

