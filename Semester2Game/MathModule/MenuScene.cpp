#include "MenuScene.h"

MenuScene::MenuScene(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-0.3f));
	m_physicsWorld->SetGravity(m_gravity);
}

void MenuScene::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	//attach the register
	ECS::AttachRegister(m_sceneReg);

	//sets up aspect ratio for camera
	float aspectRatio = windowWidth / windowHeight;
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

		ECS::AttachComponent<Player>(entity);
		
		unsigned int bitHolder = 0x0;
		ECS::SetUpIdentifier(entity, bitHolder, "DummyPlayer");
		ECS::SetIsMainPlayer(entity, true);
	}
	{
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<Sprite>(entity);
		std::string fileName = "gaiatitle.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 300, 150);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 51.f, 0.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Title Placeholder");
	}
	{
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<Sprite>(entity);
		std::string fileName = "Play.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 48);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -21.f, 0.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Menu Item 1");
	}
	/*
	{
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<Sprite>(entity);
		std::string fileName = "box.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 150, 100);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -30.f, 0.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Menu Item 2");
	}
	*/
	{
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<Sprite>(entity);
		std::string fileName = "Exit.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 48);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -71.f, 0.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Menu Item 3");
	}
}


void MenuScene::Update(entt::registry* reg)
{
}

void MenuScene::Routines()
{
}

void MenuScene::GamepadStroke(XInputController* con)
{
}

void MenuScene::GamepadStick(XInputController* con)
{
}

void MenuScene::GamepadTrigger(XInputController* con)
{
}

void MenuScene::KeyboardHold()
{
}

void MenuScene::KeyboardDown()
{
}

void MenuScene::KeyboardUp()
{
}

void MenuScene::MouseMotion(SDL_MouseMotionEvent evnt)
{
}

void MenuScene::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (evnt.x > 367&&evnt.x<1169&&evnt.y>313&&evnt.y<429)
	{
		ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetContactingGoal(true);
	}
	else if (evnt.x > 468 && evnt.x < 1067 && evnt.y>465 && evnt.y < 583)
	{
		printf("This button does nothing right now, should I make it a level select?\n");
	}
	else if (evnt.x > 568 && evnt.x < 967 && evnt.y>629 && evnt.y < 746)
	{
		exit(0);
	}

}

void MenuScene::MouseWheel(SDL_MouseWheelEvent evnt)
{
}

