#include "HelloWorld.h"

HelloWorld::HelloWorld(std::string name)
	: Scene(name)
{
}


void HelloWorld::InitScene(float windowWidth, float windowHeight)
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
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<HorizontalScroll>(entity).SetOffset(15.f);
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::HoriScrollCameraBit()||EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Horizontal Scrolling Camera");
		ECS::SetIsMainCamera(entity, true);
	}
	//setup new entity
	/*{
		//creates entity
		auto entity = ECS::CreateEntity();

		//creates new orthographic camera
		ECS::AttachComponent<HealthBar>(entity);
		ECS::GetComponent<HealthBar>(entity).SetHealth(0.7f);

		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::HealthBarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "HealthBar Entity");
	}*/
	//setup new entity
	/*{
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//sets up components
		std::string fileName = "HelloWorld.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 50);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-40.f, -60.f, 100.f));
	

		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Hello World Sign");
	}*/

	/*{
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//sets up components
		std::string fileName = "redBird.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 100);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(40.f, 35.f, 30.f));


		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Angry Red Bird");
	}*/

	/*{
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//sets up components
		std::string fileName = "marioWorld.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 111, 120);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-40.f, 30.f, 40.f));


		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Small Mario");
	}*/

	/*{
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//sets up components
		std::string fileName = "linkMinish.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 75);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, -60.f, 10.f));


		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Minish Cap Link");
	}*/

	/*{
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "linkSheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//adds first animation
		animController.AddAnimation(Animation());
		//sets active animation
		animController.SetActiveAnim(0);
		//gets first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(241.f, 144.f), vec2(261.f, 120.f));
		anim.AddFrame(vec2(272.f, 144.f), vec2(290.f, 120.f));
		anim.AddFrame(vec2(301.f, 144.f), vec2(320.f, 120.f));
		anim.AddFrame(vec2(331.f, 144.f), vec2(350.f, 120.f));
		anim.AddFrame(vec2(361.f, 144.f), vec2(380.f, 120.f));
		anim.AddFrame(vec2(392.f, 144.f), vec2(410.f, 120.f));
		//makes it repeat
		anim.SetRepeating(true);
		//sets time between frames
		anim.SetSecPerFrame(0.1667f);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 75, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, -60.f, 10.f));
		

		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Link Run");
	}*/
	{
		auto attacks = File::LoadJSON("LinkAttacks.json");
		//creates entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "spritesheet.png";
		auto &animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//adds first animation
		animController.AddAnimation(attacks["AttackLeft"]);
		animController.SetActiveAnim(0);
		//gets first animation
		auto& anim = animController.GetAnimation(0);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 75, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, -60.f, 10.f));
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Link Attack");
		ECS::SetIsMainPlayer(entity, true);
	}
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}