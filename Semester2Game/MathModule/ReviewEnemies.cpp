#include "ReviewEnemies.h"

ReviewEnemies::ReviewEnemies(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-10.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void ReviewEnemies::InitScene(float windowWidth, float windowHeight)
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
		ECS::AttachComponent<Transform>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::CameraBit();
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 24);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f, 40.f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(8.01f, 12.01f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = .6f;
		fixtureDef.restitution = 0.f;

		b2PolygonShape dynamicBoxF;
		dynamicBoxF.SetAsBox(7.8f, 1.f, b2Vec2(0.f, -12.1f), 0);
		b2FixtureDef footSensor;
		footSensor.shape = &dynamicBoxF;
		footSensor.isSensor = true;
		footSensor.userData = (void*)1;

		b2PolygonShape dynamicBoxL;
		dynamicBoxL.SetAsBox(0.5f, 11.f, b2Vec2(-8.1f, 0.f), 0);
		b2FixtureDef leftSensor;
		leftSensor.shape = &dynamicBoxL;
		leftSensor.isSensor = true;
		leftSensor.userData = (void*)2;

		b2PolygonShape dynamicBoxR;
		dynamicBoxR.SetAsBox(0.5f, 11.f, b2Vec2(8.1f, 0.f), 0);
		b2FixtureDef rightSensor;
		rightSensor.shape = &dynamicBoxR;
		rightSensor.isSensor = true;
		rightSensor.userData = (void*)3;

		tempDef.type = b2_dynamicBody;
		tempDef.fixedRotation = true;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->CreateFixture(&fixtureDef);
		tempBody->CreateFixture(&footSensor);
		tempBody->CreateFixture(&rightSensor);
		tempBody->CreateFixture(&leftSensor);
		tempBody->SetEntityNumber(entity);
		tempBody->SetEntityType(2);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "boxMain");
		ECS::SetIsMainPlayer(entity, true);
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//sets up components
		std::string fileName = "EnemiesLevel.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 192);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 9.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "level");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//sets up components
		std::string fileName = "gaiabackground.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 192);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 6.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "BG");
	}
	//spikes
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "spike.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 175, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-63.9f, -72.6f, 10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Spikes");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "spike.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(87.8f, -72.7f, 10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Spikes");
	}
	//spikes end
	//ememies start
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<BlockEnemy>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(18.5f, 29.f, 10.f));
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
		tempBody->SetEntityType(5);
		tempBody->SetFixedRotation(true);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "blockenemytest");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<BlockEnemy>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, -52.f, 10.f));
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
		tempBody->SetEntityType(5);
		tempBody->SetFixedRotation(true);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "blockenemytest");
	}
	//enemies end
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 287, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-23.9f, 8.f, -10.f));
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
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 88.f, -10.f));
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
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 192);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-160.f, 0.f, -10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall test");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 192);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 0.f, -10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall test");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(112.f, 16.f, -10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall test");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-32.f, 16.f, -10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall test");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(39.8f, -64.9f, -10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall test");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(63.9f, -72.1f, -10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall test");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.9f, -72.1f, -10.f));
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
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall test");
	}

}
void ReviewEnemies::Update(entt::registry* reg)
{
	Routines(reg);
}

void ReviewEnemies::Routines(entt::registry* reg)
{
	if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetKill())
	{
		printf("player is dead");
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).AddKillTime(Timer::deltaTime);
	}
	else
	{
		auto viewBlockEnemy = reg->view<BlockEnemy>();
		auto viewArrow = reg->view<Arrow>();
		for (auto entity : viewBlockEnemy)
		{
			if (ECS::GetComponent<BlockEnemy>(entity).GetIsLeft() && ECS::GetComponent<BlockEnemy>(entity).GetActive())
			{
				ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(-2.f, ECS::GetComponent<PhysicsBody>(entity).GetVelocity().y, 0.f));
			}
			else if (ECS::GetComponent<BlockEnemy>(entity).GetActive())
			{
				ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(2.f, ECS::GetComponent<PhysicsBody>(entity).GetVelocity().y, 0.f));
			}
		}
		for (auto entity : viewArrow)
		{
			ECS::GetComponent<Arrow>(entity).AddArrTime(Timer::deltaTime);
			if (ECS::GetComponent<Arrow>(entity).GetFrozen())
			{
				b2Vec2 curPos = ECS::GetComponent<PhysicsBody>(entity).GetBody()->GetTransform().p;

				ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetTransform(curPos, 0);
				ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetType(b2_staticBody);
				for (b2Fixture* fixture = ECS::GetComponent<PhysicsBody>(entity).GetBody()->GetFixtureList(); fixture; fixture = fixture->GetNext())
				{
					fixture->SetRestitution(0.f);
				}
			}
			if (ECS::GetComponent<Arrow>(entity).GetArrTime() > 5)
			{
				int entNum = ECS::GetComponent<PhysicsBody>(entity).GetBody()->GetEntityNumber();
				m_physicsWorld->DestroyBody(ECS::GetComponent<PhysicsBody>(entity).GetBody());
				ECS::DestroyEntity(entNum);
				ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ArrowDestroyed();
			}
		}
	}
}

void ReviewEnemies::GamepadStroke(XInputController* con)
{
}

void ReviewEnemies::GamepadStick(XInputController* con)
{

}

void ReviewEnemies::GamepadTrigger(XInputController* con)
{
}

void ReviewEnemies::KeyboardHold()
{
	auto& phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	vec3 curVelo = phsBod.GetVelocity();
	if (Input::GetKey(Key::A))
	{
		if (!ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLeftContact())
		{
			phsBod.SetVelocity(vec3(-10.f, curVelo.y, 0.f));
		}
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetLeft(true);
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetLastRight(false);

	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetLeft(false); }
	if (Input::GetKey(Key::D))
	{
		if (!ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetRightContact())
		{
			phsBod.SetVelocity(vec3(10.f, curVelo.y, 0.f));
		}
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRight(true);
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetLastRight(true);

	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRight(false); }
	if (Input::GetKey(Key::W))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetUp(true);
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetUp(false); }
	if (Input::GetKey(Key::S))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetDown(true);
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetDown(false); }
	if (Input::GetKey(Key::Shift))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRoot(true);
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			phsBod.SetVelocity(vec3(0.f, 0.f, 0.f));
		}
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRoot(false); }


}

void ReviewEnemies::KeyboardDown()
{
	auto& phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	vec3 curVelo = phsBod.GetVelocity();
	if (Input::GetKeyDown(Key::Space))
	{
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			phsBod.SetVelocity(vec3(curVelo.x, 22.f, 0.f));
		}
	}
	if (Input::GetKeyDown(Key::F))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ArrowShot(m_physicsWorld);
	}
}

void ReviewEnemies::KeyboardUp(void)
{
}

void ReviewEnemies::MouseMotion(SDL_MouseMotionEvent evnt)
{

}

void ReviewEnemies::MouseClick(SDL_MouseButtonEvent evnt)
{

}

void ReviewEnemies::MouseWheel(SDL_MouseWheelEvent evnt)
{
}

