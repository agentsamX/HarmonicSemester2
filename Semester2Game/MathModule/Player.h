#pragma once
#include "ECS.h"
class Scene;
class Player
{
public:
	Player();
	bool GetGrounded();
	bool GetLeft();
	void SetGrounded(bool);
	void ArrowShot(Scene*);
	void SetLeft(bool);
private:
	bool grounded=false;
	int arrNum = 0;
	bool faceLeft = false;
};

