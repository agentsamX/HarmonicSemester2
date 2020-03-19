#pragma once
class PlatformEnemy
{
public:
	PlatformEnemy();
	bool GetIsLeft();
	void SetIsLeft(bool);
	void SetInactive();
	bool GetActive();

private:
	bool isLeft = true;
	bool isActive = true;

};

