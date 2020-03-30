#include "PlatformEnemy.h"
PlatformEnemy::PlatformEnemy()
{
}

bool PlatformEnemy::GetIsLeft()
{
	return isLeft;
}

void PlatformEnemy::SetIsLeft(bool dire)
{
	isLeft = dire;
}

void PlatformEnemy::SetInactive()
{
	isActive = false;
}

bool PlatformEnemy::GetActive()
{
	return isActive;
}

void PlatformEnemy::SetFloating(float y)
{
	yPos = y;
	needFloat = true;
}

bool PlatformEnemy::GetFloating()
{
	return needFloat;
}

float PlatformEnemy::GetYLock()
{
	return yPos;
}
