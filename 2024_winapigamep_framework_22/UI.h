#pragma once
#include "Core.h"
class Canvas;
class UI
{
protected:
    bool active = true;
    XMVECTOR _position;
    XMVECTOR _size;
    Canvas* _owner;
    UI* _parent;
public:
    UI() : 
        _parent(nullptr),
        _owner(nullptr)
    {
        std::shared_ptr<Graphics> graphics = GET_SINGLE(Core)->GetGraphics();
        ComPtr<ID3D11Device> device = graphics->GetDevice();
        ComPtr<ID3D11DeviceContext> deviceContext = graphics->GetDeviceContext();

        _geometry = std::make_shared<Geometry<VertexTextureData>>();
        GeometryHelper::CreateRectangle(_geometry);

        _vertexBuffer = std::make_shared<VertexBuffer>(device);
        _vertexBuffer->Create(_geometry->GetVertices());

        _indexBuffer = std::make_shared <IndexBuffer>(device);
        _indexBuffer->Create(_geometry->GetIndices());

        _vertexShader = std::make_shared<VertexShader>(device);
        _vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

        _inputLayout = std::make_shared <InputLayout>(device);
        _inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

        _pixelShader = std::make_shared<PixelShader>(device);
        _pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

        _rasterizerState = std::make_shared<RasterizerState>(device);
        _rasterizerState->Create();

        _blendState = std::make_shared<BlendState>(device);
        _blendState->Create();

        _constantBuffer = std::make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
        _constantBuffer->Create();

        _texture = std::make_shared<Texture>(device);
        _texture->Create(L"Resource\\Texture\\Background.png");

        _samplerState = std::make_shared<SamplerState>(device);
        _samplerState->Create();
    }
    virtual ~UI()
    {
        _parent = nullptr;
    }
public:
    virtual void LateUpdate() abstract;
    virtual void Render(std::shared_ptr<Pipeline> pipeline)
    {
        PipelineInfo info;
        info.inputLayout = _inputLayout;
        info.vertexShader = _vertexShader;
        info.pixelShader = _pixelShader;
        info.rasterizerState = _rasterizerState;
        info.blendState = _blendState;
        pipeline->UpdatePipeline(info);

        pipeline->SetVertexBuffer(_vertexBuffer);
        pipeline->SetIndexBuffer(_indexBuffer);
        pipeline->SetConstantBuffer(0, ShaderScope_VertexShader, _constantBuffer);
        pipeline->SetTexture(0, ShaderScope_PixelShader, _texture);
        pipeline->SetSamplerState(0, ShaderScope_PixelShader, _samplerState);

        pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
    }
public:
    const bool GetActive() const
    {
        return active;
    }
    void SetActive(const bool& active)
    {
        this->active = active;
    }
public:
    void SetOwner(Canvas *canvas)
    {
        _owner = canvas;
    }
    void SetPosAndSize(const XMVECTOR& pos, const XMVECTOR& size)
    {
        this->_position = pos;
        this->_size = size;
    }
public:
    void SetPos(XMVECTOR pos)
    {
        this->_position = pos;
    }
    void SetPosX(float x)
    {
        this->_position = XMVectorSetX(_position, x);
    }
    void SetPosY(float y)
    {
        this->_position = XMVectorSetY(_position, y);
    }
    void AddPos(const XMVECTOR& pos)
    {
        this->_position += pos;
    }
    void SetSize(XMVECTOR size)
    {
        this->_size = size;
    }
    void SetSizeX(float x)
    {
        this->_size = XMVectorSetX(this->_size, x);
    }
    void SetSizeY(float y)
    {
        this->_size = XMVectorSetY(this->_size, y);
    }
    const XMVECTOR& GetPos() const
    {
        return _position;
    }
    const float& GetPosX() const
    {
        return XMVectorGetX(_position);
    }
    const float& GetPosY() const
    {
        return XMVectorGetY(_position);
    }
    const XMVECTOR& GetSize() const
    {
        return _size;
    }
    const float& GetSizeX() const
    {
        return XMVectorGetX(_size);
    }
    const float& GetSizeY() const
    {
        return XMVectorGetY(_size);
    }
public:
    void SetParent(UI* parent)
    {
        this->_parent = parent;
    }
    UI* GetParent()
    {
        return this->_parent;
    }
private:
    ComPtr<ID3D11Device> _device;

    std::shared_ptr<Geometry<VertexTextureData>> _geometry;

    std::shared_ptr<VertexBuffer> _vertexBuffer;
    std::shared_ptr<IndexBuffer> _indexBuffer;
    std::shared_ptr<InputLayout> _inputLayout;

    std::shared_ptr<VertexShader> _vertexShader;
    std::shared_ptr<RasterizerState> _rasterizerState = nullptr;
    std::shared_ptr<PixelShader> _pixelShader;
    std::shared_ptr<Texture> _texture;
    std::shared_ptr<SamplerState> _samplerState = nullptr;
    std::shared_ptr<BlendState> _blendState = nullptr;

private:
    TransformData _transformData;
    std::shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;
};