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
	bool GetDown();
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
	void SetDown(bool);
	void SetLastRight(bool);
	bool GetKill();
	void SetKill();
	float GetKillTime();
	void AddKillTime(float);
	bool GetGoalContact();
	void SetContactingGoal(bool);
	void AddJumpTime(float);
	float GetJumpTime();
	void ResetJump();
private:
	bool dead = false;
	bool grounded=false;
	int arrNum = 0;
	bool faceLeft = false;
	bool faceRight = false;
	bool faceUp = false;
	bool faceDown = false;
	bool rooted = false;
	bool lastRight = true;
	int contactNum = 0;
	int contactLeft = 0;
	int contactRight = 0;
	float killTime = 0.f;
	float jumpTime = 0.f;
	int contactingGoal = 0;
};

