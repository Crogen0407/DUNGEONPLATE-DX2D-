#include "pch.h"
#include "IncreaseAttackSpeedSkill.h"
#include "Player.h"

IncreaseAttackSpeedSkill::IncreaseAttackSpeedSkill()
{
	nameText = L"���� �ӵ� ����";
	descriptionText = L"�� �� ���� ������ \n�� �ֽ��ϴ�.";
	isActiveSkill = true;
}

IncreaseAttackSpeedSkill::~IncreaseAttackSpeedSkill()
{
}

void IncreaseAttackSpeedSkill::OnUse(Player* player)
{
}

void IncreaseAttackSpeedSkill::OnLevelUp(Player* player)
{
	Skill::OnLevelUp(player);
	if (_originParryCoolTime == -1)
	{
		_originParryCoolTime = player->GetParryCoolTime();
		//����Ʈ �߰�
	}

	player->SetParryCoolTime(_originParryCoolTime - ((_originParryCoolTime / 2) * level / 10.f));
	
}
