#include "Stage5.h"

Stage5::Stage5(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-10.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void Stage5::InitScene(float windowWidth, float windowHeight)
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
		ECS::AttachComponent<VerticalScroll>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetOffset(10.f);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::CameraBit() || EntityIdentifier::VertScrollCameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	} 
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Arrow.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-180.f, 50.f, 100.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "UIArrow1");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Arrow.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-180.f, 70.f, 100.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "UIArrow2");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Arrow.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-180.f, 90.f, 100.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "UIArrow3");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		///Sets up components
		std::string Arm = "Arm.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(Arm);
		//Arm Idle
		animController.AddAnimation(Animation());
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0.f, 160.f), vec2(150.f, 10.f));
		anim.SetRepeating(false);
		anim.SetSecPerFrame(0.1667f);
		//Arm Shoot
		animController.AddAnimation(Animation());
		auto& anim1 = animController.GetAnimation(1);
		anim1.AddFrame(vec2(0.f, 160.f), vec2(150.f, 10.f));
		anim1.AddFrame(vec2(153.f, 160.f), vec2(302.f, 10.f));
		anim1.AddFrame(vec2(330.f, 160.f), vec2(480.f, 10.f));
		anim1.SetRepeating(false);
		anim1.SetSecPerFrame(0.05);
		//transparent
		animController.AddAnimation(Animation());
		auto& anim2 = animController.GetAnimation(2);
		anim2.AddFrame(vec2(0.f, 0.f), vec2(1.f, 1.f));

		animController.SetActiveAnim(2);
		ECS::GetComponent<Sprite>(entity).LoadSprite(Arm, 16, 16, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -447.7f, 6.f));
		ECS::GetComponent<Transform>(entity).SetRotationAngleZ(PI / 2);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Arm");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string sheet = "Character.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(sheet);

		//idleRight
		animController.AddAnimation(Animation());
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0.f, 320.f), vec2(160.f, 80.f));
		anim.AddFrame(vec2(160.f, 320.f), vec2(320.f, 80.f));
		anim.SetRepeating(true);
		anim.SetSecPerFrame(0.1667f);
		//idleLeft
		animController.AddAnimation(Animation());
		auto& anim1 = animController.GetAnimation(1);
		anim1.AddFrame(vec2(160.f, 320.f), vec2(0.f, 80.f));
		anim1.AddFrame(vec2(320.f, 320.f), vec2(160.f, 80.f));
		anim1.SetRepeating(true);
		anim1.SetSecPerFrame(0.1667f);
		//idleArmlessLeft
		animController.AddAnimation(Animation());
		auto& anim2 = animController.GetAnimation(2);
		anim2.AddFrame(vec2(480.f, 320.f), vec2(320.f, 80.f));
		anim2.SetRepeating(true);
		anim2.SetSecPerFrame(0.1667f);
		//idleArmlessLeft
		animController.AddAnimation(Animation());
		auto& anim3 = animController.GetAnimation(3);
		anim3.AddFrame(vec2(320.f, 320.f), vec2(480.f, 80.f));
		anim3.SetRepeating(true);
		anim3.SetSecPerFrame(0.1667f);
		//walkRight
		animController.AddAnimation(Animation());
		auto& anim4 = animController.GetAnimation(4);
		anim4.AddFrame(vec2(0.f, 960.f), vec2(160.f, 720.f));
		anim4.AddFrame(vec2(160.f, 960.f), vec2(320.f, 720.f));
		anim4.AddFrame(vec2(320.f, 960.f), vec2(480.f, 720.f));
		anim4.AddFrame(vec2(480.f, 960.f), vec2(640.f, 720.f));
		anim4.AddFrame(vec2(640.f, 960.f), vec2(800.f, 720.f));
		anim4.SetRepeating(true);
		anim4.SetSecPerFrame(0.1667f);
		//walkLeft
		animController.AddAnimation(Animation());
		auto& anim5 = animController.GetAnimation(5);
		anim5.AddFrame(vec2(160.f, 960.f), vec2(0.f, 720.f));
		anim5.AddFrame(vec2(320.f, 960.f), vec2(160.f, 720.f));
		anim5.AddFrame(vec2(480.f, 960.f), vec2(320.f, 720.f));
		anim5.AddFrame(vec2(640.f, 960.f), vec2(480.f, 720.f));
		anim5.AddFrame(vec2(800.f, 960.f), vec2(640.f, 720.f));
		anim5.SetRepeating(true);
		anim5.SetSecPerFrame(0.1667f);
		//armlessWalkLeft
		animController.AddAnimation(Animation());
		auto& anim6 = animController.GetAnimation(6);
		anim6.AddFrame(vec2(960.f, 960.f), vec2(800.f, 720.f));
		anim6.AddFrame(vec2(1120.f, 960.f), vec2(960.f, 720.f));
		anim6.AddFrame(vec2(1280.f, 960.f), vec2(1120.f, 720.f));
		anim6.AddFrame(vec2(1440.f, 960.f), vec2(1280.f, 720.f));
		anim6.AddFrame(vec2(1600.f, 960.f), vec2(1440.f, 720.f));
		anim6.SetRepeating(true);
		anim6.SetSecPerFrame(0.1667f);
		//armlessWalkRight
		animController.AddAnimation(Animation());
		auto& anim7 = animController.GetAnimation(7);
		anim7.AddFrame(vec2(800.f, 960.f), vec2(960.f, 720.f));
		anim7.AddFrame(vec2(960.f, 960.f), vec2(1120.f, 720.f));
		anim7.AddFrame(vec2(1120.f, 960.f), vec2(1280.f, 720.f));
		anim7.AddFrame(vec2(1280.f, 960.f), vec2(1440.f, 720.f));
		anim7.AddFrame(vec2(1440.f, 960.f), vec2(1600.f, 720.f));
		anim7.SetRepeating(true);
		anim7.SetSecPerFrame(0.1667f);
		//jump right
		animController.AddAnimation(Animation());
		auto& anim8 = animController.GetAnimation(8);
		anim8.AddFrame(vec2(0.f, 1280.f), vec2(160.f, 1040.f));
		anim8.AddFrame(vec2(160.f, 1280.f), vec2(320.f, 1040.f));
		anim8.AddFrame(vec2(372.f, 1280.f), vec2(532.f, 1040.f));
		anim8.SetRepeating(false);
		anim8.SetSecPerFrame(0.05);
		//jump left
		animController.AddAnimation(Animation());
		auto& anim9 = animController.GetAnimation(9);
		anim9.AddFrame(vec2(160.f, 1280.f), vec2(0.f, 1040.f));
		anim9.AddFrame(vec2(320.f, 1280.f), vec2(160.f, 1040.f));
		anim9.AddFrame(vec2(532.f, 1280.f), vec2(372.f, 1040.f));
		anim9.SetRepeating(false);
		anim9.SetSecPerFrame(0.05);
		//shoot right
		animController.AddAnimation(Animation());
		auto& anim10 = animController.GetAnimation(10);
		anim10.AddFrame(vec2(0.f, 640.f), vec2(160.f, 400.f));
		anim10.AddFrame(vec2(160.f, 640.f), vec2(320.f, 400.f));
		anim10.AddFrame(vec2(320.f, 640.f), vec2(480.f, 400.f));
		anim10.SetRepeating(false);
		anim10.SetSecPerFrame(0.05);
		//shoot left
		animController.AddAnimation(Animation());
		auto& anim11 = animController.GetAnimation(11);
		anim11.AddFrame(vec2(160.f, 640.f), vec2(0.f, 400.f));
		anim11.AddFrame(vec2(320.f, 640.f), vec2(160.f, 400.f));
		anim11.AddFrame(vec2(480.f, 640.f), vec2(320.f, 400.f));
		anim11.SetRepeating(false);
		anim11.SetSecPerFrame(0.05);
		//death
		animController.AddAnimation(Animation());
		auto& anim12 = animController.GetAnimation(12);
		anim12.AddFrame(vec2(20.f, 1600.f), vec2(260.f, 1370.f));
		anim12.AddFrame(vec2(330.f, 1600.f), vec2(570.f, 1370.f));
		anim12.AddFrame(vec2(650.f, 1600.f), vec2(890.f, 1370.f));
		anim12.AddFrame(vec2(970.f, 1600.f), vec2(1210.f, 1370.f));
		anim12.AddFrame(vec2(1280.f, 1600.f), vec2(1520.f, 1370.f));
		anim12.SetRepeating(false);
		anim12.SetSecPerFrame(0.1667f);


		animController.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity).LoadSprite(sheet, 16, 24, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, 232.f, 10.f));
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
		dynamicBoxF.SetAsBox(7.8f, 0.5f, b2Vec2(0.f, -12.1f), 0);
		b2FixtureDef footSensor;
		footSensor.shape = &dynamicBoxF;
		footSensor.isSensor = true;
		footSensor.userData = (void*)1;

		b2PolygonShape dynamicBoxH;
		dynamicBoxH.SetAsBox(7.8f, 0.5f, b2Vec2(0.f, 12.1f), 0);
		b2FixtureDef headSensor;
		headSensor.shape = &dynamicBoxH;
		headSensor.isSensor = true;
		headSensor.userData = (void*)4;

		b2PolygonShape dynamicBoxL;
		dynamicBoxL.SetAsBox(1.f, 11.f, b2Vec2(-8.1f, 0.f), 0);
		b2FixtureDef leftSensor;
		leftSensor.shape = &dynamicBoxL;
		leftSensor.isSensor = true;
		leftSensor.userData = (void*)2;

		b2PolygonShape dynamicBoxR;
		dynamicBoxR.SetAsBox(1.f, 11.f, b2Vec2(8.1f, 0.f), 0);
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
		tempBody->CreateFixture(&headSensor);
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
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 288.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(336), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "roof");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "JungleLevel2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 592);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 9.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		//tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		//	vec2(0.f, 0.f),
		//	true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "LevelBackground");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//sets up components
		std::string fileName = "gaiabackground.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 205);
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

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(592),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "wall");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(592),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "wall");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(24.f, 208.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(256), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-48.f, 272.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-144.f, 128.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(80),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, 120.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(64),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-8.f, 128.f, -10.f));
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
		tempBody->SetEntityType(6);
		tempPhsBody = PhysicsBody(tempBody, float(224), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "spikes");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(112.f, 120.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(64),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-8.f, 96.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(224), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f, 80.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(24.f, 8.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(256), float(32),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(112.f, 32.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-32.f, 32.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-136.f, -72.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(32), float(64),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f, -72.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(80), float(32),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(8.f, -80.f, -10.f));
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
		tempBody->SetEntityType(6);
		tempPhsBody = PhysicsBody(tempBody, float(96), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "spikes");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(88.f, -80.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(64), float(48),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(112.f, -136.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(64),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-24.f, -144.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(256), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, -144.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(14), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(144.f, -96.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(14), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, -224.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(48), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(88.f, -240.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(32), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(64.f, -256.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(40.f, -272.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(32), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(8.f, -256.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(32), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-16.f, -232.f, -10.f));
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
		tempBody->SetEntityType(1);
		tempPhsBody = PhysicsBody(tempBody, float(16), float(32),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "stick wall");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-40.f, -208.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(32), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-48.f, -240.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(48),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floors");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-72.f, -272.f, -10.f));
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
		tempBody->SetEntityType(6);
		tempPhsBody = PhysicsBody(tempBody, float(32), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "spikes");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-96.f, -248.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(32),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-96.f, -168.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(32),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(16.f, -160.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(16.f, -192.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(14.5), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(40.f, -208.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(31.5), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(64.f, -192.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, -176.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(96.f, -160.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(32.f, -176.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(16), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, -176.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(48), float(16),
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, -240.f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(48), float(16),
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
		ECS::AttachComponent<Gate>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string Door = "DoorOpening.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(Door);
		//Adds first animation
		animController.AddAnimation(Animation());
		//Sets active animation
		animController.SetActiveAnim(0);

		//gets first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));
		anim.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
		anim.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
		anim.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
		anim.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
		anim.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
		anim.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
		anim.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
		anim.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
		anim.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
		anim.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
		anim.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
		anim.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
		anim.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
		anim.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
		anim.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
		anim.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
		anim.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
		anim.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
		anim.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
		anim.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
		anim.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
		anim.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
		anim.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
		anim.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));

		//Makes it repeat
		anim.SetRepeating(false);
		//Sets the time between frames
		anim.SetSecPerFrame(0.05f);
		animController.AddAnimation(Animation());

		//gets first animation
		auto& anim2 = animController.GetAnimation(1);
		anim2.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));
		anim2.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
		anim2.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
		anim2.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
		anim2.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
		anim2.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
		anim2.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
		anim2.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
		anim2.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
		anim2.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
		anim2.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
		anim2.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
		anim2.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
		anim2.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
		anim2.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
		anim2.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
		anim2.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
		anim2.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
		anim2.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
		anim2.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
		anim2.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
		anim2.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
		anim2.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
		anim2.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
		anim2.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));

		//Makes it repeat
		anim2.SetRepeating(false);
		//Sets the time between frames
		anim2.SetSecPerFrame(0.05f);


		ECS::GetComponent<Sprite>(entity).LoadSprite(Door, 16, 48, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-32.f, 176.f, 8.f));
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetEntityNumber(entity);
		tempBody->SetEntityType(0);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(47.5),
			vec2(0.f, 0.f),
			false);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Gate");


		auto entity2 = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::AttachComponent<PhysicsBody>(entity2);
		ECS::AttachComponent<Target>(entity2);
		//sets up components
		std::string fileName2 = "TargetL.png";
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 9, 16);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-44.f, 192.f, 8.f));
		ECS::GetComponent<Target>(entity2).SetGateNum(entity);
		auto& tempTrans2 = ECS::GetComponent<Transform>(entity2);
		auto& tempSpr2 = ECS::GetComponent<Sprite>(entity2);
		auto& tempPhsBody2 = ECS::GetComponent<PhysicsBody>(entity2);
		b2Body* tempBody2;
		b2BodyDef tempDef2;
		tempDef2.type = b2_kinematicBody;
		tempDef2.position.Set(float32(tempTrans2.GetPositionX()), float32(tempTrans2.GetPositionY()));
		tempBody2 = m_physicsWorld->CreateBody(&tempDef2);
		tempBody2->SetEntityNumber(entity2);
		tempBody2->SetEntityType(7);
		tempPhsBody2 = PhysicsBody(tempBody2, float(tempSpr2.GetWidth()), float(tempSpr2.GetHeight()),
			vec2(4.f, 0.f),
			false);
		//sets up the identifier
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Target");
	}

	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Gate>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Door = "DoorOpening.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Door);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));
	anim.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(false);
	//Sets the time between frames
	anim.SetSecPerFrame(0.05f);
	animController.AddAnimation(Animation());

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));
	anim2.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim2.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim2.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim2.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim2.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim2.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim2.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim2.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim2.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim2.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim2.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim2.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim2.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim2.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim2.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim2.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));

	//Makes it repeat
	anim2.SetRepeating(false);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.05f);


	ECS::GetComponent<Sprite>(entity).LoadSprite(Door, 16, 48, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(48.f, 176.f, 8.f));
	auto& tempTrans = ECS::GetComponent<Transform>(entity);
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_kinematicBody;
	tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetEntityNumber(entity);
	tempBody->SetEntityType(0);
	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(47.5),
		vec2(0.f, 0.f),
		false);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Gate");


	auto entity2 = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity2);
	ECS::AttachComponent<Transform>(entity2);
	ECS::AttachComponent<PhysicsBody>(entity2);
	ECS::AttachComponent<Target>(entity2);
	//sets up components
	std::string fileName2 = "TargetL.png";
	ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 9, 16);
	ECS::GetComponent<Transform>(entity2).SetPosition(vec3(36.f, 176.f, 8.f));
	ECS::GetComponent<Target>(entity2).SetGateNum(entity);
	auto& tempTrans2 = ECS::GetComponent<Transform>(entity2);
	auto& tempSpr2 = ECS::GetComponent<Sprite>(entity2);
	auto& tempPhsBody2 = ECS::GetComponent<PhysicsBody>(entity2);
	b2Body* tempBody2;
	b2BodyDef tempDef2;
	tempDef2.type = b2_kinematicBody;
	tempDef2.position.Set(float32(tempTrans2.GetPositionX()), float32(tempTrans2.GetPositionY()));
	tempBody2 = m_physicsWorld->CreateBody(&tempDef2);
	tempBody2->SetEntityNumber(entity2);
	tempBody2->SetEntityType(7);
	tempPhsBody2 = PhysicsBody(tempBody2, float(tempSpr2.GetWidth()), float(tempSpr2.GetHeight()),
		vec2(4.f, 0.f),
		false);
	//sets up the identifier
	unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity2, bitHolder2, "Target");
	}

	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Gate>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Door = "DoorOpening.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Door);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));
	anim.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(false);
	//Sets the time between frames
	anim.SetSecPerFrame(0.05f);
	animController.AddAnimation(Animation());

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));
	anim2.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim2.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim2.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim2.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim2.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim2.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim2.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim2.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim2.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim2.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim2.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim2.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim2.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim2.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim2.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim2.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));

	//Makes it repeat
	anim2.SetRepeating(false);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.05f);


	ECS::GetComponent<Sprite>(entity).LoadSprite(Door, 16, 48, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(64.f, -32.f, 8.f));
	auto& tempTrans = ECS::GetComponent<Transform>(entity);
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_kinematicBody;
	tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetEntityNumber(entity);
	tempBody->SetEntityType(0);
	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(47.5),
		vec2(0.f, 0.f),
		false);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Gate");


	auto entity2 = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity2);
	ECS::AttachComponent<Transform>(entity2);
	ECS::AttachComponent<PhysicsBody>(entity2);
	ECS::AttachComponent<Target>(entity2);
	//sets up components
	std::string fileName2 = "TargetL.png";
	ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 9, 16);
	ECS::GetComponent<Transform>(entity2).SetPosition(vec3(44.f, -32.f, 8.f));
	ECS::GetComponent<Target>(entity2).SetGateNum(entity);
	auto& tempTrans2 = ECS::GetComponent<Transform>(entity2);
	auto& tempSpr2 = ECS::GetComponent<Sprite>(entity2);
	auto& tempPhsBody2 = ECS::GetComponent<PhysicsBody>(entity2);
	b2Body* tempBody2;
	b2BodyDef tempDef2;
	tempDef2.type = b2_kinematicBody;
	tempDef2.position.Set(float32(tempTrans2.GetPositionX()), float32(tempTrans2.GetPositionY()));
	tempBody2 = m_physicsWorld->CreateBody(&tempDef2);
	tempBody2->SetEntityNumber(entity2);
	tempBody2->SetEntityType(7);
	tempPhsBody2 = PhysicsBody(tempBody2, float(tempSpr2.GetWidth()), float(tempSpr2.GetHeight()),
		vec2(4.f, 0.f),
		false);
	//sets up the identifier
	unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity2, bitHolder2, "Target");
	}

	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Gate>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Door = "DoorOpening.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Door);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));
	anim.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(false);
	//Sets the time between frames
	anim.SetSecPerFrame(0.05f);
	animController.AddAnimation(Animation());

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));
	anim2.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim2.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim2.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim2.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim2.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim2.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim2.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim2.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim2.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim2.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim2.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim2.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim2.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim2.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim2.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim2.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));

	//Makes it repeat
	anim2.SetRepeating(false);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.05f);


	ECS::GetComponent<Sprite>(entity).LoadSprite(Door, 16, 48, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-64.f, -32.f, 8.f));
	auto& tempTrans = ECS::GetComponent<Transform>(entity);
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_kinematicBody;
	tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetEntityNumber(entity);
	tempBody->SetEntityType(0);
	tempPhsBody = PhysicsBody(tempBody, float(16), float(47.5),
		vec2(0.f, 0.f),
		false);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Gate");


	auto entity2 = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity2);
	ECS::AttachComponent<Transform>(entity2);
	ECS::AttachComponent<PhysicsBody>(entity2);
	ECS::AttachComponent<Target>(entity2);
	//sets up components
	std::string fileName2 = "TargetL.png";
	ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 9, 16);
	ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-84.f, -16.f, 8.f));
	ECS::GetComponent<Target>(entity2).SetGateNum(entity);
	auto& tempTrans2 = ECS::GetComponent<Transform>(entity2);
	auto& tempSpr2 = ECS::GetComponent<Sprite>(entity2);
	auto& tempPhsBody2 = ECS::GetComponent<PhysicsBody>(entity2);
	b2Body* tempBody2;
	b2BodyDef tempDef2;
	tempDef2.type = b2_kinematicBody;
	tempDef2.position.Set(float32(tempTrans2.GetPositionX()), float32(tempTrans2.GetPositionY()));
	tempBody2 = m_physicsWorld->CreateBody(&tempDef2);
	tempBody2->SetEntityNumber(entity2);
	tempBody2->SetEntityType(7);
	tempPhsBody2 = PhysicsBody(tempBody2, float(tempSpr2.GetWidth()), float(tempSpr2.GetHeight()),
		vec2(4.f, 0.f),
		false);
	//sets up the identifier
	unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity2, bitHolder2, "Target");
	}
	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Gate>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Door = "DoorOpening.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Door);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));
	anim.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(false);
	//Sets the time between frames
	anim.SetSecPerFrame(0.05f);
	animController.AddAnimation(Animation());

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));
	anim2.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim2.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim2.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim2.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim2.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim2.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim2.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim2.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim2.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim2.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim2.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim2.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim2.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim2.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim2.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim2.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));

	//Makes it repeat
	anim2.SetRepeating(false);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.05f);


	ECS::GetComponent<Sprite>(entity).LoadSprite(Door, 16, 48, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-48.f, 240.f, 8.f));
	auto& tempTrans = ECS::GetComponent<Transform>(entity);
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_kinematicBody;
	tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetEntityNumber(entity);
	tempBody->SetEntityType(0);
	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f),
		false);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Gate");


	auto entity2 = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity2);
	ECS::AttachComponent<Transform>(entity2);
	ECS::AttachComponent<PhysicsBody>(entity2);
	ECS::AttachComponent<PressurePlate>(entity2);
	//sets up components
	std::string fileName2 = "Pressure.png";
	ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 16, 16);
	ECS::GetComponent<Transform>(entity2).SetPosition(vec3(0.f, 224.f, 8.f));
	ECS::GetComponent<PressurePlate>(entity2).SetGateNum(entity);
	auto& tempTrans2 = ECS::GetComponent<Transform>(entity2);
	auto& tempSpr2 = ECS::GetComponent<Sprite>(entity2);
	auto& tempPhsBody2 = ECS::GetComponent<PhysicsBody>(entity2);
	b2Body* tempBody2;
	b2BodyDef tempDef2;

	b2FixtureDef plateDef;
	b2PolygonShape plateShape;
	plateShape.SetAsBox(8.f, 2.f, b2Vec2(0.f, -6.f), 0);
	plateDef.shape = &plateShape;
	plateDef.isSensor = true;

	tempDef2.type = b2_kinematicBody;
	tempDef2.position.Set(float32(tempTrans2.GetPositionX()), float32(tempTrans2.GetPositionY()));
	tempBody2 = m_physicsWorld->CreateBody(&tempDef2);
	tempBody2->CreateFixture(&plateDef);
	tempBody2->SetEntityNumber(entity2);
	tempBody2->SetEntityType(8);
	tempPhsBody2 = PhysicsBody(tempBody2, float(16), float(4),
		vec2(0.f, 0.f),
		false,false);
	//sets up the identifier
	unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity2, bitHolder2, "Pressure");
	}

	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Gate>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Door = "DoorOpening.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Door);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));
	anim.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(false);
	//Sets the time between frames
	anim.SetSecPerFrame(0.05f);
	animController.AddAnimation(Animation());

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(0.f, 480.f), vec2(160.f, 0.f));
	anim2.AddFrame(vec2(160.f, 480.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(320.f, 480.f), vec2(480.f, 0.f));
	anim2.AddFrame(vec2(480.f, 480.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(640.f, 480.f), vec2(800.f, 0.f));
	anim2.AddFrame(vec2(800.f, 480.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(960.f, 480.f), vec2(1120.f, 0.f));
	anim2.AddFrame(vec2(1120.f, 480.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 480.f), vec2(1440.f, 0.f));
	anim2.AddFrame(vec2(1440.f, 480.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 480.f), vec2(1760.f, 0.f));
	anim2.AddFrame(vec2(1760.f, 480.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 480.f), vec2(2080.f, 0.f));
	anim2.AddFrame(vec2(2080.f, 480.f), vec2(2240.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 480.f), vec2(2400.f, 0.f));
	anim2.AddFrame(vec2(2400.f, 480.f), vec2(2560.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 480.f), vec2(2720.f, 0.f));
	anim2.AddFrame(vec2(2720.f, 480.f), vec2(2880.f, 0.f));
	anim2.AddFrame(vec2(2880.f, 480.f), vec2(3040.f, 0.f));
	anim2.AddFrame(vec2(3040.f, 480.f), vec2(3200.f, 0.f));
	anim2.AddFrame(vec2(3200.f, 480.f), vec2(3360.f, 0.f));
	anim2.AddFrame(vec2(3360.f, 480.f), vec2(3520.f, 0.f));
	anim2.AddFrame(vec2(3520.f, 480.f), vec2(3680.f, 0.f));
	anim2.AddFrame(vec2(3680.f, 480.f), vec2(3840.f, 0.f));
	anim2.AddFrame(vec2(3840.f, 480.f), vec2(4000.f, 0.f));

	//Makes it repeat
	anim2.SetRepeating(false);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.05f);


	ECS::GetComponent<Sprite>(entity).LoadSprite(Door, 16, 48, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f, 48.f, 8.f));
	auto& tempTrans = ECS::GetComponent<Transform>(entity);
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_kinematicBody;
	tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetEntityNumber(entity);
	tempBody->SetEntityType(0);
	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f),
		false);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Gate");


	auto entity2 = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity2);
	ECS::AttachComponent<Transform>(entity2);
	ECS::AttachComponent<PhysicsBody>(entity2);
	ECS::AttachComponent<PressurePlate>(entity2);
	//sets up components
	std::string fileName2 = "Pressure.png";
	ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 16, 16);
	ECS::GetComponent<Transform>(entity2).SetPosition(vec3(32.f, 32.f, 8.f));
	ECS::GetComponent<PressurePlate>(entity2).SetGateNum(entity);
	auto& tempTrans2 = ECS::GetComponent<Transform>(entity2);
	auto& tempSpr2 = ECS::GetComponent<Sprite>(entity2);
	auto& tempPhsBody2 = ECS::GetComponent<PhysicsBody>(entity2);
	b2Body* tempBody2;
	b2BodyDef tempDef2;

	b2FixtureDef plateDef;
	b2PolygonShape plateShape;
	plateShape.SetAsBox(8.f, 2.f, b2Vec2(0.f, -6.f), 0);
	plateDef.shape = &plateShape;
	plateDef.isSensor = true;

	tempDef2.type = b2_kinematicBody;
	tempDef2.position.Set(float32(tempTrans2.GetPositionX()), float32(tempTrans2.GetPositionY()));
	tempBody2 = m_physicsWorld->CreateBody(&tempDef2);
	tempBody2->CreateFixture(&plateDef);
	tempBody2->SetEntityNumber(entity2);
	tempBody2->SetEntityType(8);
	tempPhsBody2 = PhysicsBody(tempBody2, float(16), float(4),
		vec2(0.f, -8.f),
		false, false);
	//sets up the identifier
	unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity2, bitHolder2, "Pressure");
	}

	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<PlatformEnemy>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Float = "Floating Enemy.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Float);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(0.f, 160.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(320.f, 160.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(640.f, 160.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(960.f, 160.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(1280.f, 160.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1600.f, 160.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1920.f, 160.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(2240.f, 160.f), vec2(2560.f, 0.f));
	anim.AddFrame(vec2(2560.f, 160.f), vec2(2880.f, 0.f));
	anim.AddFrame(vec2(2880.f, 160.f), vec2(3200.f, 0.f));
	anim.AddFrame(vec2(3200.f, 160.f), vec2(3520.f, 0.f));
	anim.AddFrame(vec2(3520.f, 160.f), vec2(3840.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(true);
	//Sets the time between frames
	anim.SetSecPerFrame(0.1667f);
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(1);

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(320.f, 160.f), vec2(0.f, 0.f));
	anim2.AddFrame(vec2(640.f, 160.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(960.f, 160.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 160.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 160.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 160.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 160.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 160.f), vec2(2240.f, 0.f));
	anim2.AddFrame(vec2(2880.f, 160.f), vec2(2560.f, 0.f));
	anim2.AddFrame(vec2(3200.f, 160.f), vec2(2880.f, 0.f));
	anim2.AddFrame(vec2(3520.f, 160.f), vec2(3200.f, 0.f));
	anim2.AddFrame(vec2(3840.f, 160.f), vec2(3520.f, 0.f));


	//Makes it repeat
	anim2.SetRepeating(true);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.1667f);


	ECS::GetComponent<Sprite>(entity).LoadSprite(Float, 32, 16, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-24.f, 144.f, 10.f));
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
	tempBody->SetEntityType(9);
	tempBody->SetFixedRotation(true);
	tempPhsBody = PhysicsBody(tempBody, float(32), float(16),
		vec2(0.f, 0.f),
		true);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit()|EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Platform enemy");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<PlatformEnemy>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string Float = "Floating Enemy.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(Float);
		//Adds first animation
		animController.AddAnimation(Animation());
		//Sets active animation
		animController.SetActiveAnim(0);

		//gets first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0.f, 160.f), vec2(320.f, 0.f));
		anim.AddFrame(vec2(320.f, 160.f), vec2(640.f, 0.f));
		anim.AddFrame(vec2(640.f, 160.f), vec2(960.f, 0.f));
		anim.AddFrame(vec2(960.f, 160.f), vec2(1280.f, 0.f));
		anim.AddFrame(vec2(1280.f, 160.f), vec2(1600.f, 0.f));
		anim.AddFrame(vec2(1600.f, 160.f), vec2(1920.f, 0.f));
		anim.AddFrame(vec2(1920.f, 160.f), vec2(2240.f, 0.f));
		anim.AddFrame(vec2(2240.f, 160.f), vec2(2560.f, 0.f));
		anim.AddFrame(vec2(2560.f, 160.f), vec2(2880.f, 0.f));
		anim.AddFrame(vec2(2880.f, 160.f), vec2(3200.f, 0.f));
		anim.AddFrame(vec2(3200.f, 160.f), vec2(3520.f, 0.f));
		anim.AddFrame(vec2(3520.f, 160.f), vec2(3840.f, 0.f));

		//Makes it repeat
		anim.SetRepeating(true);
		//Sets the time between frames
		anim.SetSecPerFrame(0.1667f);
		animController.AddAnimation(Animation());
		//Sets active animation
		animController.SetActiveAnim(1);

		//gets first animation
		auto& anim2 = animController.GetAnimation(1);
		anim2.AddFrame(vec2(320.f, 160.f), vec2(0.f, 0.f));
		anim2.AddFrame(vec2(640.f, 160.f), vec2(320.f, 0.f));
		anim2.AddFrame(vec2(960.f, 160.f), vec2(640.f, 0.f));
		anim2.AddFrame(vec2(1280.f, 160.f), vec2(960.f, 0.f));
		anim2.AddFrame(vec2(1600.f, 160.f), vec2(1280.f, 0.f));
		anim2.AddFrame(vec2(1920.f, 160.f), vec2(1600.f, 0.f));
		anim2.AddFrame(vec2(2240.f, 160.f), vec2(1920.f, 0.f));
		anim2.AddFrame(vec2(2560.f, 160.f), vec2(2240.f, 0.f));
		anim2.AddFrame(vec2(2880.f, 160.f), vec2(2560.f, 0.f));
		anim2.AddFrame(vec2(3200.f, 160.f), vec2(2880.f, 0.f));
		anim2.AddFrame(vec2(3520.f, 160.f), vec2(3200.f, 0.f));
		anim2.AddFrame(vec2(3840.f, 160.f), vec2(3520.f, 0.f));


		//Makes it repeat
		anim2.SetRepeating(true);
		//Sets the time between frames
		anim2.SetSecPerFrame(0.1667f);


		ECS::GetComponent<Sprite>(entity).LoadSprite(Float, 32, 16, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-23.5, -64.f, 10.f));
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
		tempBody->SetEntityType(9);
		tempBody->SetFixedRotation(true);
		tempPhsBody = PhysicsBody(tempBody, float(32), float(16),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform enemy");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<BlockEnemy>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string Block = "BlockMoveGol.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(Block);
		//Adds first animation
		animController.AddAnimation(Animation());
		//Sets active animation
		animController.SetActiveAnim(0);

		//gets first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0.f, 320.f), vec2(320.f, 0.f));
		anim.AddFrame(vec2(320.f, 320.f), vec2(640.f, 0.f));
		anim.AddFrame(vec2(640.f, 320.f), vec2(960.f, 0.f));
		anim.AddFrame(vec2(960.f, 320.f), vec2(1280.f, 0.f));
		anim.AddFrame(vec2(1280.f, 320.f), vec2(1600.f, 0.f));
		anim.AddFrame(vec2(1600.f, 320.f), vec2(1920.f, 0.f));
		anim.AddFrame(vec2(1920.f, 320.f), vec2(2240.f, 0.f));
		anim.AddFrame(vec2(2240.f, 320.f), vec2(2560.f, 0.f));

		//Makes it repeat
		anim.SetRepeating(true);
		//Sets the time between frames
		anim.SetSecPerFrame(0.1667f);

		animController.AddAnimation(Animation());
		//Sets active animation
		animController.SetActiveAnim(1);

		//gets first animation
		auto& anim2 = animController.GetAnimation(1);
		anim2.AddFrame(vec2(320.f, 320.f), vec2(0.f, 0.f));
		anim2.AddFrame(vec2(640.f, 320.f), vec2(320.f, 0.f));
		anim2.AddFrame(vec2(960.f, 320.f), vec2(640.f, 0.f));
		anim2.AddFrame(vec2(1280.f, 320.f), vec2(960.f, 0.f));
		anim2.AddFrame(vec2(1600.f, 320.f), vec2(1280.f, 0.f));
		anim2.AddFrame(vec2(1920.f, 320.f), vec2(1600.f, 0.f));
		anim2.AddFrame(vec2(2240.f, 320.f), vec2(1920.f, 0.f));
		anim2.AddFrame(vec2(2560.f, 320.f), vec2(2240.f, 0.f));

		//Makes it repeat
		anim2.SetRepeating(true);
		//Sets the time between frames
		anim2.SetSecPerFrame(0.1667f);
		animController.AddAnimation(Animation());
		//Sets active animation
		animController.SetActiveAnim(0);

		//gets first animation
		auto& anim3 = animController.GetAnimation(2);
		anim3.AddFrame(vec2(0.f, 640.f), vec2(320.f, 320.f));
		anim3.AddFrame(vec2(320.f, 640.f), vec2(640.f, 320.f));
		anim3.AddFrame(vec2(640.f, 640.f), vec2(960.f, 320.f));
		anim3.AddFrame(vec2(960.f, 640.f), vec2(1280.f, 320.f));
		anim3.AddFrame(vec2(1280.f, 640.f), vec2(1600.f, 320.f));
		anim3.AddFrame(vec2(1600.f, 640.f), vec2(1920.f, 320.f));
		anim3.AddFrame(vec2(1920.f, 640.f), vec2(2240.f, 320.f));
		anim3.AddFrame(vec2(2240.f, 640.f), vec2(2560.f, 320.f));
		anim3.AddFrame(vec2(2560.f, 640.f), vec2(2880.f, 320.f));
		anim3.AddFrame(vec2(2880.f, 640.f), vec2(3200.f, 320.f));
		anim3.AddFrame(vec2(3200.f, 640.f), vec2(3520.f, 320.f));
		anim3.AddFrame(vec2(3520.f, 640.f), vec2(3840.f, 320.f));
		anim3.AddFrame(vec2(3840.f, 640.f), vec2(4160.f, 320.f));
		anim3.AddFrame(vec2(4160.f, 640.f), vec2(4480.f, 320.f));
		//Makes it repeat
		anim3.SetRepeating(false);
		//Sets the time between frames
		anim3.SetSecPerFrame(0.1f);



		ECS::GetComponent<Sprite>(entity).LoadSprite(Block, 16, 16, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-87.f, -128.f, 10.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "block enemy ");
	}

	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<BlockEnemy>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Block = "BlockMoveGol.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Block);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(0.f, 320.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(320.f, 320.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(640.f, 320.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(960.f, 320.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(1280.f, 320.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1600.f, 320.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1920.f, 320.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(2240.f, 320.f), vec2(2560.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(true);
	//Sets the time between frames
	anim.SetSecPerFrame(0.1667f);

	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(1);

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(320.f, 320.f), vec2(0.f, 0.f));
	anim2.AddFrame(vec2(640.f, 320.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(960.f, 320.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 320.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 320.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 320.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 320.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 320.f), vec2(2240.f, 0.f));

	//Makes it repeat
	anim2.SetRepeating(true);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.1667f);
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim3 = animController.GetAnimation(2);
	anim3.AddFrame(vec2(0.f, 640.f), vec2(320.f, 320.f));
	anim3.AddFrame(vec2(320.f, 640.f), vec2(640.f, 320.f));
	anim3.AddFrame(vec2(640.f, 640.f), vec2(960.f, 320.f));
	anim3.AddFrame(vec2(960.f, 640.f), vec2(1280.f, 320.f));
	anim3.AddFrame(vec2(1280.f, 640.f), vec2(1600.f, 320.f));
	anim3.AddFrame(vec2(1600.f, 640.f), vec2(1920.f, 320.f));
	anim3.AddFrame(vec2(1920.f, 640.f), vec2(2240.f, 320.f));
	anim3.AddFrame(vec2(2240.f, 640.f), vec2(2560.f, 320.f));
	anim3.AddFrame(vec2(2560.f, 640.f), vec2(2880.f, 320.f));
	anim3.AddFrame(vec2(2880.f, 640.f), vec2(3200.f, 320.f));
	anim3.AddFrame(vec2(3200.f, 640.f), vec2(3520.f, 320.f));
	anim3.AddFrame(vec2(3520.f, 640.f), vec2(3840.f, 320.f));
	anim3.AddFrame(vec2(3840.f, 640.f), vec2(4160.f, 320.f));
	anim3.AddFrame(vec2(4160.f, 640.f), vec2(4480.f, 320.f));
	//Makes it repeat
	anim3.SetRepeating(false);
	//Sets the time between frames
	anim3.SetSecPerFrame(0.1f);



	ECS::GetComponent<Sprite>(entity).LoadSprite(Block, 16, 16, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(52.f, 224.f, 10.f));
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
	ECS::GetComponent<BlockEnemy>(entity).SetInactive();
	ECS::GetComponent<AnimationController>(entity).SetActiveAnim(2);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "block enemy ");
	}

	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<BlockEnemy>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Block = "BlockMoveGol.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Block);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(0.f, 320.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(320.f, 320.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(640.f, 320.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(960.f, 320.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(1280.f, 320.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1600.f, 320.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1920.f, 320.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(2240.f, 320.f), vec2(2560.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(true);
	//Sets the time between frames
	anim.SetSecPerFrame(0.1667f);

	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(1);

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(320.f, 320.f), vec2(0.f, 0.f));
	anim2.AddFrame(vec2(640.f, 320.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(960.f, 320.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 320.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 320.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 320.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 320.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 320.f), vec2(2240.f, 0.f));

	//Makes it repeat
	anim2.SetRepeating(true);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.1667f);
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim3 = animController.GetAnimation(2);
	anim3.AddFrame(vec2(0.f, 640.f), vec2(320.f, 320.f));
	anim3.AddFrame(vec2(320.f, 640.f), vec2(640.f, 320.f));
	anim3.AddFrame(vec2(640.f, 640.f), vec2(960.f, 320.f));
	anim3.AddFrame(vec2(960.f, 640.f), vec2(1280.f, 320.f));
	anim3.AddFrame(vec2(1280.f, 640.f), vec2(1600.f, 320.f));
	anim3.AddFrame(vec2(1600.f, 640.f), vec2(1920.f, 320.f));
	anim3.AddFrame(vec2(1920.f, 640.f), vec2(2240.f, 320.f));
	anim3.AddFrame(vec2(2240.f, 640.f), vec2(2560.f, 320.f));
	anim3.AddFrame(vec2(2560.f, 640.f), vec2(2880.f, 320.f));
	anim3.AddFrame(vec2(2880.f, 640.f), vec2(3200.f, 320.f));
	anim3.AddFrame(vec2(3200.f, 640.f), vec2(3520.f, 320.f));
	anim3.AddFrame(vec2(3520.f, 640.f), vec2(3840.f, 320.f));
	anim3.AddFrame(vec2(3840.f, 640.f), vec2(4160.f, 320.f));
	anim3.AddFrame(vec2(4160.f, 640.f), vec2(4480.f, 320.f));
	//Makes it repeat
	anim3.SetRepeating(false);
	//Sets the time between frames
	anim3.SetSecPerFrame(0.1f);



	ECS::GetComponent<Sprite>(entity).LoadSprite(Block, 16, 16, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-96.f, -126.f, 10.f));
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
	ECS::GetComponent<BlockEnemy>(entity).SetInactive();
	ECS::GetComponent<AnimationController>(entity).SetActiveAnim(2);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "block enemy ");
	}

	{
	auto entity = ECS::CreateEntity();
	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<BlockEnemy>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string Block = "BlockMoveGol.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(Block);
	//Adds first animation
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim = animController.GetAnimation(0);
	anim.AddFrame(vec2(0.f, 320.f), vec2(320.f, 0.f));
	anim.AddFrame(vec2(320.f, 320.f), vec2(640.f, 0.f));
	anim.AddFrame(vec2(640.f, 320.f), vec2(960.f, 0.f));
	anim.AddFrame(vec2(960.f, 320.f), vec2(1280.f, 0.f));
	anim.AddFrame(vec2(1280.f, 320.f), vec2(1600.f, 0.f));
	anim.AddFrame(vec2(1600.f, 320.f), vec2(1920.f, 0.f));
	anim.AddFrame(vec2(1920.f, 320.f), vec2(2240.f, 0.f));
	anim.AddFrame(vec2(2240.f, 320.f), vec2(2560.f, 0.f));

	//Makes it repeat
	anim.SetRepeating(true);
	//Sets the time between frames
	anim.SetSecPerFrame(0.1667f);

	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(1);

	//gets first animation
	auto& anim2 = animController.GetAnimation(1);
	anim2.AddFrame(vec2(320.f, 320.f), vec2(0.f, 0.f));
	anim2.AddFrame(vec2(640.f, 320.f), vec2(320.f, 0.f));
	anim2.AddFrame(vec2(960.f, 320.f), vec2(640.f, 0.f));
	anim2.AddFrame(vec2(1280.f, 320.f), vec2(960.f, 0.f));
	anim2.AddFrame(vec2(1600.f, 320.f), vec2(1280.f, 0.f));
	anim2.AddFrame(vec2(1920.f, 320.f), vec2(1600.f, 0.f));
	anim2.AddFrame(vec2(2240.f, 320.f), vec2(1920.f, 0.f));
	anim2.AddFrame(vec2(2560.f, 320.f), vec2(2240.f, 0.f));

	//Makes it repeat
	anim2.SetRepeating(true);
	//Sets the time between frames
	anim2.SetSecPerFrame(0.1667f);
	animController.AddAnimation(Animation());
	//Sets active animation
	animController.SetActiveAnim(0);

	//gets first animation
	auto& anim3 = animController.GetAnimation(2);
	anim3.AddFrame(vec2(0.f, 640.f), vec2(320.f, 320.f));
	anim3.AddFrame(vec2(320.f, 640.f), vec2(640.f, 320.f));
	anim3.AddFrame(vec2(640.f, 640.f), vec2(960.f, 320.f));
	anim3.AddFrame(vec2(960.f, 640.f), vec2(1280.f, 320.f));
	anim3.AddFrame(vec2(1280.f, 640.f), vec2(1600.f, 320.f));
	anim3.AddFrame(vec2(1600.f, 640.f), vec2(1920.f, 320.f));
	anim3.AddFrame(vec2(1920.f, 640.f), vec2(2240.f, 320.f));
	anim3.AddFrame(vec2(2240.f, 640.f), vec2(2560.f, 320.f));
	anim3.AddFrame(vec2(2560.f, 640.f), vec2(2880.f, 320.f));
	anim3.AddFrame(vec2(2880.f, 640.f), vec2(3200.f, 320.f));
	anim3.AddFrame(vec2(3200.f, 640.f), vec2(3520.f, 320.f));
	anim3.AddFrame(vec2(3520.f, 640.f), vec2(3840.f, 320.f));
	anim3.AddFrame(vec2(3840.f, 640.f), vec2(4160.f, 320.f));
	anim3.AddFrame(vec2(4160.f, 640.f), vec2(4480.f, 320.f));
	//Makes it repeat
	anim3.SetRepeating(false);
	//Sets the time between frames
	anim3.SetSecPerFrame(0.1f);



	ECS::GetComponent<Sprite>(entity).LoadSprite(Block, 16, 16, true, &animController);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(36.f, 32.f, 10.f));
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
	ECS::GetComponent<BlockEnemy>(entity).SetInactive();
	ECS::GetComponent<AnimationController>(entity).SetActiveAnim(2);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "block enemy ");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, 224.f, -10.f));
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
		tempBody->SetEntityType(6);
		tempPhsBody = PhysicsBody(tempBody, float(16), float(8),
			vec2(0.f, -8.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "spikes");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, 224.f, -10.f));
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
		tempBody->SetEntityType(6);
		tempPhsBody = PhysicsBody(tempBody, float(6), float(8),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "spikes");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(112.f, -48.f, -10.f));
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
		tempBody->SetEntityType(6);
		tempPhsBody = PhysicsBody(tempBody, float(16), float(8),
			vec2(0.f, -8.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "spikes");
	}

	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(112.f, -48.f, -10.f));
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
		tempBody->SetEntityType(6);
		tempPhsBody = PhysicsBody(tempBody, float(6), float(8),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "spikes");
	}
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

void Stage5::Update(entt::registry* reg)
{
	Routines(reg);
}

void Stage5::Routines(entt::registry* reg)
{
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	vec3 camPos = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).GetPosition();
	vec3 playPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	ECS::GetComponent<Transform>(1).SetPosition(camPos + vec3(-180.f, 50.f, 0.f));
	ECS::GetComponent<Transform>(2).SetPosition(camPos + vec3(-180.f, 70.f, 0.f));
	ECS::GetComponent<Transform>(3).SetPosition(camPos + vec3(-180.f, 90.f, 0.f));
	ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).AddJumpTime(Timer::deltaTime);
	ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).AddShootTime(Timer::deltaTime);
	if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetKill())
	{
		ECS::GetComponent<Sprite>(EntityIdentifier::MainPlayer()).SetWidth(24.f);
		ECS::GetComponent<Sprite>(EntityIdentifier::MainPlayer()).SetHeight(24.f);
		ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(12);
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).AddKillTime(Timer::deltaTime);
	}
	else
	{
		auto viewBlockEnemy = reg->view<BlockEnemy>();
		auto viewPlatformEnemy = reg->view<PlatformEnemy>();
		auto viewArrow = reg->view<Arrow>();
		for (auto entity : viewBlockEnemy)
		{
			if (ECS::GetComponent<BlockEnemy>(entity).GetIsLeft() && ECS::GetComponent<BlockEnemy>(entity).GetActive())
			{
				ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(-2.f, ECS::GetComponent<PhysicsBody>(entity).GetVelocity().y, 0.f));
				ECS::GetComponent<AnimationController>(entity).SetActiveAnim(0);
			}
			else if (ECS::GetComponent<BlockEnemy>(entity).GetActive())
			{
				ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(2.f, ECS::GetComponent<PhysicsBody>(entity).GetVelocity().y, 0.f));
				ECS::GetComponent<AnimationController>(entity).SetActiveAnim(1);
			}
			else if (ECS::GetComponent<BlockEnemy>(entity).GetJustDead())
			{
				ECS::GetComponent<PhysicsBody>(entity).GetBody()->GetFixtureList()->SetSensor(true);
				b2FixtureDef blockDead;
				b2PolygonShape deadShape;
				deadShape.SetAsBox(8.f, 7.f, b2Vec2(0.f, -1.5f), 0);
				blockDead.shape = &deadShape;
				ECS::GetComponent<PhysicsBody>(entity).GetBody()->CreateFixture(&blockDead);

			}
		}
		for (auto entity : viewPlatformEnemy)
		{
			if (ECS::GetComponent<PlatformEnemy>(entity).GetIsLeft())
			{
				ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(-5.f, ECS::GetComponent<PhysicsBody>(entity).GetVelocity().y, 0.f));
				ECS::GetComponent<AnimationController>(entity).SetActiveAnim(0);
			}
			else
			{
				ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(5.f, ECS::GetComponent<PhysicsBody>(entity).GetVelocity().y, 0.f));
				ECS::GetComponent<AnimationController>(entity).SetActiveAnim(1);
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

void Stage5::GamepadStroke(XInputController* con)
{
	auto phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	vec3 curVelo = phsBod.GetVelocity();
	if (con->IsButtonPressed(A))
	{
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			phsBod.SetVelocity(vec3(curVelo.x, 23.f, 0.f));
		}
	}
	if (con->IsButtonPressed(X))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ArrowShot(m_physicsWorld);
	}
	if (con->IsButtonPressed(DPAD_LEFT))
	{
		if (!ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLeftContact())
		{
			phsBod.SetVelocity(vec3(-10.f, curVelo.y, 0.f));
		}
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetLeft(true);
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetLastRight(false);

	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetLeft(false); }
	if (con->IsButtonPressed(DPAD_RIGHT))
	{
		if (!ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetRightContact())
		{
			phsBod.SetVelocity(vec3(10.f, curVelo.y, 0.f));
		}
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRight(true);
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetLastRight(true);

	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRight(false); }
	if (con->IsButtonPressed(DPAD_UP))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetUp(true);
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetUp(false); }
	if (con->IsButtonPressed(DPAD_DOWN))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetDown(true);
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetDown(false); }
	if (con->IsButtonPressed(RB))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRoot(true);
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			phsBod.SetVelocity(vec3(0.f, 0.f, 0.f));
		}
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRoot(false); }
}

void Stage5::GamepadStick(XInputController* con)
{
	Stick sticks[2];
	con->GetSticks(sticks);
}

void Stage5::GamepadTrigger(XInputController* con)
{
}

void Stage5::KeyboardHold()
{
	bool moved = false;
	bool noShoot = false;
	bool noJump = false;
	vec3 playPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	ECS::GetComponent<Transform>(4).SetPosition(playPos + vec3(-2.f, 10.f, 0.f));
	if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetJumpTime() > 1.f)
	{
		noJump = true;
	}
	if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetShootTime() > 0.5f)
	{
		noShoot = true;
		ECS::GetComponent<AnimationController>(4).SetActiveAnim(2);
	}
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
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded() && noShoot&& noJump)
		{
			ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(5);
		}
		moved = true;

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
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded() && noShoot&& noJump)
		{
			ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(4);
		}
		moved = true;

	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRight(false); }
	if (Input::GetKey(Key::W))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetUp(true);
		if (moved && !ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetRooted() && ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetRight() && noShoot)
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(4);
			}
			else if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLeft() && noShoot)
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(5);
			}
			else
			{
				if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLastRight() && noShoot)
				{
					ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(7);
				}
				else if (noShoot)
				{
					ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(6);
				}
			}
		}
		else if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetRight())
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(0);
			}
			else if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLeft())
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(1);
			}
			else
			{
				if (noShoot)
				{
					ECS::GetComponent<AnimationController>(4).SetActiveAnim(0);
				}
				ECS::GetComponent<Transform>(4).SetPosition(playPos + vec3(-2.f, 10.f, 0.f));
				if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLastRight())
				{
					ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(3);
				}
				else
				{
					ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(2);
				}
			}
		}
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetUp(false); }
	if (Input::GetKey(Key::S))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetDown(true);
		if (moved && !ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetRooted() && ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetRight() && noShoot)
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(4);
			}
			else if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLeft() && noShoot)
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(5);
			}
			else
			{

				if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLastRight() && noShoot)
				{
					ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(7);
				}
				else if (noShoot)
				{
					ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(6);
				}
			}
		}
		else if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetRight())
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(0);
			}
			else if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLeft())
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(1);
			}
			else
			{
				if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLastRight())
				{
					ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(0);
				}
				else
				{
					ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(1);
				}
			}
		}
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetDown(false); }
	if (Input::GetKey(Key::Shift))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRoot(true);
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			phsBod.SetVelocity(vec3(0.f, 0.f, 0.f));
			moved = false;
		}
	}
	else { ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetRoot(false); }

	if (!moved && !ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetUp() && !ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetDown())
	{
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded() && noShoot&& noJump)
		{
			if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLastRight())
			{
				//play idle right
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(0);
			}
			else
			{
				//play idle left
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(1);
			}
		}
	}
	/*
	0 Idle Right
	1 Idle Left
	2 Idle Armless Left
	3 Idle Armless right
	4 Move Right
	5 Move Left
	6 Armless Left move
	7 Armless Right move
	8 Jump right
	9 jump left
	10 shoot right
	11 shoot left
	*/


}

void Stage5::KeyboardDown()
{
	auto& phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	vec3 curVelo = phsBod.GetVelocity();
	if (Input::GetKeyDown(Key::Space))
	{
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ResetJump();
			phsBod.SetVelocity(vec3(curVelo.x, 23.f, 0.f));
			if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLastRight())
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(8);
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetAnimation(8).Reset();
			}
			else
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(9);
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetAnimation(9).Reset();
			}

		}
	}
	if (Input::GetKeyDown(Key::K))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ArrowShot(m_physicsWorld);
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ResetShoot();
		if (ECS::GetComponent<AnimationController>(4).GetActiveAnim() == 0)
		{
			ECS::GetComponent<AnimationController>(4).SetActiveAnim(1);
			ECS::GetComponent<AnimationController>(4).GetAnimation(1).Reset();
		}
		else
		{
			if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetLastRight())
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(10);
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetAnimation(10).Reset();

			}
			else
			{
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(11);
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetAnimation(11).Reset();
			}
		}
	}
}

void Stage5::KeyboardUp(void)
{
}

void Stage5::MouseMotion(SDL_MouseMotionEvent evnt)
{

}

void Stage5::MouseClick(SDL_MouseButtonEvent evnt)
{

}

void Stage5::MouseWheel(SDL_MouseWheelEvent evnt)
{
}