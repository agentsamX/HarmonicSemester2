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
	m_name = "Gaia's Grasp";
	m_clearColor = vec4(0.105, 0.105, 0.105, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//creates a new HelloWorld scene
	m_scenes.push_back(new MenuScene("Main Menu"));
	//sets active scene reference to our HelloWOrld scene
	m_activeScene = m_scenes[0];

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
		if (m_activeScene->GetDone())
		{
			
		}
		
		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			if (!ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetKill())
			{
				//Accept all input
				AcceptInput();
			}
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

	m_activeScene->Update(m_register);
	
	if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetKillTime()>3.f)
	{
		Game::ResetScene();
	}

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
	
}

void Game::GamepadUp(XInputController* con)
{
	m_activeScene->GamepadUp(con);
	//gamepad button up

}

void Game::GamepadDown(XInputController* con)
{
	m_activeScene->GamepadDown(con);
	
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
	

}

void Game::KeyboardUp()
{
	m_activeScene->KeyboardUp();
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
	if (Input::GetKeyUp(Key::P))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
	if (Input::GetKeyDown(Key::Zero))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new MenuScene("Main Menu"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 0;
	}
	if (Input::GetKeyDown(Key::One))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage1("First Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 1;
	}
	if (Input::GetKeyDown(Key::Two))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage2("Second Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 2;
	}
	if (Input::GetKeyDown(Key::Three))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage3("Third Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 2;
	}
	if (Input::GetKeyDown(Key::Four))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage4("Fourth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 1;
	}
	if (Input::GetKeyDown(Key::Five))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage5("Fifth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 3;
	}
	if (Input::GetKeyDown(Key::Six))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage6("Sixth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 4;
	}
	if (Input::GetKeyDown(Key::Seven))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage7("Seventh Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 5;
	}
	if (Input::GetKeyDown(Key::Eight))
	{
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage8("Eighth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		m_curScene = 6;
	}
	if (Input::GetKeyDown(Key::R))
	{
		Game::ResetScene();
	}
	if (Input::GetKeyDown(Key::OEMComma))
	{
		Game::AdvanceScene();
	}
	if (Input::GetKeyUp(Key::W))
	{
		if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGoalContact())
		{
			printf("advanced scene");
			Game::AdvanceScene();
		}
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	m_activeScene->MouseMotion(evnt);
	if (ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).GetGoalContact())
	{
		printf("advanced scene");
		Game::AdvanceScene();
	}
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

void Game::AdvanceScene()
{
	switch (m_curScene)
	{
	case 0:

		m_activeScene->~Scene();
		m_scenes.push_back(new Stage4("First Level"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 1:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage3("Second Level"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 2:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage5("Third Level"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 3:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage6("Fourth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 4:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage7("Fifth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 5:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage8("Sixth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	}
	m_curScene++;
	
}

void Game::ResetScene()
{
	switch (m_curScene)
	{
	case 0:
		
	case 1:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage4("First Level"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 2:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage3("Second Level"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 3:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage5("Third Level"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 4:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage6("Fourth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 5:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage7("Fifth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	case 6:
		m_activeScene->~Scene();
		m_scenes.push_back(new Stage8("Sixth Stage"));
		m_activeScene = m_scenes.back();
		m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_activeScene->GetScene();
		break;
	}
}
