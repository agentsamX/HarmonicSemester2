#pragma once
#include "ECS.h"
class PressurePlate
{
public:
	PressurePlate();
	int GetGateNum();
	void SetGateNum(int num);
	bool GetPressure();
	void PressOn();
	void PressOff();
private:
	int gateNum;
	int press =0;
};

