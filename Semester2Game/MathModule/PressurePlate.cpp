#include "PressurePlate.h"
PressurePlate::PressurePlate()
{
}

int PressurePlate::GetGateNum()
{
	return gateNum;
}

void PressurePlate::SetGateNum(int num)
{
	gateNum = num;
}

bool PressurePlate::GetPressure()
{
	if (press > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PressurePlate::PressOn()
{
	press++;
	if (press > 0)
	{
			ECS::GetComponent<PhysicsBody>(GetGateNum()).GetBody()->GetFixtureList()->SetSensor(true);
			ECS::GetComponent<AnimationController>(GetGateNum()).SetActiveAnim(1);
			ECS::GetComponent<AnimationController>(GetGateNum()).GetAnimation(1).Reset();
	}
}
void PressurePlate::PressOff()
{
	press--;
	if (press <= 0)
	{
		ECS::GetComponent<PhysicsBody>(GetGateNum()).GetBody()->GetFixtureList()->SetSensor(false);
		ECS::GetComponent<AnimationController>(GetGateNum()).SetActiveAnim(0);
		ECS::GetComponent<AnimationController>(GetGateNum()).GetAnimation(0).Reset();
	}
}
