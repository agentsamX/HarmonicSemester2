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
	void Contacted();
	void EndContacted();
	void ArrowShot(b2World*);
	void SetLeft(bool);
private:
	bool grounded=false;
	int arrNum = 0;
	bool faceLeft = false;
	int contactNum = 0;
};

