#include "Player.h"

Player::Player()
{
}

bool Player::GetGrounded()
{
	return grounded;
}

void Player::SetGrounded(bool state)
{
	grounded = state;
}
