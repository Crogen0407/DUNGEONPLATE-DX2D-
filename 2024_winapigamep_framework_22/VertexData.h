#pragma once

struct VertexData
{
	XMFLOAT3 position = { 0, 0, 0 };
};

struct VertexTextureData : public VertexData
{
	XMFLOAT2 uv = { 0, 0 };
	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct VertexColorData : public VertexData
{
	XMFLOAT4 color = { 0, 0, 0, 0 };
	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

