#include "pch.h"
#include "IncreaseMoveSpeedSkill.h"
#include "Player.h"

IncreaseMoveSpeedSkill::IncreaseMoveSpeedSkill()
{
	nameText = L"�̵� �ӵ� ����";
	descriptionText = L"������!!!\n���� �÷��ô�!!";
	isActiveSkill = true;
}

IncreaseMoveSpeedSkill::~IncreaseMoveSpeedSkill()
{
}

void IncreaseMoveSpeedSkill::OnUse(Player* player)
{
}

void IncreaseMoveSpeedSkill::OnLevelUp(Player* player)
{
	Skill::OnLevelUp(player);
	if (_playerOriginMoveSpeed == -1)
	{
		_playerOriginMoveSpeed = player->GetMoveSpeed();
		//����Ʈ �ֱ�
	}

	_increasePercent += 0.15f;

	player->SetMoveSpeed(_playerOriginMoveSpeed + _playerOriginMoveSpeed * _increasePercent);
}