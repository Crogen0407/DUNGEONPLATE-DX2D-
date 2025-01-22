#include "pch.h"
#include "Background.h"
#include "Collider.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Stage.h"
#include "StageLoader.h"
#include "Enemy.h"
#include "HealthCompo.h"

Background::Background()
{
	AddComponent<SpriteRenderer>();
	AddComponent<Collider>();
	_spriteRenderer = GetComponent<SpriteRenderer>();
	Collider* collider = GetComponent<Collider>();
	collider->SetSize(StageLoader::mapSize);
	collider->SetOffSetPos({ 0, 0 });
	_spriteRenderer->isRotatable = false;
	_spriteRenderer->SetTexture(L"Background", L"Texture\\Background.bmp");

	_font = CreateFont(40, 30,
		0, 0, 0, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, L"PF스타더스트 Bold");

	_enemySpawner = new EnemySpawner;
}

Background::~Background()
{
	delete(_enemySpawner);
}

void Background::Render(HDC _hdc)
{
    ComponentRender(_hdc);

	if (_maxEnemyCount- _currentEnemyCount <= 0) return;
	XMVECTOR pos = GetPos();
	XMVECTOR size = GetSize();
	::SetTextColor(_hdc, RGB(155, 188, 15));
	HFONT oldFont = static_cast<HFONT>(SelectObject(_hdc, _font));

	::SetBkMode(_hdc, 1);
	RECT rect = { XMVectorGetX(pos) - XMVectorGetX(size) / 2, XMVectorGetY(pos) - XMVectorGetY(size) / 2, XMVectorGetX(pos) + XMVectorGetX(size) / 2, XMVectorGetY(pos) + XMVectorGetY(size) / 2 };  // 출력할 영역

	::DrawText(_hdc, std::to_wstring(_maxEnemyCount- _currentEnemyCount).c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SetTextColor(_hdc, RGB(0, 0, 0));
	SelectObject(_hdc, oldFont);
}

void Background::SpawnEnemy(EnemyType enemyType, const XMVECTOR& pos)
{
	if (_currentSpawnedEnemyCount >= _maxEnemyCount)
	{
		return;
	}

	_currentSpawnedEnemyCount++;
	Enemy* enemy = _enemySpawner->SpawnEnemy(pos, enemyType);
	enemy->GetComponent<HealthCompo>()->DieEvent +=
		[this](int _)
		{
			_currentEnemyCount+=1;
			if (_maxEnemyCount - _currentEnemyCount > 0) return;
			isClear = true;
			owner->stageLoader->TryNextStage();
		};
}

void Background::SpawnEnemyByRandomPos(EnemyType enemyType)
{
	srand(time(NULL));
	int offset = 50;

	XMVECTOR size = { GetSizeX() - offset , GetSizeY() - offset };

	int ranX = 
		(rand() % (int)XMVectorGetX(size))
		- (int)XMVectorGetX(size) / 2
		+ GetPosX();
	int ranY = (rand() % (int)XMVectorGetY(size))
		- (int)XMVectorGetY(size) / 2
		+ GetPosY();
	XMVECTOR pos = { ranX, ranY };

	SpawnEnemy(enemyType, pos);
}
