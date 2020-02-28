#pragma once
#include "ECS.h"
class Scene;
class Player
{
public:
	Player();
	bool GetGrounded();
	bool GetLeftContact();
	bool GetRightContact();
	bool GetLeft();
	bool GetRight();
	bool GetUp();
	bool GetRooted();
	bool GetLastRight();
	void SetGrounded(bool);
	void Contacted();
	void ContactLeft();
	void ContactRight();
	void EndLeft();
	void EndRight();
	void EndContacted();
	void ArrowShot(b2World*);
	void ArrowDestroyed();
	void SetLeft(bool);
	void SetRight(bool);
	void SetUp(bool);
	void SetRoot(bool);
	void SetLastRight(bool);
private:
	bool grounded=false;
	int arrNum = 0;
	bool faceLeft = false;
	bool faceRight = false;
	bool faceUp = false;
	bool rooted = false;
	bool lastRight = true;
	int contactNum = 0;
	int contactLeft = 0;
	int contactRight = 0;
};

