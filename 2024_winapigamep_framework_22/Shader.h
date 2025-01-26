#pragma once

enum ShaderScope 
{
	ShaderScope_None = 0,
	ShaderScope_VertexShader = (1 << 0),
	ShaderScope_PixelShader = (1 << 1),
	ShaderScope_Both = ShaderScope_VertexShader | ShaderScope_PixelShader
};

class Shader
{
public:
	Shader(ComPtr<ID3D11Device> device);
	virtual ~Shader();

	virtual void Create(const wstring& path, const string& name, const string& version) abstract;

	ComPtr<ID3DBlob> GetBlob() { return _blob; }

protected:
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version);

protected:
	wstring _path;
	string _name;
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3DBlob> _blob;
};

