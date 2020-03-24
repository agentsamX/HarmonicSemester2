#include "Stage3.h"

Stage3::Stage3(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-10.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void Stage3::InitScene(float windowWidth, float windowHeight)
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
		//ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "JungleLevel1.png";
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
		//sets up components
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 24);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-129.f, -13.f, 10.f));
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
	//enemies
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



		ECS::GetComponent<Sprite>(entity).LoadSprite(Block, 16, 16, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -40.f, 10.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "block enemy 1");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-34.f, -117.f, 10.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform enemy 1");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-5.f, -213.f, 10.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform entity 2");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, -480.f, 10.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform enemy 3");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(60.f, -480.f, 10.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform enemy 4");
	}
	
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 255, 31);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-24.f, -50.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 47);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(104.2f, -234.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 47);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-72.f, -219.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-48.f, -26.6f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "nub");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(32.f, -26.6f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "nub");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 325, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-6.f, 38.f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "roof");
	}
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		//sets up components
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 271, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(16.f, -153.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-112.f, -130.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 47, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(32.f, -130.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 63, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(120.f, -130.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 63, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-119.3f, -234.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 275, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-17.9f, -250.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 260, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(26.f, -322.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 177, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-64.5f, -418.2f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(88.f, -418.2f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.3f, -498.1f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 80, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-112.f, -498.1f, -10.f));
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
		ECS::SetUpIdentifier(entity, bitHolder, "floor");
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 112, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-48.f, -138.f, -10.f));
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(72.f, -123.0f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 143, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(16.2f, -234.f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 179, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(15.9f, -506.6f, -10.f));
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 47, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(48.1f, -411.9f, -10.f));
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
		std::string fileName = "floor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-7.9f, -386.2f, -10.f));
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, -282.f, 8.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Gate test");


		auto entity2 = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::AttachComponent<PhysicsBody>(entity2);
		ECS::AttachComponent<Target>(entity2);
		//sets up components
		std::string fileName2 = "TargetR.png";
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 9, 16);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(95.f, -281.5f, 8.f));
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
			vec2(0.f, 0.f),
			false);
		//sets up the identifier
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Target test");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-32.1f, -282.f, 8.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Gate test");


		auto entity2 = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::AttachComponent<PhysicsBody>(entity2);
		ECS::AttachComponent<Target>(entity2);
		//sets up components
		std::string fileName2 = "TargetR.png";
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 9, 16);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-17.7f, -266.f, 8.f));
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
			vec2(0.f, 0.f),
			false);
		//sets up the identifier
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Target test");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.1f, -378.7f, 8.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Sticky gate");


		auto entity2 = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::AttachComponent<PhysicsBody>(entity2);
		ECS::AttachComponent<Target>(entity2);
		//sets up components
		std::string fileName2 = "TargetL.png";
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 9, 16);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-82.1f, -345.9f, 8.f));
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
			vec2(0.f, 0.f),
			false);
		//sets up the identifier
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Target test");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.1f, -458.f, 8.f));
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()|EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Gate test");


		auto entity2 = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::AttachComponent<PhysicsBody>(entity2);
		ECS::AttachComponent<Target>(entity2);
		//sets up components
		std::string fileName2 = "TargetR.png";
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName2, 9, 16);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-65.7f, -442.2f, 8.f));
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
			vec2(0.f, 0.f),
			false);
		//sets up the identifier
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Target test");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-127.f, -466.f, 10.f));
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
void Stage3::Update(entt::registry* reg)
{
	Routines(reg);
}

void Stage3::Routines(entt::registry* reg)
{
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	vec3 camPos = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).GetPosition();
	ECS::GetComponent<Transform>(1).SetPosition(camPos + vec3(-180.f, 50.f, 0.f));
	ECS::GetComponent<Transform>(2).SetPosition(camPos + vec3(-180.f, 70.f, 0.f));
	ECS::GetComponent<Transform>(3).SetPosition(camPos + vec3(-180.f, 90.f, 0.f));
	if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetKill())
	{
		printf("player is dead");
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

void Stage3::GamepadStroke(XInputController* con)
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

void Stage3::GamepadStick(XInputController* con)
{
	Stick sticks[2];
	con->GetSticks(sticks);
}

void Stage3::GamepadTrigger(XInputController* con)
{
}

void Stage3::KeyboardHold()
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

void Stage3::KeyboardDown()
{
	
	auto& phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	vec3 curVelo = phsBod.GetVelocity();
	if (Input::GetKeyDown(Key::Space))
	{
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGrounded())
		{
			
			phsBod.SetVelocity(vec3(curVelo.x, 23.f, 0.f));
		}
	}
	if (Input::GetKeyDown(Key::F))
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ArrowShot(m_physicsWorld);
	}
}

void Stage3::KeyboardUp(void)
{
}

void Stage3::MouseMotion(SDL_MouseMotionEvent evnt)
{

}

void Stage3::MouseClick(SDL_MouseButtonEvent evnt)
{

}

void Stage3::MouseWheel(SDL_MouseWheelEvent evnt)
{
}