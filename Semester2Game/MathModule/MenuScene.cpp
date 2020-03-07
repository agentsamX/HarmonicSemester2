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
		unsigned int bitHolder =EntityIdentifier::CameraBit();
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
}

void MenuScene::MouseWheel(SDL_MouseWheelEvent evnt)
{
}

