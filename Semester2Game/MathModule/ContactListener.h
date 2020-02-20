#pragma once
#include "Box2D/Box2D.h"
#include "ECS.h"
class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) {

        int entA = (contact->GetFixtureA()->GetBody()->GetEntityNumber());
        int entB = (contact->GetFixtureB()->GetBody()->GetEntityNumber());
        /*if (entA == EntityIdentifier::MainPlayer() && ECS::GetComponent<Transform>(entA).GetPositionY() >
            ECS::GetComponent<Transform>(entB).GetPositionY() + ECS::GetComponent<Sprite>(entB).GetHeight() / 2 + ECS::GetComponent<Sprite>(entA).GetHeight() / 2)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetGrounded(true);
        }*/
        //ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetGrounded(true);

    }

    void EndContact(b2Contact* contact) {

        
        printf("contact ended");
       
    }
};