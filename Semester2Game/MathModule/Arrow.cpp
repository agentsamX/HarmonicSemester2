#include "Arrow.h"
#include "Scene.h"

Arrow::Arrow()
{
}

int Arrow::GetArrowType()
{
	return 0;
}

int Arrow::SetArrowType()
{
	return 0;
}

void Arrow::SetFrozen(bool fro)
{
	frozen = fro;
}

bool Arrow::GetFrozen()
{
	return frozen;
}

void Arrow::AddArrTime(float delta)
{
	arrTime += delta;
}

float Arrow::GetArrTime()
{
	return arrTime;
}

void Arrow::SetArrTime(float t)
{
	arrTime = t;
}

void Arrow::ArrCollide()
{
	collisions++;
	/*if (collisions >= 6)
	{
		SetArrTime(4.9f);
	}*/
	//arrows collide with player many times when shot, so I will deal with this later
}
