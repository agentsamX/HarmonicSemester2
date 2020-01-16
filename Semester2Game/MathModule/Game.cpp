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

	m_activeScene->Update();
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
	m_activeScene->GamepadStroke(con);
	//gamepad button press
	if (con->IsButtonStroked(Buttons::A))
	{
		printf("A stroked\n");
	}
}

void Game::GamepadUp(XInputController* con)
{
	m_activeScene->GamepadUp(con);
	//gamepad button up
	if (con->IsButtonReleased(Buttons::RB))
	{
		//printf("RB released\n");
	}
}

void Game::GamepadDown(XInputController* con)
{
	m_activeScene->GamepadDown(con);
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
	m_activeScene->GamepadStick(con);
}

void Game::GamepadTrigger(XInputController* con)
{
	m_activeScene->GamepadTrigger(con);
}

void Game::KeyboardHold()
{
	m_activeScene->KeyboardHold();
}

void Game::KeyboardDown()
{
	m_activeScene->KeyboardDown();
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
	m_activeScene->KeyboardUp();
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	m_activeScene->MouseMotion(evnt);
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
	m_activeScene->MouseClick(evnt);

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
	m_activeScene->MouseWheel(evnt);
	printf("mouse scroll %f\n", float(evnt.y));
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
