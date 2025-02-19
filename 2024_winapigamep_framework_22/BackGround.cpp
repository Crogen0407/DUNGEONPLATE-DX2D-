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
#include "Core.h"

Background::Background()
{
	AddComponent<Collider>();
	_spriteRenderer = AddComponent<SpriteRenderer>();
	Collider* collider = GetComponent<Collider>();
	collider->SetSize(StageLoader::mapSize);
	collider->SetOffSetPos({ 0, 0 });
	_spriteRenderer->SetTexture(L"Background", L"Texture\\Background.png");

	GET_SINGLE(ResourceManager)->GetWriteFactory()->CreateTextFormat(
		L"PF스타더스트",
		nullptr,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		40.f,
		L"ko-KR",
		_textFormat.GetAddressOf()
	);

	_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	GET_SINGLE(Core)->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0x0f380f), _brush.GetAddressOf());

	_enemySpawner = new EnemySpawner;
}

Background::~Background()
{
	delete(_enemySpawner);
}

void Background::Render(ComPtr<ID2D1RenderTarget> renderTarget)
{
	Object::Render(renderTarget);

	if (_maxEnemyCount- _currentEnemyCount <= 0) return;
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	D2D1_RECT_F rect = { pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2 };  // 출력할 영역
	float offset = 5;
	rect.top += offset;
	rect.bottom += offset;
	wstring str = std::to_wstring(_maxEnemyCount - _currentEnemyCount).c_str();

	renderTarget->DrawTextW(
		str.c_str(),
		str.size(),
		_textFormat.Get(),
		rect,
		_brush.Get()
	);

}

void Background::SpawnEnemy(EnemyType enemyType, const Vec2& pos)
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

	Vec2 size = Vec2(( GetSize().x - offset ), (GetSize().y - offset));

	float ranX = 
		(rand() % (int)size.x)
		- (int)size.x / 2
		+ GetPos().x;
	float ranY = (rand() % (int)size.y)
		- (int)size.y / 2
		+ GetPos().y;
	Vec2 pos = { ranX, ranY };

	SpawnEnemy(enemyType, pos);
}
