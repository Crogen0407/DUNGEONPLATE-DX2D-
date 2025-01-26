#include "pch.h"
#include "Object.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Component.h"
#include <typeinfo>
#include "Core.h"

Object::Object()
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

Object::~Object()
{
	for (Component* com : m_vecComponents)
	{
		if (com != nullptr)
			delete com;
	}
	m_vecComponents.clear();
}

void Object::Update()
{
	_transformData.offset.x = sinf(TIME) * 0.3f;
	_transformData.offset.y = 0.3f;
	_constantBuffer->CopyData(_transformData);
}

void Object::LateUpdate()
{
	for (Component* com : m_vecComponents)
	{
		if (com)
		{
			com->LateUpdate();
		}
	}
}

void Object::Render(std::shared_ptr<Pipeline> pipeline)
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

	ComponentRender(pipeline);
}

void Object::ComponentRender(std::shared_ptr<Pipeline> pipeline)
{
	for (Component* com : m_vecComponents)
	{
		if (com)
		{
			com->Render();
		}
	}
}

void Object::EnterCollision(Collider* _other)
{
}

void Object::StayCollision(Collider* _other)
{
}

void Object::ExitCollision(Collider* _other)
{
}

Object* Object::FindObject(std::wstring name, LAYER layer)
{
	Object* object = GET_SINGLE(SceneManager)->FindObject(name, layer);
	return object;
}

vector<Object*> Object::FindObjects(LAYER layer)
{
	vector<Object*> objects = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(layer);

	return objects;
}