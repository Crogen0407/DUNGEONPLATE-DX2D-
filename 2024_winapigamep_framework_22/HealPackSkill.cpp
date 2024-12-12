#include "pch.h"
#include "HealPackSkill.h"
#include "Player.h"
#include "PlayerHealthCompo.h"

HealPackSkill::HealPackSkill() :
	healthCompo(nullptr)
{
	nameText = L"�� ��";
	descriptionText = L"10�� ���� ���� ���� \n�� �ֽ��ϴ�.";
}

HealPackSkill::~HealPackSkill()
{
}

void HealPackSkill::OnUse(Player* player)
{
	if (healthCompo == nullptr)
		healthCompo = player->GetComponent<PlayerHealthCompo>();
	
	healthCompo->ApplyHeal(healAmount);
}

void HealPackSkill::OnLevelUp(Player* player)
{
	Skill::OnLevelUp(player);
	healAmount += 3;
}
