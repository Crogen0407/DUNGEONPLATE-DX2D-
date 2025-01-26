#include "pch.h"
#include "SamplerState.h"

SamplerState::SamplerState(ComPtr<ID3D11Device> device)
	: _device(device)
{	
}

SamplerState::~SamplerState()
{
}

void SamplerState::Create()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0.f;
	desc.MaxAnisotropy = 2;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;
	desc.MaxLOD = FLT_MAX;       //밉맵의 범위상한치 MaxLod >= MinLod이어야 하며         
	desc.MinLOD = -FLT_MAX;      //밉맵의 범위하한치 0이 최대이며 가장 세부적인 밉맵 레벨을 나타낸다

	_device->CreateSamplerState(&desc, _samplerState.GetAddressOf());

}
