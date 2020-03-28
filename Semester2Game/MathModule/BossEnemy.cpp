#include "BossEnemy.h"

BossEnemy::BossEnemy()
{
}

bool BossEnemy::GetIsLeft()
{
	return isLeft;
}

void BossEnemy::SetIsLeft(bool dire)
{
	isLeft = dire;
}

void BossEnemy::SetInactive()
{
	isActive = false;
	justDead = true;
}

bool BossEnemy::GetActive()
{
	return isActive;
}

bool BossEnemy::GetJustDead()
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

void BossEnemy::TakeDamage()
{
	if (timeSinceHit > 1.5f)
	{
		timeSinceHit = 0.f;
		health--;
		if (health == 0)
		{
			SetInactive();
		}
	}
}

void BossEnemy::AddTime(float delta)
{
	timeSinceHit += delta;
}
