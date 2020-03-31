#include "Stage6.h"

Stage6::Stage6(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-10.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void Stage6::InitScene(float windowWidth, float windowHeight)
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
		//ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "JungleLevel4.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 592);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -250.f, 9.f));
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -56.7f, 6.f));
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
		//sets up components
		std::string fileName = "gaiabackground.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 205);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -261.3f, 6.f));
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
		//sets up components
		std::string fileName = "gaiabackground.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 170);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -447.7f, 6.f));
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-129.f, 0.f, 10.f));
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -20.f, 10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "block enemy 1");
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
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-30.f, -230.f, 10.f));
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
	ECS::SetUpIdentifier(entity, bitHolder, "block enemy 2");
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
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(66.5f, -506.f, 10.f));
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
	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f),
		true);
	//sets up the identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Platform enemy 1");
	}

	//floating (needs fix)
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


		ECS::GetComponent<Sprite>(entity).LoadSprite(Float, 36, 16, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(79.1f, -260.5f, 10.f));
		
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
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//ECS::GetComponent<PlatformEnemy>(entity).SetFloating(ECS::GetComponent<PhysicsBody>(entity).GetBody()->GetTransform().p.y);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Floating Platform enemy 1");
	}
	
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-24.5f, -42.f, -10.f));
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
	//walls start
	{

		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 592);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-160.f, -250.f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall 1");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-143.5f, -122.2f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-96.2f, -122.2f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 592);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, -250.f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 315, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 37.9f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-48.f, -26.1f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(144.6f, -73.7f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 94, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(39.1f, -442.2f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "addedFloor");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(95.4f, -106.f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 93);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.2f, -83.5f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(63.9f, -122.1f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 29, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(41.4f, -105.9f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 53, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-61.6f, -106.5f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(144.1f, -155.f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(31.9f, -170.3f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(15.6f, -154.f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 34, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-9.8f, -138.2f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 90);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-79.7f, -148.9f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 243, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(33.5f, -186.f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 258, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-24.9f, -250.3f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-63.9f, -234.2f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 70);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-95.9f, -290.3f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 59);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-32.1f, -351.6f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(136.2f, -298.4f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 144, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.1f, -330.2f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 258, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-25.f, -377.9f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(144.4f, -410.1f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 167, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(18.4f, -457.8f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-56.1f, -442.2f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 93, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(54.5f, -442.2f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 89, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-110.7f, -490.f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 99);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-63.9f, -489.3f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(144.f, -489.8f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(112.f, -506.2f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(144.3f, -474.5f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.1f, -490.5f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "non stick wall");
	}

	//sticky
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 66);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(32.3f, -81.1f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "sticky wall");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 51);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-32.1f, -107.3f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "sticky wall");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(95.4f, -450.1f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "sticky wall");
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 209, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(47.6f, -522.9f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 29, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(71.1f, -33.9f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 17, 15);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(71.8f, -28.2f, -10.f));
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(136.6f, -171.1f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-94.7f, -108.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-144.9f, -115.2f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 66, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-58.2f, -315.3f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 147, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(83.f, -315.3f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-15.8f, -443.8f, -10.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Spikes");
	}
	//pressure
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(64.1f, -218.2f, 8.f));
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
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(0.f, -234.3f, 8.f));
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
			false, false);
		//sets up the identifier
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Pressure");
	}
	//gates
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.2f, -154.f, 8.f));
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
		ECS::AttachComponent<AnimationController>(entity2);

		//Sets up components
		std::string targ = "Target.png";
		auto& animController2 = ECS::GetComponent<AnimationController>(entity2);
		animController2.InitUVs(targ);
		//Adds first animation
		animController2.AddAnimation(Animation());
		animController2.SetActiveAnim(0);
		auto& anim3 = animController2.GetAnimation(0);
		anim3.AddFrame(vec2(0.f, 160.f), vec2(150.f, 10.f));
		//Makes it repeat
		anim3.SetRepeating(false);
		//Sets the time between frames
		anim3.SetSecPerFrame(0.1667f);
		animController2.AddAnimation(Animation());
		auto& anim4 = animController2.GetAnimation(1);
		anim4.AddFrame(vec2(0.f, 160.f), vec2(150.f, 10.f));
		anim4.AddFrame(vec2(160.f, 160.f), vec2(310.f, 10.f));
		anim4.AddFrame(vec2(320.f, 160.f), vec2(470.f, 10.f));
		anim4.AddFrame(vec2(480.f, 160.f), vec2(630.f, 10.f));
		anim4.AddFrame(vec2(640.f, 160.f), vec2(790.f, 10.f));
		anim4.AddFrame(vec2(800.f, 160.f), vec2(950.f, 10.f));
		//Makes it repeat
		anim4.SetRepeating(false);
		//Sets the time between frames
		anim4.SetSecPerFrame(0.07f);


		ECS::GetComponent<Sprite>(entity2).LoadSprite(targ, 16, 16, true, &animController2);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(91.7f, -121.6f, 8.f));
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


		ECS::GetComponent<Sprite>(entity).LoadSprite(Door, 16, 32, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f, -84.7f, 8.f));
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
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(32.5),
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
		ECS::AttachComponent<AnimationController>(entity2);

		//Sets up components
		std::string targ = "Target.png";
		auto& animController2 = ECS::GetComponent<AnimationController>(entity2);
		animController2.InitUVs(targ);
		//Adds first animation
		animController2.AddAnimation(Animation());
		animController2.SetActiveAnim(0);
		auto& anim3 = animController2.GetAnimation(0);
		anim3.AddFrame(vec2(0.f, 160.f), vec2(150.f, 10.f));
		//Makes it repeat
		anim3.SetRepeating(false);
		//Sets the time between frames
		anim3.SetSecPerFrame(0.1667f);
		animController2.AddAnimation(Animation());
		auto& anim4 = animController2.GetAnimation(1);
		anim4.AddFrame(vec2(0.f, 160.f), vec2(150.f, 10.f));
		anim4.AddFrame(vec2(160.f, 160.f), vec2(310.f, 10.f));
		anim4.AddFrame(vec2(320.f, 160.f), vec2(470.f, 10.f));
		anim4.AddFrame(vec2(480.f, 160.f), vec2(630.f, 10.f));
		anim4.AddFrame(vec2(640.f, 160.f), vec2(790.f, 10.f));
		anim4.AddFrame(vec2(800.f, 160.f), vec2(950.f, 10.f));
		//Makes it repeat
		anim4.SetRepeating(false);
		//Sets the time between frames
		anim4.SetSecPerFrame(0.07f);


		ECS::GetComponent<Sprite>(entity2).LoadSprite(targ, 16, 16, true, &animController2);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-148.f, -75.5f, 8.f));
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(96.1f, -218.2f, 8.f));
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
		ECS::AttachComponent<AnimationController>(entity2);

		//Sets up components
		std::string targ = "Target.png";
		auto& animController2 = ECS::GetComponent<AnimationController>(entity2);
		animController2.InitUVs(targ);
		//Adds first animation
		animController2.AddAnimation(Animation());
		animController2.SetActiveAnim(0);
		auto& anim3 = animController2.GetAnimation(0);
		anim3.AddFrame(vec2(150.f, 160.f), vec2(0.f, 10.f));
		//Makes it repeat
		anim3.SetRepeating(false);
		//Sets the time between frames
		anim3.SetSecPerFrame(0.1667f);
		animController2.AddAnimation(Animation());
		auto& anim4 = animController2.GetAnimation(1);
		anim4.AddFrame(vec2(150.f, 160.f), vec2(0.f, 10.f));
		anim4.AddFrame(vec2(310.f, 160.f), vec2(160.f, 10.f));
		anim4.AddFrame(vec2(470.f, 160.f), vec2(320.f, 10.f));
		anim4.AddFrame(vec2(630.f, 160.f), vec2(480.f, 10.f));
		anim4.AddFrame(vec2(790.f, 160.f), vec2(640.f, 10.f));
		anim4.AddFrame(vec2(950.f, 160.f), vec2(800.f, 10.f));
		//Makes it repeat
		anim4.SetRepeating(false);
		//Sets the time between frames
		anim4.SetSecPerFrame(0.07f);


		ECS::GetComponent<Sprite>(entity2).LoadSprite(targ, 16, 16, true, &animController2);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(84.f, -203.3f, 8.f));
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
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(79.9f, -410.3f, 8.f));
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
	ECS::AttachComponent<AnimationController>(entity2);

	//Sets up components
	std::string targ = "Target.png";
	auto& animController2 = ECS::GetComponent<AnimationController>(entity2);
	animController2.InitUVs(targ);
	//Adds first animation
	animController2.AddAnimation(Animation());
	animController2.SetActiveAnim(0);
	auto& anim3 = animController2.GetAnimation(0);
	anim3.AddFrame(vec2(0.f, 160.f), vec2(150.f, 10.f));
	//Makes it repeat
	anim3.SetRepeating(false);
	//Sets the time between frames
	anim3.SetSecPerFrame(0.1667f);
	animController2.AddAnimation(Animation());
	auto& anim4 = animController2.GetAnimation(1);
	anim4.AddFrame(vec2(0.f, 160.f), vec2(150.f, 10.f));
	anim4.AddFrame(vec2(160.f, 160.f), vec2(310.f, 10.f));
	anim4.AddFrame(vec2(320.f, 160.f), vec2(470.f, 10.f));
	anim4.AddFrame(vec2(480.f, 160.f), vec2(630.f, 10.f));
	anim4.AddFrame(vec2(640.f, 160.f), vec2(790.f, 10.f));
	anim4.AddFrame(vec2(800.f, 160.f), vec2(950.f, 10.f));
	//Makes it repeat
	anim4.SetRepeating(false);
	//Sets the time between frames
	anim4.SetSecPerFrame(0.07f);


	ECS::GetComponent<Sprite>(entity2).LoadSprite(targ, 16, 16, true, &animController2);
	ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-52.f, -473.f, 8.f));
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
		ECS::AttachComponent<LevelGoal>(entity);
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, -466.1f, -10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.fixedRotation = true;
		b2FixtureDef doorSense;
		b2PolygonShape doorShape;
		doorShape.SetAsBox(8.f, 16.f);
		doorSense.shape = &doorShape;
		doorSense.isSensor = true;
		/*b2FixtureDef baseFix;
		b2PolygonShape doorBase;
		doorBase.SetAsBox(8.f, 0.01f, b2Vec2(0.f, -16.f), 0.f);
		baseFix.shape = &doorBase;*/
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->CreateFixture(&doorSense);
		//tempBody->CreateFixture(&baseFix);
		tempBody->SetEntityNumber(entity);
		tempBody->SetEntityType(4);
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			false, false);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "TestGoal");
	}


	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

void Stage6::Update(entt::registry* reg)
{
	Routines(reg);
}

void Stage6::Routines(entt::registry* reg)
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
				ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(-5.f, 0.f, 0.f));
				ECS::GetComponent<AnimationController>(entity).SetActiveAnim(0);
			}
			else
			{
				ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(5.f, 0.f, 0.f));
				ECS::GetComponent<AnimationController>(entity).SetActiveAnim(1);
			}
			if (ECS::GetComponent<PlatformEnemy>(entity).GetFloating())
			{
				b2Vec2 tempPos = ECS::GetComponent<PhysicsBody>(entity).GetBody()->GetTransform().p;
				ECS::GetComponent<PhysicsBody>(entity).SetPosition(b2Vec2(tempPos.x, ECS::GetComponent<PlatformEnemy>(entity).GetYLock()));
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

void Stage6::GamepadStroke(XInputController* con)
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

void Stage6::GamepadStick(XInputController* con)
{
	Stick sticks[2];
	con->GetSticks(sticks);
}

void Stage6::GamepadTrigger(XInputController* con)
{
}

void Stage6::KeyboardHold()
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

void Stage6::KeyboardDown()
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

void Stage6::KeyboardUp(void)
{
}

void Stage6::MouseMotion(SDL_MouseMotionEvent evnt)
{

}

void Stage6::MouseClick(SDL_MouseButtonEvent evnt)
{

}

void Stage6::MouseWheel(SDL_MouseWheelEvent evnt)
{
}