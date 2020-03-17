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
	void SetArrTime(float);
	void ArrCollide();

private:
	bool frozen=false;
	float arrTime=0.f;
	int collisions = 0;
};
