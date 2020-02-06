#pragma once
class Player
{
public:
	Player();
	bool GetGrounded();
	void SetGrounded(bool);
private:
	bool grounded=false;
};

