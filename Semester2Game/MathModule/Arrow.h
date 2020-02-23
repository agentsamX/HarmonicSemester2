#pragma once
#include "ECS.h"
class Arrow
{
public:
	Arrow();
	int GetArrowType();
	int SetArrowType();
	void SetFrozen(bool);
	bool GetFrozen();
	void AddArrTime(float);
	float GetArrTime();

private:
	bool frozen=false;
	float arrTime=0.f;
};
