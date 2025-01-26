#pragma once
class Collider;
class Component;
class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(std::shared_ptr<Pipeline> pipeline);

private:
	void ComponentRender(std::shared_ptr<Pipeline> pipeline);

public:
	void SetPos(XMVECTOR _vPos) { m_vPos = _vPos; }
	void AddPos(XMVECTOR pos) { m_vPos += pos; }
	void SetSize(XMVECTOR _vSize) { m_vSize = _vSize; }
	const XMVECTOR& GetPos() const { return m_vPos; }
	const float& GetPosX() const { return XMVectorGetX(m_vPos); }
	const float& GetPosY() const { return XMVectorGetY(m_vPos); }
	const XMVECTOR& GetSize() const { return m_vSize; }
	const float& GetSizeX() const { return XMVectorGetX(m_vSize); }
	const float& GetSizeY() const { return XMVectorGetY(m_vSize); }

public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
	const bool& GetIsDead() const { return m_IsDie; }
	void SetDead() { m_IsDie = true; }
	void SetActive(bool active) { activeSelf = active; }
	const bool GetActive() const { return activeSelf; }
	void SetName(wstring _name) { m_name = _name; }
	const wstring& GetName() const { return m_name; }
	static Object* FindObject(std::wstring name, LAYER layer);
	static vector<Object*> FindObjects(LAYER layer);

protected:
	bool m_IsDie;
	bool activeSelf = true;
	wstring m_name;

public:
	template<typename T>
	void AddComponent()
	{
		T* com = new T;
		com->SetOwner(this);
		m_vecComponents.push_back(com);
	}
	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* com : m_vecComponents)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}
private:
	//POINT m_ptPos;
	//POINT m_ptSize;
	XMVECTOR m_vPos;
	XMVECTOR m_vSize = { 100, 100 };
	vector<Component*> m_vecComponents;

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

	XMFLOAT3 _localPosition = { 1.f, 1.f, 1.f };
	XMFLOAT3 _localRotation = { 1.f, 1.f, 1.f };
	XMFLOAT3 _localScale = { 1.f, 1.f, 1.f };
};

