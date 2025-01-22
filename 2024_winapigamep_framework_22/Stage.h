#pragma once
#include "BackGround.h"
#include "Object.h"
#include "SceneManager.h"
#include "StageLoader.h"
#include "Scene.h"

class Object;
class StageLoader;
class Stage
{
public:
	StageLoader* stageLoader;
public:
	Stage();
	virtual ~Stage();
public:
	virtual void Init() abstract;
	void Release();
public:
	template<typename T>
	T* AddBackground(int x, int y)
	{
		XMVECTOR size = StageLoader::mapSize;

		int xStart = (SCREEN_WIDTH	- XMVectorGetX(size) * 3) / 2 + (XMVectorGetX(size)/2);
		int yStart = (SCREEN_HEIGHT - XMVectorGetY(size) * 3) / 2 + (XMVectorGetY(size)/2);

		XMVECTOR pos = 
		{ 
			xStart + XMVectorGetX(size) * x,
			yStart + XMVectorGetY(size) * y
		};
		grid[x][y] = new T;
		grid[x][y]->owner = this;
		grid[x][y]->SetSize(size);
		grid[x][y]->SetPos(pos);
		ADDOBJECT(grid[x][y], LAYER::BACKGROUND);
		return static_cast<T*>(grid[x][y]);
	}
	template<typename T>
	T* AddBackground(int x, int y, bool isPlayerArea)
	{
		AddBackground<T>(x, y);
		_playerPos = { (float)x, (float)y };
		grid[x][y]->isPlayerArea = isPlayerArea;
		return static_cast<T*>(grid[x][y]);
	}
	int GetEnemyCount() const { return _enemyCount; }
	const Background* GetPlayerArea() const
	{
		return grid[(int)XMVectorGetX(_playerPos)][(int)XMVectorGetY(_playerPos)];
	}
public:
	Background* grid[3][3];
protected:
	int _enemyCount;
	XMVECTOR _playerPos;
	bool m_isClear = false;
};