#pragma once

#include <GL/glew.h>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2ContactManager.h>
#include "JSON.h"
#include "EntityIdentifier.h"
#include "Vector.h"
#include "VertexManager.h"
#include "Transform.h"

enum class BodyType
{
	BOX,
	CIRCLE,

	NUM_TYPES
};

struct CollisionIDs
{
public:
	//gets the different IDs
	static unsigned int Player();
	static unsigned int Environment();
	static unsigned int Enemy();
private:
	//holds the IDs
	static unsigned int m_playerID;
	static unsigned int m_environmentID;
	static unsigned int m_enemyID;
};

class PhysicsBody
{
public:
	PhysicsBody() { };
	PhysicsBody(b2Body* body, float radius, vec2 centerOffset, bool isDynamic  );
	PhysicsBody(b2Body* body, float width, float height, vec2 centerOffset, bool isDynamic);
	
	//updates physics stuff
	void Update(Transform* trans);

	//initializes body to draw
	void InitBody();

	void DrawBody();

	b2Body* GetBody() const;
	//gets body pos
	b2Vec2 GetPosition() const;
	//applys a force
	void ApplyForce(vec3 force);
	vec3 GetForce() const;
	vec3 GetAcceleration() const;
	float GetMaxVelo() const;
	vec3 GetVelocity() const;
	float GetFriction() const;

	static vec3 GetGravityAcceleration();
	bool GetGravity() const;

	float GetMass();

	BodyType GetBodyType() const;
	vec2 GetCenterOffset() const;
	vec2 GetBottomLeft() const;
	vec2 GetBottomRight() const;
	vec2 GetTopLeft() const;
	vec2 GetTopRight() const;
	float GetWidth() const;
	float GetHeight() const;
	float GetRadius() const;

	unsigned int GetBodyID() const;
	unsigned int GetCollideID() const;

	bool GetDynamic() const;

	static bool GetDraw();

	void SetBody(b2Body* body);
	void SetPosition(b2Vec2 bodyPos);
	//setters
	void SetForce(vec3 force);
	void SetAcceleration(vec3 accel);
	void SetMaxVelo(float velo);
	void SetVelocity(vec3 velo);
	void SetFriction(float fric);

	static void SetGravityAcceleration(vec3 grav);
	void SetGravity(bool grav);

	void SetMass(float mass);

	void SetBodyType(BodyType type);
	void SetCenterOffset(vec2 cent);
	void SetBottomLeft(vec2 BL);
	void SetBottomRight(vec2 BR);
	void SetTopLeft(vec2 TL);
	void SetTopRight(vec2 TR);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetRadius(float radius);

	void SetBodyID(unsigned int bodyID);
	void SetCollideID(unsigned int collideID);

	void SetDynamic(bool isDynamic);
	static void SetDraw(bool drawBodies);


private:
	//b2d bodies
	b2Body* m_body = nullptr;
	b2Vec2 m_position = b2Vec2(0.f, 0.f);
	//the applied force
	vec3 m_appliedForce = vec3(0.f, 0.f, 0.f);
	//the frictional force
	vec3 m_frictionalForce = vec3(0.f, 0.f, 0.f);
	//stores net force
	vec3 m_netForce = vec3(0.f, 0.f, 0.f);
	//stores accel
	vec3 m_acceleration = vec3(0.f, 0.f, 0.f);
	//Max velo in each axes
	float m_maxVelo = 20.f;
	//stores velo
	vec3 m_velocity = vec3(0.f, 0.f, 0.f);

	//coefficient of friction
	float m_friction = 0.35f;

	//the acceleration due to gravity*mass
	static vec3 m_gravityAcceleration;
	bool m_applyGravity = false;

	//mass of body
	float m_mass = 1.f;

	//body type
	BodyType m_bodyType = BodyType::CIRCLE;
	//how far from center of sprite it is
	vec2 m_centerOffset = vec2();
	//eachcorner
	vec2 m_bottomLeft = vec2();
	vec2 m_bottomRight = vec2();
	vec2 m_topLeft = vec2();
	vec2 m_topRight = vec2();
	//width and height
	float m_width = 0.f;
	float m_height = 0.f;

	float m_radius = 0.f;

	//the type of the body
	unsigned int m_bodyID;
	//the types it collides with
	unsigned int m_collideID;

	//is the oobject non-moving
	bool m_dynamic = false;

	//do you draw bodies
	static bool m_drawBodies;

	//physics body drawing
	GLuint m_vao = GL_NONE;
	GLuint m_vboPos = GL_NONE;
};
inline void to_json(nlohmann::json& j, const PhysicsBody& phys)
{
	j["BodyPosition"] = { phys.GetPosition().x,phys.GetPosition().y };
	//Stores body type 
	j["BodyType"] = phys.GetBodyType();
	//Center offset 
	j["CenterOffset"] = { phys.GetCenterOffset().x, phys.GetCenterOffset().y };
	//Stores corners
	j["BottomLeft"] = { phys.GetBottomLeft().x, phys.GetBottomLeft().y };
	j["BottomRight"] = { phys.GetBottomRight().x, phys.GetBottomRight().y };
	j["TopLeft"] = { phys.GetTopLeft().x, phys.GetTopLeft().y };
	j["TopRight"] = { phys.GetTopRight().x, phys.GetTopRight().y };
	//height and width
	j["Width"] = phys.GetWidth();
	j["Height"] = phys.GetHeight();
	//Radius
	j["Radius"] = phys.GetRadius();
	//Max velocity
	j["MaxVelo"] = phys.GetMaxVelo();
	//Friction strength
	j["Friction"] = phys.GetFriction();
	//Gravity enabled?
	j["Gravity"] = phys.GetGravity();
	//Collision type (body id) and what this body collides *with*
	j["BodyID"] = phys.GetBodyID();
	j["CollideID"] = phys.GetCollideID();
	//Sets whether the object is moving 
	j["IsDynamic"] = phys.GetDynamic();

}
inline void from_json(const nlohmann::json& j, PhysicsBody& phys)
{
	phys.SetPosition(b2Vec2(j["BodyPosition"][0], j["bodyPosition"][1]));
	//Sets body type
	phys.SetBodyType(j["BodyType"]);
	//Set the center offset 
	phys.SetCenterOffset(vec2(j["CenterOffset"][0], j["CenterOffset"][1]));
	//Sets corners
	phys.SetBottomLeft(vec2(j["BottomLeft"][0], j["BottomLeft"][1]));
	phys.SetBottomRight(vec2(j["BottomRight"][0], j["BottomRight"][1]));
	phys.SetTopLeft(vec2(j["TopLeft"][0], j["TopLeft"][1]));
	phys.SetTopRight(vec2(j["TopRight"][0], j["TopRight"][1]));
	//Set wto-_ and height 
	phys.SetWidth(j["Width"]);
	phys.SetHeight(j["Height"]);
	//Set radius
	phys.SetRadius(j["Radius"]);
	//Sets Max velncity
	phys.SetMaxVelo(j["MaxVelo"]);
	//Sets Friction strength
	phys.SetFriction(j["Friction"]);
	//Set does gravity affect this body?
	phys.SetGravity(j["Gravity"]);
	//Set collision type (body id) and what this body collides *with* 
	phys.SetBodyID(j["BodyID"]);
	phys.SetCollideID(j["CollideID"]);
	//Set whether or not the object is moving 
	phys.SetDynamic(j["IsDynamic"]);
}