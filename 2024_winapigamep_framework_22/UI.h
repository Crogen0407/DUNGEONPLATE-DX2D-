#pragma once
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

    }
    virtual ~UI()
    {
        _parent = nullptr;
    }
public:
    virtual void LateUpdate() abstract;
    virtual void Render(HDC _hdc) abstract;
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
};