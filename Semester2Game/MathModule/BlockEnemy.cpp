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
