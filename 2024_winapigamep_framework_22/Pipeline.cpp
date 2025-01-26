#include "pch.h"
#include "Pipeline.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "SamplerState.h"

Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> deviceContext)
	: _deviceContext(deviceContext)
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::UpdatePipeline(PipelineInfo info)
{
	// IA
	_deviceContext->IASetInputLayout(info.inputLayout->GetComPtr().Get());
	_deviceContext->IASetPrimitiveTopology(info.topolgy);

	// VS
	if (info.vertexShader)
		_deviceContext->VSSetShader(info.vertexShader->GetComPtr().Get(), nullptr, 0);

	// RS 
	if (info.rasterizerState)
		_deviceContext->RSSetState(info.rasterizerState->GetComPtr().Get());

	// PS
	if (info.pixelShader)
		_deviceContext->PSSetShader(info.pixelShader->GetComPtr().Get(), nullptr, 0);

	// OM
	if(info.blendState)
		_deviceContext->OMSetBlendState(info.blendState->GetComPtr().Get(), info.blendState->GetBlendFactor(), info.blendState->GetSampleMask());
}

void Pipeline::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
	UINT stride = buffer->GetStride();
	UINT offset = buffer->GetOffest();
	_deviceContext->IASetVertexBuffers(0, 1, buffer->GetComPtr().GetAddressOf(), &stride, &offset);
}

void Pipeline::SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
{
	_deviceContext->IASetIndexBuffer(buffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Pipeline::SetTexture(UINT slot, UINT scope, std::shared_ptr<Texture> texture)
{
	if (scope & ShaderScope_VertexShader)
		_deviceContext->VSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());

	if (scope & ShaderScope_PixelShader)
		_deviceContext->PSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());
}

void Pipeline::SetSamplerState(UINT slot, UINT scope, std::shared_ptr<SamplerState> samplerState)
{
	if (scope & ShaderScope_VertexShader)
		_deviceContext->VSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());

	if (scope & ShaderScope_PixelShader)
		_deviceContext->PSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());
}

void Pipeline::Draw(UINT vertexCount, UINT startVertexLocation)
{
	_deviceContext->Draw(vertexCount, startVertexLocation);
}

void Pipeline::DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT baseVertexLocation)
{
	_deviceContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}
