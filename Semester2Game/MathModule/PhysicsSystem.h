#pragma once

#include "ECS.h"
#include "PhysicsBody.h"
#include "Timer.h"
#include "Shader.h"
struct Box
{
public:
	vec3 m_bottomLeft;
	vec3 m_bottomRight;
	vec3 m_topLeft;
	vec3 m_topRight;
	vec3 m_center;
};

struct Circle
{
public: 
	vec3 m_center;
	float m_radius;
};

namespace PhysicsSystem
{
	//updates the system
	void Update(entt::registry* reg, b2World& world);

	//run our collision detection
	//Box circle
	//box box
	void Run(b2World& world);

	bool BoxBoxCollision(std::pair<PhysicsBody&, Box> group1, std::pair<PhysicsBody&, Box> group2);

	static Shader physicsDrawShader;

	void Init();

	void Draw(entt::registry* reg);
}