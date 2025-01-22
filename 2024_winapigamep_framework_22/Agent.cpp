#include "pch.h"
#include "Agent.h"
#include "Animator.h"
#include "Object.h"

Agent::Agent()
{
	AddComponent<Animator>();
}

Agent::~Agent()
{
}

void Agent::Move(XMVECTOR dir)
{
	XMVECTOR position = GetPos();
	position += dir;

	SetPos(position);
}
