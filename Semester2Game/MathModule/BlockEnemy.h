#pragma once
class BlockEnemy
{
public:
	BlockEnemy();
	bool GetIsLeft();
	void SetIsLeft(bool);
	void SetInactive();
	bool GetActive();
	bool GetJustDead();

private:
	bool isLeft = true;
	bool isActive = true;
	bool justDead = false;

};

