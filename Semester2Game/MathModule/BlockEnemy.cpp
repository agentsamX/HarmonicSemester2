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
	justDead = true;
}

bool BlockEnemy::GetActive()
{
	return isActive;
}

bool BlockEnemy::GetJustDead()
{
	if (justDead)
	{
		justDead = false;
		return true;
	}
	else
	{
		return false;
	}
}
