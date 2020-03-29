#pragma once
class PlatformEnemy
{
public:
	PlatformEnemy();
	bool GetIsLeft();
	void SetIsLeft(bool);
	void SetInactive();
	bool GetActive();
	void SetFloating(float);
	bool GetFloating();
	float GetYLock();
	

private:
	bool isLeft = true;
	bool isActive = true;
	bool needFloat = false;
	float yPos = 0.f;

};

