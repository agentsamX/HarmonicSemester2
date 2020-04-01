#include "EndScene.h"

EndScene::EndScene(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-0.3f));
	m_physicsWorld->SetGravity(m_gravity);
}

void EndScene::InitScene(float windowWidth, float windowHeight)
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
		std::string fileName = "UntilTheNextAdventure.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 300, 100);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0, 0.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Title Placeholder");
	}
	
}


void EndScene::Update(entt::registry* reg)
{
}

void EndScene::Routines()
{
}

void EndScene::GamepadStroke(XInputController* con)
{
}

void EndScene::GamepadStick(XInputController* con)
{
}

void EndScene::GamepadTrigger(XInputController* con)
{
}

void EndScene::KeyboardHold()
{
}

void EndScene::KeyboardDown()
{
}

void EndScene::KeyboardUp()
{
}

void EndScene::MouseMotion(SDL_MouseMotionEvent evnt)
{
}

void EndScene::MouseClick(SDL_MouseButtonEvent evnt)
{

}

void EndScene::MouseWheel(SDL_MouseWheelEvent evnt)
{
}

