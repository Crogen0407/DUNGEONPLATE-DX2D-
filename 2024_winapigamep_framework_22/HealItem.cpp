#include "pch.h"
#include "HealItem.h"
#include "Player.h"
#include "PlayerHealthCompo.h"

HealItem::HealItem()
{
	nameText = L"���� ����";
	descriptionText = L"��� 20��ŭ ȸ���մϴ�.";
}

HealItem::~HealItem()
{
}

void HealItem::OnLevelUp(Player* player)
{
	player->GetComponent<PlayerHealthCompo>()->ApplyHeal(20);
}

void HealItem::OnUse(Player* player)
{
}
