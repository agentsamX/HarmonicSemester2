#pragma once

#include "Scene.h"

class AssignScene1 : public Scene
{
public:
	AssignScene1(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};