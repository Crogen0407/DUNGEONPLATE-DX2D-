#include "pch.h"
#include "SkillManager.h"
#include "TimeManager.h"
#include "Skill.h"
#include "Item.h"
#include "HealPackSkill.h"
#include "IncreaseAttackSpeedSkill.h"
#include "IncreaseMoveSpeedSkill.h"
#include "DashSkill.h"
#include "FireBallSkill.h"
#include "HealItem.h"

SkillManager::~SkillManager()
{
	for (auto skill : skills)
	{
		delete skill.second;
	}
}

void SkillManager::Init()
{
	//Skills
	AddSkill(ESkillType::DashSkill,					static_cast<Skill*>(new DashSkill));
	AddSkill(ESkillType::HealPack,					static_cast<Skill*>(new HealPackSkill));
	AddSkill(ESkillType::IncreaseAttackSpeed,		static_cast<Skill*>(new IncreaseAttackSpeedSkill));
	AddSkill(ESkillType::IncreaseMoveSpeed,			static_cast<Skill*>(new IncreaseMoveSpeedSkill));
	AddSkill(ESkillType::FireBall,					static_cast<Skill*>(new FireBallSkill));

	//Items
	AddSkill(ESkillType::HealItem,					static_cast<Item*>(new HealItem));
}

void SkillManager::Update()
{
	for (auto skill : skills)
	{
		Skill* origin = skill.second;
		//0������ ������ ���� ���� �����̴�.
		if (origin->GetLevel() == 0) continue;
		origin->Update();
		//��Ƽ�� ��ų�� Ȱ��ȭ�Ǿ� �ִ� ���� ����Ǵ� ���̱� ������
		//�������� ���� �����ϸ� �ȴ�.
		if (origin->IsActiveSkill()) continue;

		//��Ÿ�� ����
		origin->curDelayTime += fDT;
		if (origin->curDelayTime > origin->maxDelayTime)
		{
			//��Ÿ�� �� ���Ҵٸ� ��ų ����
			origin->curDelayTime = 0.f;
			origin->OnUse(player);
		}
		origin->DelayTimeEvent.Invoke(origin->curDelayTime/ origin->maxDelayTime);
	}
}

void SkillManager::Release()
{
	for (auto skill : skills)
	{
		skill.second->SetEnable(false);
		skill.second->SetLevel(0);
	}
}

const vector<Skill*> SkillManager::GetRandomSkills()
{
	int arr[(UINT)ESkillType::LAST];
	int lastNum = 0;
	for (int i = 0; i < (UINT)ESkillType::LAST; i++)
	{
		arr[i] = i;
		lastNum = i;
	}

	srand((unsigned int)time(NULL));
	
	for (int i = 0; i < 30; i++)
	{
		int dest = rand() % (UINT)ESkillType::LAST;
		int sour = rand() % (UINT)ESkillType::LAST;

		int temp = arr[dest];
		arr[dest] = arr[sour];
		arr[sour] = temp;
	}

	vector<Skill*> output;

	//���� ����
	for (int i = 0; i < (UINT)ESkillType::LAST; i++)
	{
		if (output.size() >= 3) break;
		if (skills[(ESkillType)arr[i]]->GetLevel() >= 10) continue;
		output.push_back(skills[(ESkillType)arr[i]]);
	}

	return output;
}

void SkillManager::AddSkill(ESkillType type, Skill* skill)
{
	skills[type] = skill;
}

void SkillManager::LevelUpSkill(ESkillType type)
{
	Skill* skill = skills[type];
	//Ȱ��ȭ�� �ȵǾ� �ִٸ�
	if (skill->GetEnable() == false)
	{
		skill->SetEnable(true);
	}
	skill->OnLevelUp(player);
	skill->OnUse(player);
}