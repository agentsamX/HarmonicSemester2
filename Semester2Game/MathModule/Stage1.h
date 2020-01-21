#pragma once

#include "Scene.h"

class Stage1 : public Scene
{
public:
	Stage1(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

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