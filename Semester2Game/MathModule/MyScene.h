#pragma once

#include "Scene.h"

class MyScene : public Scene
{
public:
	MyScene(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};