#pragma once
#include "ECS.h"
class Target
{
public:
	Target();
	int GetGateNum();
	void SetGateNum(int num);
	bool GetHit();
	void SetHit();
private:
	int gateNum;
	bool targHit = false;
};

