#include "pch.h"
#include "FireBallSkill.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include "PoolManager.h"
#include <ctime>

FireBallSkill::FireBallSkill()
{
	nameText = L"���̾";
	descriptionText = L"���� 20�� ���� \n������ ���ѳ� \n���ڸ��� ����� �� \n�ִ� ������ ����. \n(���� �� �ߵ��մϴ�)";
	isActiveSkill = true;
}

FireBallSkill::~FireBallSkill()
{
}

void FireBallSkill::OnUse(Player* player)
{
}

void FireBallSkill::OnLevelUp(Player* player)
{
	Skill::OnLevelUp(player);
	player->AttackEvent.Clear();
	player->AttackEvent +=
		[ct = this, ctPlayer = player](int _)
		{
			float x = ct->GetLevel() / 10.f;
			int count = (int)((1 - cosf((x * PI) / 2.f)) * 9) + 1;
			EFireBallModeType fireBallModeType = EFireBallModeType::FireBall_L;
			switch (ct->GetLevel())
			{	
			case 1:
			case 2:
				fireBallModeType = EFireBallModeType::FireBall_S;
				break;
			case 3:
			case 4:
			case 5:
				fireBallModeType = EFireBallModeType::FireBall_M;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				fireBallModeType = EFireBallModeType::FireBall_L;
				break;
			}


			ct->Fire(ctPlayer, fireBallModeType, count);
		};
}

void FireBallSkill::Update()
{
}

void FireBallSkill::Fire(Player* player, const EFireBallModeType& fireBallModeType, const int& count)
{
	Vec2 playerPos = player->GetPos();
	for (int i = 0; i < count; i++)
	{
		Vec2 ranDir;

		srand(time(NULL)+i);
		rand(); //�̻��ϰ� ó������ ��� Ư�� ���� ���Ϸ� �ȶ�����...
		ranDir.y = (rand() / static_cast<float>(RAND_MAX)) * 2 - 1.f;
		ranDir.x = (rand() / static_cast<float>(RAND_MAX)) * 2 - 1.f;

		ranDir.Normalize();

		FireBallEffect* fireBallEffect =
			static_cast<FireBallEffect*>(POP(L"FireBallEffect", playerPos));
		fireBallEffect->SetDir(ranDir);
		fireBallEffect->SetMode(fireBallModeType);
	}
}
