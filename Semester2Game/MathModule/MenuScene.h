#pragma once

#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update(entt::registry* reg) override;

	void Routines();

	void GamepadStroke(XInputController* con) override;
	void GamepadStick(XInputController* con) override;
	void GamepadTrigger(XInputController* con) override;
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void MouseMotion(SDL_MouseMotionEvent evnt) override;
	void MouseClick(SDL_MouseButtonEvent evnt) override;
	void MouseWheel(SDL_MouseWheelEvent evnt) override;
	
	
};