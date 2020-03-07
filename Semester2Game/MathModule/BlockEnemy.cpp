#include "BlockEnemy.h"

BlockEnemy::BlockEnemy()
{
}

bool BlockEnemy::GetIsLeft()
{
	return isLeft;
}

void BlockEnemy::SetIsLeft(bool dire)
{
	isLeft = dire;
}

void BlockEnemy::SetInactive()
{
	isActive = false;
}

bool BlockEnemy::GetActive()
{
	return isActive;
}
