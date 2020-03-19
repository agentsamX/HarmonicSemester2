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
