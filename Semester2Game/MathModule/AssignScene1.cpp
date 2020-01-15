#include "AssignScene1.h"

AssignScene1::AssignScene1(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-0.3f));
	m_physicsWorld->SetGravity(m_gravity);
}

void AssignScene1::InitScene(float windowWidth, float windowHeight)
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
		unsigned int bitHolder = EntityIdentifier::VertScrollCameraBit() || EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	}
	/*{
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "megaSheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//adds first animation
		animController.AddAnimation(Animation());
		//sets active animation
		animController.SetActiveAnim(0);
		//gets first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0.f, 32.f), vec2(31.f, 1.f));
		anim.AddFrame(vec2(35.f, 32.f), vec2(67.f, 1.f));
		anim.AddFrame(vec2(69.f, 32.f), vec2(101.f, 1.f));
		anim.AddFrame(vec2(35.f, 32.f), vec2(67.f, 1.f));
		//makes it repeat
		anim.SetRepeating(true);
		//sets time between frames
		anim.SetSecPerFrame(0.1667f);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 64, 64, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(200.f, -60.f, 10.f));


		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "MegaMan");
	}
	{
		auto attacks = File::LoadJSON("kenAnim.json");
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "kenOver.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//adds first animation
		animController.AddAnimation(attacks["KenIdle"]);
		animController.AddAnimation(attacks["KenHado"]);
		animController.SetActiveAnim(1);
		//gets first animation
		auto& anim = animController.GetAnimation(1);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 30, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(15.f, 20.f, 10.f));
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Ken");
		ECS::SetIsMainPlayer(entity, true);
	}*/
	/*{
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//sets up components
		std::string fileName = "contraTopSheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		animController.AddAnimation(Animation());
		animController.AddAnimation(Animation());
		animController.SetActiveAnim(0);
		//adds first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(45.f, 10.f), vec2(72.f, 40.f));
		anim.AddFrame(vec2(73.f, 13.f), vec2(99.f, 40.f));
		anim.AddFrame(vec2(100.f, 13.f), vec2(127.f, 40.f));
		anim.AddFrame(vec2(73.f, 13.f), vec2(99.f, 40.f));
		anim.SetRepeating(true);
		//sets time between frames
		anim.SetSecPerFrame(0.1667f);
		auto& anim2 = animController.GetAnimation(1);
		anim2.AddFrame(vec2(146.f, 10.f), vec2(172.f, 40.f));
		anim2.AddFrame(vec2(145.f, 10.f), vec2(171.f, 40.f));
		anim2.AddFrame(vec2(144.f, 10.f), vec2(170.f, 40.f));
		anim2.AddFrame(vec2(145.f, 10.f), vec2(171.f, 40.f));
		anim2.AddFrame(vec2(146.f, 10.f), vec2(172.f, 40.f));
		anim2.AddFrame(vec2(147.f, 10.f), vec2(173.f, 40.f));
		anim2.AddFrame(vec2(148.f, 10.f), vec2(174.f, 40.f));
		anim2.AddFrame(vec2(147.f, 10.f), vec2(173.f, 40.f));
		anim2.SetRepeating(true);
		//sets time between frames
		anim2.SetSecPerFrame(0.05f);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-5.f, 40.f, 10.f));
		//sets up physics
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		
		tempPhsBody = PhysicsBody(tempBody,float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			 true);
		tempPhsBody.SetGravity(false);
		tempPhsBody.SetFriction(0.3f);

		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit()|EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "contra");
		
	}*//*
	{
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//sets up components
		std::string fileName = "TlozBGR1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200, 200);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -1));
		


		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Dark Background");
	}
	{
		//creates entity
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "guardSheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		animController.AddAnimation(Animation());
		animController.AddAnimation(Animation());
		animController.SetActiveAnim(0);
		//adds first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(16.f, 16.f), vec2(0.f, 0.f));
		anim.AddFrame(vec2(35.f, 16.f), vec2(19.f, 0.f));
		anim.SetRepeating(true);
		//sets time between frames
		anim.SetSecPerFrame(0.1667f);
		auto& anim2 = animController.GetAnimation(1);
		anim2.AddFrame(vec2(77.f, 16.f), vec2(62.f, 0.f));
		anim2.AddFrame(vec2(94.f, 16.f), vec2(79.f, 0.f));
		anim2.SetRepeating(true);
		//sets time between frames
		anim2.SetSecPerFrame(0.1667f);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-52.6f, 92.6f, 10.f));
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "guard");
	}
	{
		//creates entity
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "guardSheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		animController.AddAnimation(Animation());
		animController.AddAnimation(Animation());
		animController.SetActiveAnim(0);
		//adds first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(47.f, 16.f), vec2(35.f, 0.f));
		anim.AddFrame(vec2(60.f, 16.f), vec2(48.f, 0.f));
		anim.SetRepeating(true);
		//sets time between frames
		anim.SetSecPerFrame(0.1667f);
		auto& anim2 = animController.GetAnimation(1);
		anim2.AddFrame(vec2(35.f, 16.f), vec2(47.f, 0.f));
		anim2.AddFrame(vec2(48.f, 16.f), vec2(60.f, 0.f));
		anim2.SetRepeating(true);
		//sets time between frames
		anim2.SetSecPerFrame(0.1667f);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 12, 16, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-60.f, -10.f, 10.f));
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "sideguard");
	}
	{
		//creates entity
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "fireball.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		animController.AddAnimation(Animation());
		animController.AddAnimation(Animation());
		animController.SetActiveAnim(0);
		//adds first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0.f, 0.f), vec2(32.f, 32.f));
		anim.AddFrame(vec2(32.f, 32.f), vec2(64.f, 64.f));
		anim.AddFrame(vec2(64.f, 64.f), vec2(96.f, 96.f));
		anim.AddFrame(vec2(96.f, 96.f), vec2(128.f, 128.f));

		anim.SetRepeating(true);
		//sets time between frames
		anim.SetSecPerFrame(0.15f);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(60.f, 15.f, 10.f));
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "fireball");
	}
	{
		//creates entity
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//sets up components
		std::string fileName = "whirlpool.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		animController.AddAnimation(Animation());
		animController.SetActiveAnim(0);
		//adds first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0.f, 0.f), vec2(64.f, 64));
		anim.AddFrame(vec2(68.f, 0.f), vec2(131.f, 64.f));
		anim.AddFrame(vec2(133.f, 0.f), vec2(197.f, 64.f));
		anim.AddFrame(vec2(199.f, 0.f), vec2(263.f, 64.f));
		anim.AddFrame(vec2(265.f, 0.f), vec2(329.f, 64.f));
		anim.AddFrame(vec2(331.f, 0.f), vec2(395.f, 64.f));
		anim.AddFrame(vec2(397.f, 0.f), vec2(461.f, 64.f));

		anim.SetRepeating(true);
		//sets time between frames
		anim.SetSecPerFrame(0.1f);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-4.9f, -82.5f, 10.f));
		//collision settings
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans= ECS::GetComponent<Transform>(entity);
		
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);



		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit()|EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "WhirlPool");
	}*/
	{
		auto entity = ECS::CreateEntity();
		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
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
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));
		tempBody = m_physicsWorld->CreateBody(&tempDef);
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
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f),
			true);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "floor");
	}
ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}
void AssignScene1::Update()
{
	Routines();
}

void AssignScene1::Routines()
{
}

void AssignScene1::GamepadStroke(XInputController* con)
{
}

void AssignScene1::GamepadStick(XInputController* con)
{

}

void AssignScene1::GamepadTrigger(XInputController* con)
{

}

void AssignScene1::KeyboardHold()
{

}

void AssignScene1::KeyboardDown()
{

}

void AssignScene1::KeyboardUp()
{
}

void AssignScene1::MouseMotion(SDL_MouseMotionEvent evnt)
{

}

void AssignScene1::MouseClick(SDL_MouseButtonEvent evnt)
{

}

void AssignScene1::MouseWheel(SDL_MouseWheelEvent evnt)
{
}

