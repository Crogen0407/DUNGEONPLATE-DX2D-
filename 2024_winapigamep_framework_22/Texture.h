#pragma once
#include "ResourceBase.h"
class Texture : public ResourceBase
{
public:
    Texture(ComPtr<ID3D11Device> device);
    ~Texture();

    ComPtr<ID3D11ShaderResourceView> GetComPtr() { return _shaderResourceView; }

    void Create(const wstring& path);

    float GetWidth() { return 0.0f; }
    float GetHeight() { return 0.0f; }

private:
    ComPtr<ID3D11Device> _device;
    ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
};

