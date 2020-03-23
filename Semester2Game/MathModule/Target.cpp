#include "Target.h"

Target::Target()
{
}

int Target::GetGateNum()
{
	return gateNum;
}

void Target::SetGateNum(int num)
{
	gateNum = num;
}

bool Target::GetHit()
{
	return targHit;
}

void Target::SetHit()
{
	targHit = true;
	ECS::GetComponent<PhysicsBody>(GetGateNum()).GetBody()->GetFixtureList()->SetSensor(true);
	ECS::GetComponent<AnimationController>(GetGateNum()).SetActiveAnim(1);
	
}
