#pragma once
class InputLayout;
class VertexShader;
class PixelShader;
class RasterizerState;
class BlendState;
class VertexBuffer;
class IndexBuffer;
class Texture;
class SamplerState;

#include "Shader.h"
#include "ConstantBuffer.h"

struct PipelineInfo
{
	std::shared_ptr<InputLayout> inputLayout;
	std::shared_ptr<VertexShader> vertexShader;
	std::shared_ptr<PixelShader> pixelShader;
	std::shared_ptr<RasterizerState> rasterizerState;
	std::shared_ptr<BlendState> blendState;
	D3D11_PRIMITIVE_TOPOLOGY topolgy = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{
public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer);

	template<typename T>
	void SetConstantBuffer(UINT slot, UINT scope, std::shared_ptr<ConstantBuffer<T>> buffer)
	{
		if (scope & ShaderScope_VertexShader)
			_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

		if (scope & ShaderScope_PixelShader)
			_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());
	}

	void SetTexture(UINT slot, UINT scope, std::shared_ptr<Texture> texture);
	void SetSamplerState(UINT slot, UINT scope, std::shared_ptr<SamplerState> samplerState);

	void Draw(UINT vertexCount, UINT startVertexLocation);
	void DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT baseVertexLocation);

private:
	ComPtr<ID3D11DeviceContext> _deviceContext;
};

