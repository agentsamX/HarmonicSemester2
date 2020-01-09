#include "Game.h"

#include <random>


Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	m_name = "Hello World";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//creates a new HelloWorld scene
	m_scenes.push_back(new HelloWorld("Horizontal scrolling scene"));
	m_scenes.push_back(new MyScene("My Scene"));
	m_scenes.push_back(new HelloWorld("Second Loaded Scene"));
	m_scenes.push_back(new AssignScene1("Scene for assignment 1"));
	//sets active scene reference to our HelloWOrld scene
	m_activeScene = m_scenes[3];

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	//sets m_register to point to the register in the active scene

	PhysicsSystem::Init();

	m_register = m_activeScene->GetScene();
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();
		Routines();
		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);

	//updates physics
	PhysicsSystem::Update(m_register, m_activeScene->GetPhysicsWorld());
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::Routines()
{/*
	vec3 positionEn1 = m_register->get<Transform>(5).GetPosition();
	vec3 positionEn2 = m_register->get<Transform>(6).GetPosition();
	vec2 acceleration = vec2(0,0);

	if (positionEn1.y < 40.3)
	{
		m_velocityEn1.y = 10.f;
		m_register->get<AnimationController>(5).SetActiveAnim(1);
	}
	else if (positionEn1.y > 90.3)
	{
		m_velocityEn1.y = -10.f;
		m_register->get<AnimationController>(5).SetActiveAnim(0);
	}
	if (positionEn2.x < -55)
	{
		acceleration.x = 10.f;
		m_register->get<AnimationController>(6).SetActiveAnim(0);
	}
	else if (positionEn2.x > 35)
	{
		acceleration.x = -10.f;
		m_register->get<AnimationController>(6).SetActiveAnim(1);
	}
	m_velocityEn2 = m_velocityEn2 + acceleration * Timer::deltaTime;
	positionEn1 = positionEn1+ vec3(vec3(m_velocityEn1.x, m_velocityEn1.y, 0.f) * Timer::deltaTime);
	positionEn2 = positionEn2 + (vec3(m_velocityEn2.x, m_velocityEn2.y, 0.f) * Timer::deltaTime)
		+ (vec3(acceleration.x, acceleration.y, 0.f) * 0.5f * (Timer::deltaTime * Timer::deltaTime));
	
	m_register->get<Transform>(5).SetPosition(positionEn1);
	m_register->get<Transform>(6).SetPosition(positionEn2);
	*/
}

void Game::AcceptInput()
{
	XInputManager::Update();
	//Just calls all the other input functions 
	GamepadInput();

	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::GamepadInput()
{
	XInputController* tempCon;
	//gamepad button stroked(pressed)
	for (int i = 0; i < 3; i++)
	{
		if (XInputManager::ControllerConnected(i))
		{
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);

			//if the controller is connected we run the different input types
			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);
		}
	}
}

void Game::GamepadStroke(XInputController* con)
{
	//gamepad button press
	if (con->IsButtonStroked(Buttons::A))
	{
		printf("A stroked\n");
	}
}

void Game::GamepadUp(XInputController* con)
{
	//gamepad button up
	if (con->IsButtonReleased(Buttons::RB))
	{
		//printf("RB released\n");
	}
}

void Game::GamepadDown(XInputController* con)
{
	//gamepad button down
	if (con->IsButtonPressed(Buttons::THUMB_LEFT))
	{
		printf("Left Thumbsticked Clicked In\n");
	}
	if (con->IsButtonPressed(Buttons::DPAD_UP))
	{
		printf("Up press registered\n");
	}
	if (con->IsButtonPressed(Buttons::DPAD_LEFT))
	{
		printf("Left press registered\n");
	}
	if (con->IsButtonPressed(Buttons::DPAD_RIGHT))
	{
		printf("Right press registered\n");
	}
	if (con->IsButtonPressed(Buttons::DPAD_DOWN))
	{
		printf("Down press registered\n");
	}
}

void Game::GamepadStick(XInputController* con)
{
	auto& look = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());
	auto& phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	float angle;
	vec2 friction;
	bool moving = false;
	//Gamepad stick stuffs
	Stick sticks[2];
	con->GetSticks(sticks);

	vec2 totalForce = vec2(0.f, 0.f);
	if (sticks[0].y > 0.3f)
	{
		phsBod.ApplyForce(vec3(0.f,20.f,0.f));
	}
	if (sticks[0].x < -0.3f)
	{
		phsBod.ApplyForce(vec3(-20.f,0.f, 0.f));
	}
	if (sticks[0].x > 0.3f)
	{
		phsBod.ApplyForce(vec3(20.f,0.f, 0.f));
	}
	if (sticks[0].y < -0.3f)
	{
		phsBod.ApplyForce(vec3(0.f, -20.f, 0.f));
	}
	

	
	if (sticks[1].x > 0.3f && sticks[1].y > 0.3f)
	{
		angle = PI - PI/4;
		look.SetRotationAngleZ(angle);
	}
	else if (sticks[1].x < -0.3f && sticks[1].y > 0.3f)
	{
		angle = PI + PI/4;
		look.SetRotationAngleZ(angle);
	}
	else if(sticks[1].y < -0.3f&& sticks[1].x > 0.3f)
	{
		angle = PI/4;
		look.SetRotationAngleZ(angle);
	}
	else if(sticks[1].y < -0.3f&& sticks[1].x < -0.3f)
	{
		angle = 2*PI -PI/4;
		look.SetRotationAngleZ(angle);
	}
	else if (sticks[1].y > 0.3f)
	{
		//printf("Up Pointing\n");
		angle = PI;
		look.SetRotationAngleZ(angle);
	}
	else if (sticks[1].x < -0.3f)
	{
		//printf("Left Pointing\n");
		angle = PI/2 + PI;
		look.SetRotationAngleZ(angle);
	}
	else if (sticks[1].x > 0.3f)
	{
		//printf("Right Pointing\n");
		angle = PI/2;
		look.SetRotationAngleZ(angle);
	}
	else if (sticks[1].y < -0.3f)
	{
		//printf("Down Pointing\n");
		angle = 0;
		look.SetRotationAngleZ(angle);
	}
}

void Game::GamepadTrigger(XInputController* con)
{
	Triggers triggers;
	con->GetTriggers(triggers);

	if (triggers.RT > 0.5f && triggers.RT < 0.8f)
	{
		printf("Half press\n");
	}
	if (triggers.RT > 0.8f)
	{
		printf("Full press\n");
	}
}

void Game::KeyboardHold()
{
	//Keyboard button held
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	auto& phsBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());

	auto& look = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());
	float angle;
	vec2 totalForce = vec2(0.f, 0.f);
	bool moving = false;

	float speed = 30.f;
	if (Input::GetKey(Key::In::UpArrow)&&Input::GetKey(Key::In::RightArrow))
	{
		angle = PI - PI / 4;
		look.SetRotationAngleZ(angle);
	}
	else if (Input::GetKey(Key::In::UpArrow) && Input::GetKey(Key::In::LeftArrow))
	{
		angle = PI + PI / 4;
		look.SetRotationAngleZ(angle);
	}
	else if (Input::GetKey(Key::In::DownArrow) && Input::GetKey(Key::In::RightArrow))
	{
		angle = PI / 4;
		look.SetRotationAngleZ(angle);
	}
	else if (Input::GetKey(Key::In::DownArrow) && Input::GetKey(Key::In::LeftArrow))
	{
		angle = 2 * PI - PI / 4;
		look.SetRotationAngleZ(angle);
	}
	else if (Input::GetKey(Key::In::UpArrow))
	{
		//printf("Up Pointing\n");
		angle = PI;
		look.SetRotationAngleZ(angle);
	}
	else if (Input::GetKey(Key::In::LeftArrow))
	{
		//printf("Left Pointing\n");
		angle = PI / 2 + PI;
		look.SetRotationAngleZ(angle);
	}
	else if (Input::GetKey(Key::In::RightArrow))
	{
		//printf("Right Pointing\n");
		angle = PI / 2;
		look.SetRotationAngleZ(angle);
	}
	else if (Input::GetKey(Key::In::DownArrow))
	{
		//printf("Down Pointing\n");
		angle = 0;
		look.SetRotationAngleZ(angle);
	}
	if (Input::GetKey(Key::W))
	{
		phsBod.ApplyForce(vec3(0.f, 800.f, 0.f));
	}
	if (Input::GetKey(Key::A))
	{
		phsBod.ApplyForce(vec3(-800.f, 0.f, 0.f));
	}
	if (Input::GetKey(Key::S))
	{
		phsBod.ApplyForce(vec3(0.f, -800.f, 0.f));
	}
	if (Input::GetKey(Key::D))
	{
		phsBod.ApplyForce(vec3(800.f, 0.f, 0.f));
	}
}

void Game::KeyboardDown()
{
	//Keyboard button down
	if (Input::GetKeyDown(Key::F4))
	{
		printf("F4 key pressed\n");
	}
	if (Input::GetKeyDown(Key::Enter))
	{
		printf("Enter has been pressed");

	}

}

void Game::KeyboardUp()
{
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}

	if (Input::GetKeyUp(Key::K))
	{
		//switches between ken's two animations
		auto& animController = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
		if (animController.GetActiveAnim() == 0)
		{
			animController.SetActiveAnim(1);
		}
		else
		{
			animController.SetActiveAnim(0);
		}
	}
	/*if (Input::GetKeyUp(Key::W))
	{
		auto& transKen = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());
		transKen.SetPosition(vec3(transKen.GetPosition().x, transKen.GetPosition().y + 1, transKen.GetPosition().z));
	}*/
	if (Input::GetKeyUp(Key::P))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		printf("Left mouse clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		printf("Right mouse clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
	{
		printf("Middle mouse clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
	}
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	printf("mouse scroll %f\n", float(evnt.y));
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
