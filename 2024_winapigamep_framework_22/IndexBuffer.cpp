#include "pch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ComPtr<ID3D11Device> device)
	: _device(device)
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Create(const vector<UINT>& indices)
{
	_stride = sizeof(UINT);
	_count = static_cast<UINT>(indices.size());

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE; // 해당 버퍼를 CPU와 GPU가 접근할 수 있는지의 여부를 정해준다
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // 인덱스 버퍼를 만드는 데 사용할 것이다
	desc.ByteWidth = (UINT)(_stride * _count);

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = indices.data();

	HRESULT hr = _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
	CHECK(hr);
}
