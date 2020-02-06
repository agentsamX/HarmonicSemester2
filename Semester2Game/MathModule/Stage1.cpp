#include "Stage1.h"

Stage1::Stage1(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-10.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void Stage1::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	//you can later reInit this scene
	m_sceneReg = new entt::registry;

	//attach the register
	ECS::AttachRegister(m_sceneReg);

	//sets up aspect ratio for camera
	float aspectRatio = windowWidth / windowHeight;

	//setup main camera entity
	{
		//creates camera entity
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		//create new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<Transform>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<HorizontalScroll>(entity).SetOffset(15.f);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::HoriScrollCameraBit() || EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Player>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f,-60.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f,1.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.31 ;
		tempDef.type = b2_dynamicBody;
		tempDef.fixedRotation = true;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->CreateFixture(&fixtureDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()| EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "boxMain");
		ECS::SetIsMainPlayer(entity, true);
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(5.f, -60.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box1-1");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -60.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box1-2");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(55.f, -60.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box1-3");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, -60.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box1-4");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(17.5f, -44.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box2-1");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(42.f, -44.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box2-2");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(67.f, -44.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box2-3");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -28.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box3-1");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(55.f, -28.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box3-2");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(42.f, -12.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "box4-1");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 30);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-40.f, -82.5f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floor");
	}
ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}
void Stage1::Update()
{
	Routines();
}

void Stage1::Routines()
{
}

void Stage1::GamepadStroke(XInputController* con)
{
}

void Stage1::GamepadStick(XInputController* con)
{

}

void Stage1::GamepadTrigger(XInputController* con)
{
}

void Stage1::KeyboardHold()
{
	auto& phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	vec3 curVelo = phsBod.GetVelocity();
	if (Input::GetKey(Key::A))
	{
		phsBod.SetVelocity(vec3(-10.f, curVelo.y, 0.f));
	}
	if (Input::GetKey(Key::D))
	{
		phsBod.SetVelocity(vec3(10.f, curVelo.y, 0.f));
	}
}

void Stage1::KeyboardDown()
{
	auto& phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	vec3 curVelo = phsBod.GetVelocity();
	if (Input::GetKeyDown(Key::Space))
	{
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			phsBod.SetVelocity(vec3(curVelo.x, 30.f, 0.f));
		}
	}
}

void Stage1::KeyboardUp()
{
}

void Stage1::MouseMotion(SDL_MouseMotionEvent evnt)
{

}

void Stage1::MouseClick(SDL_MouseButtonEvent evnt)
{

}

void Stage1::MouseWheel(SDL_MouseWheelEvent evnt)
{
}

