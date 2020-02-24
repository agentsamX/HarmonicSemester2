#include "PhysicsBody.h"

unsigned int CollisionIDs::m_playerID		 = 0x00000001;
unsigned int CollisionIDs::m_environmentID   = 0x00000010;
unsigned int CollisionIDs::m_enemyID         = 0x00000100;


unsigned int CollisionIDs::Player()
{
	return m_playerID;
}

unsigned int CollisionIDs::Environment()
{
	return m_environmentID;
}

unsigned int CollisionIDs::Enemy()
{
	return m_enemyID;
}

vec3 PhysicsBody::m_gravityAcceleration = vec3(0.f, -35.f, 0.f);
bool PhysicsBody::m_drawBodies = false;


void PhysicsBody::SetForce(vec3 force)
{
	m_appliedForce = force;
}

void PhysicsBody::SetAcceleration(vec3 accel)
{
	m_acceleration = accel;
}

void PhysicsBody::SetMaxVelo(float velo)
{
	m_maxVelo = velo;
}

void PhysicsBody::SetVelocity(vec3 velo)
{
	m_body->SetLinearVelocity(b2Vec2(float32(velo.x), float32(velo.y)));
}

void PhysicsBody::SetFriction(float fric)
{
	m_friction = fric;
}

void PhysicsBody::SetGravityAcceleration(vec3 grav)
{
	m_gravityAcceleration = grav;
}

void PhysicsBody::SetGravity(bool grav)
{
	m_applyGravity = grav;
}

void PhysicsBody::SetMass(float mass)
{
	m_mass = mass;
}

void PhysicsBody::SetBodyType(BodyType type)
{
	m_bodyType = type;
}

void PhysicsBody::SetCenterOffset(vec2 cent)
{
	m_centerOffset = cent;
}

void PhysicsBody::SetBottomLeft(vec2 BL)
{
	m_bottomLeft = BL;
}

void PhysicsBody::SetBottomRight(vec2 BR)
{
	m_bottomRight = BR;
}

void PhysicsBody::SetTopLeft(vec2 TL)
{
	m_topLeft = TL;
}

void PhysicsBody::SetTopRight(vec2 TR)
{
	m_topRight = TR;
}

void PhysicsBody::SetWidth(float width)
{
	m_width = width;
}

void PhysicsBody::SetHeight(float height)
{
	m_height = height;
}

void PhysicsBody::SetRadius(float radius)
{
	m_radius = radius;
}

void PhysicsBody::SetBodyID(unsigned int bodyID)
{
	m_bodyID = bodyID;
}

void PhysicsBody::SetCollideID(unsigned int collideID)
{
	m_collideID = collideID;
}

void PhysicsBody::SetDynamic(bool isDynamic)
{
	m_dynamic = isDynamic;
}

void PhysicsBody::SetDraw(bool drawBodies)
{
	m_drawBodies = drawBodies;
}

PhysicsBody::PhysicsBody(b2Body* body, float radius, vec2 centerOffset, bool isDynamic)
{
	//bodies dont ref a shape
	// they need a shape linked to fixture
	b2CircleShape  tempShape;
	tempShape.m_p = b2Vec2(float32(centerOffset.x), float32(centerOffset.y));
	tempShape.m_radius = radius;

	b2FixtureDef tempFixture;
	tempFixture.shape = &tempShape;
	tempFixture.density = 1.f;
	tempFixture.friction = 0.3f;

	m_body = body;
	m_body->CreateFixture(&tempFixture);

	m_body = body;
	m_bodyType = BodyType::CIRCLE;

	//stores pos
	m_position = m_body->GetPosition();

	m_width = radius*2.f;
	m_height = radius*2.f;

	m_centerOffset = centerOffset;
	m_bottomLeft = vec2(centerOffset.x - (radius), centerOffset.y - (radius));
	m_bottomRight = vec2(centerOffset.x + (radius), centerOffset.y - (radius));
	m_topLeft = vec2(centerOffset.x - (radius), centerOffset.y + (radius));
	m_topRight = vec2(centerOffset.x + (radius), centerOffset.y + (radius));

	m_dynamic = isDynamic;

	InitBody();
}

PhysicsBody::PhysicsBody(b2Body* body, float width, float height, vec2 centerOffset, bool isDynamic)
{
	b2PolygonShape  tempShape;
	tempShape.SetAsBox(float32(width / 2.f), float32(height / 2.f),
		b2Vec2(float32(centerOffset.x), float32(centerOffset.y)), float32(0.f));

	b2FixtureDef tempFixture;
	tempFixture.shape = &tempShape;
	tempFixture.density = 1.f;
	tempFixture.friction = 0.3f;

	m_body = body;
	m_body->CreateFixture(&tempFixture);

	m_body = body;
	m_bodyType = BodyType::BOX;

	m_width = width;
	m_height = height;

	m_centerOffset = centerOffset;
	m_bottomLeft = vec2(centerOffset.x - (width/2.f), centerOffset.y - (height/2.f));
	m_bottomRight = vec2(centerOffset.x + (width / 2.f), centerOffset.y - (height / 2.f));
	m_topLeft = vec2(centerOffset.x - (width / 2.f), centerOffset.y + (height / 2.f));
	m_topRight = vec2(centerOffset.x + (width / 2.f), centerOffset.y + (height / 2.f));

	m_dynamic = isDynamic;

	InitBody();
}

void PhysicsBody::Update(Transform* trans)
{
	//stores position
	m_position = m_body->GetPosition();

	//sets transform to body
	trans->SetPosition(vec3(m_body->GetPosition().x, m_body->GetPosition().y, trans->GetPosition().z));
	trans->SetRotationAngleZ(Degrees(m_body->GetAngle()));
}

void PhysicsBody::InitBody()
{
	m_vao = VertexManager::CreateVAO();
	glBindVertexArray(m_vao);

	//enable slot 0
	glEnableVertexAttribArray(0);    //vertices

	//vbo positions
	m_vboPos = VertexManager::GetPlaneVertVBO();
	//pushes away warning
#pragma warning(push)
#pragma warning(disable : 4312)
	//bind pos biffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
	//sets attrib pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
#pragma warning(pop)

	//unbinds buffers
	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);
}

void PhysicsBody::DrawBody()
{
	//bind vao
	glBindVertexArray(m_vao);
	//draw the points
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//unbind vao
	glBindVertexArray(GL_NONE);
}

b2Body* PhysicsBody::GetBody() const
{
	return m_body;
}

b2Vec2 PhysicsBody::GetPosition() const
{
	return b2Vec2();
}

void PhysicsBody::ApplyForce(vec3 force)
{
	m_body->ApplyForce(b2Vec2(float32(force.x), float32(force.y)),
		b2Vec2(float32(m_body->GetPosition().x), float32(m_body->GetPosition().y)),
		true);
}

vec3 PhysicsBody::GetForce() const
{
	return vec3(m_appliedForce);
}

vec3 PhysicsBody::GetAcceleration() const
{
	return vec3(m_acceleration);
}

float PhysicsBody::GetMaxVelo() const
{
	return m_maxVelo;
}

vec3 PhysicsBody::GetVelocity() const
{
	return vec3(m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y,0.f);
}

float PhysicsBody::GetFriction() const
{
	return m_friction;
}

vec3 PhysicsBody::GetGravityAcceleration()
{
	return vec3(m_gravityAcceleration);
}

bool PhysicsBody::GetGravity() const
{
	return m_applyGravity;
}

float PhysicsBody::GetMass()
{
	return m_mass;
}

BodyType PhysicsBody::GetBodyType() const
{
	return BodyType(m_bodyType);
}

vec2 PhysicsBody::GetCenterOffset() const
{
	return vec2(m_centerOffset);
}

vec2 PhysicsBody::GetBottomLeft() const
{
	return vec2(m_bottomLeft);
}

vec2 PhysicsBody::GetBottomRight() const
{
	return vec2(m_bottomRight);
}

vec2 PhysicsBody::GetTopLeft() const
{
	return vec2(m_topLeft);
}

vec2 PhysicsBody::GetTopRight() const
{
	return vec2(m_topRight);
}

float PhysicsBody::GetWidth() const
{
	return m_width;
}

float PhysicsBody::GetHeight() const
{
	return m_height;
}

float PhysicsBody::GetRadius() const
{
	return m_radius;
}

unsigned int PhysicsBody::GetBodyID() const
{
	return m_bodyID;
}

unsigned int PhysicsBody::GetCollideID() const
{
	return m_collideID;
}

bool PhysicsBody::GetDynamic() const
{
	return m_dynamic;
}

bool PhysicsBody::GetDraw()
{
	return m_drawBodies;
}

void PhysicsBody::SetBody(b2Body* body)
{
	m_body = body;
}

void PhysicsBody::SetPosition(b2Vec2 bodyPos)
{
	m_position = bodyPos;
}
