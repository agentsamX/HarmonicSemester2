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
	}
}
void PressurePlate::PressOff()
{
	press--;
	if (press <= 0)
	{
		ECS::GetComponent<PhysicsBody>(GetGateNum()).GetBody()->GetFixtureList()->SetSensor(false);
	}
}
