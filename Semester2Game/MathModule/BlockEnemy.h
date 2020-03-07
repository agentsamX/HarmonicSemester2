#pragma once
class BlockEnemy
{
public:
	BlockEnemy();
	bool GetIsLeft();
	void SetIsLeft(bool);
	void SetInactive();
	bool GetActive();

private:
	bool isLeft = true;
	bool isActive = true;

};

