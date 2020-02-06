#include "Player.h"
#include "Scene.h"

Player::Player()
{
}

bool Player::GetGrounded()
{
	return grounded;
}

bool Player::GetLeft()
{
	return faceLeft;
}

void Player::SetGrounded(bool state)
{
	grounded = state;
}

void Player::ArrowShot(Scene* curScene)
{
	int offset;
	int veloDir;
	if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLeft())
	{
		offset = -ECS::GetComponent<Sprite>(EntityIdentifier::MainPlayer()).GetWidth() / 2;
		veloDir = -40;
	}
	else
	{
		offset = ECS::GetComponent<Sprite>(EntityIdentifier::MainPlayer()).GetWidth() / 2;
		veloDir = 40;
	}
	if (arrNum < 3)
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10,1 );
		ECS::GetComponent<Transform>(entity).SetPosition(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition()+
			vec3(offset,0,0));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = curScene->GetPhysicsWorld().CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		tempPhsBody.SetVelocity(vec3(veloDir, 0, 0));
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box1-2");
	}
	else
	{
	
	}
}

void Player::SetLeft(bool left)
{
	faceLeft = left;
}
