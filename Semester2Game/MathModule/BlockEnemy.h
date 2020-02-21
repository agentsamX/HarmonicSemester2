#pragma once
class BlockEnemy
{
public:
	BlockEnemy();
	bool GetIsLeft();
	void SetIsLeft(bool);

private:
	bool isLeft = true;
	bool isActive = true;

};

