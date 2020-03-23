#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    int entA = (contact->GetFixtureA()->GetBody()->GetEntityNumber());
    int entB = (contact->GetFixtureB()->GetBody()->GetEntityNumber());
    if (contact->GetFixtureA()->IsSensor())
    {
        void* fixtureUserData = contact->GetFixtureA()->GetUserData();
        int Btype = contact->GetFixtureB()->GetBody()->GetEntityType();
        if ((int)fixtureUserData == 1)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).Contacted();
            if (Btype == 6)
            {
                printf("player touched spikes on foot");
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
        else if ((int)fixtureUserData == 2)
        {
            if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactLeft();
            }
            if (Btype == 5)
            {
                printf("player touched enemy on side");
                if (ECS::GetComponent<BlockEnemy>(entB).GetActive())
                {
                    ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
                }
            }
            else if (Btype == 9)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
        else if ((int)fixtureUserData == 3)
        {   
            if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactRight();
            }
            if (Btype==5)
            {
                printf("player touched enemy on side");
                if (ECS::GetComponent<BlockEnemy>(entB).GetActive())
                {
                    ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
                }
            }
            else if (Btype == 9)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
        else if ((int)fixtureUserData == 4)
        {
            if (Btype == 6)
            {
                printf("player touched spikes on head");
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
    }
    if (contact->GetFixtureB()->IsSensor())
    {
        void* fixtureUserData = contact->GetFixtureB()->GetUserData();
        int Atype = contact->GetFixtureB()->GetBody()->GetEntityType();
        if ((int)fixtureUserData == 1)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).Contacted();
            if (Atype == 6)
            {
                printf("player touched spikes on foot");
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
        else if ((int)fixtureUserData == 2)
        {
            if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactLeft();
            }
            if (Atype == 5)
            {
                printf("player touched enemy on side");
                if (ECS::GetComponent<BlockEnemy>(entA).GetActive())
                {
                    ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
                }
            }
            else if (Atype == 9)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
        else if ((int)fixtureUserData == 3)
        {
            if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactRight();
            }
            if (Atype == 5)
            {
                printf("player touched enemy on side");
                if (ECS::GetComponent<BlockEnemy>(entA).GetActive())
                {
                    ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
                }
            }
            else if (Atype == 9)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
        else if ((int)fixtureUserData == 4)
        {
            if (Atype == 6)
            {
                printf("player touched spikes on head");
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
    }
   
    if (contact->GetFixtureB()->GetBody()->GetEntityType() == 5)
    {
        //type 5 is block enemy
        ECS::GetComponent<BlockEnemy>(entB).SetIsLeft(!ECS::GetComponent<BlockEnemy>(entB).GetIsLeft());
        if (contact->GetFixtureA()->GetBody()->GetEntityType() == 3)
        {
            //printf("enemy hit by arrow");
            //type 3 is arrow
            if (ECS::GetComponent<BlockEnemy>(entB).GetActive())
            {
                ECS::GetComponent<BlockEnemy>(entB).SetInactive();
                ECS::GetComponent<PhysicsBody>(entB).SetVelocity(vec3(0.f, 0.f, 0.f));
                ECS::GetComponent<Arrow>(entA).SetArrTime(4.9f);
            }

        }
    }
    else if (contact->GetFixtureA()->GetBody()->GetEntityType() == 5)
    {
        //type 5 is block enemy
        ECS::GetComponent<BlockEnemy>(entA).SetIsLeft(!ECS::GetComponent<BlockEnemy>(entA).GetIsLeft());
        if (contact->GetFixtureB()->GetBody()->GetEntityType() == 3)
        {
            //printf("enemy hit by arrow");
            //type 3 is arrow
            if (ECS::GetComponent<BlockEnemy>(entA).GetActive())
            {
                ECS::GetComponent<BlockEnemy>(entA).SetInactive();
                ECS::GetComponent<PhysicsBody>(entA).SetVelocity(vec3(0.f, 0.f, 0.f));
                ECS::GetComponent<Arrow>(entB).SetArrTime(4.9f);
            }
        }
    }

    if (contact->GetFixtureB()->GetBody()->GetEntityType() == 9)
    {
        //type 9 is platform enemy
        ECS::GetComponent<PlatformEnemy>(entB).SetIsLeft(!ECS::GetComponent<PlatformEnemy>(entB).GetIsLeft());
    }
    else if (contact->GetFixtureA()->GetBody()->GetEntityType() == 9)
    {
        //type 9 is platform enemy
        ECS::GetComponent<PlatformEnemy>(entA).SetIsLeft(!ECS::GetComponent<PlatformEnemy>(entA).GetIsLeft());
    }
    if (contact->GetFixtureB()->GetBody()->GetEntityType() == 1)
    {
        //type 1 is sticky wall
        if (contact->GetFixtureA()->GetBody()->GetEntityType() == 3)
        {
            ECS::GetComponent<Arrow>(entA).SetFrozen(true);
        }
    }
    else if (contact->GetFixtureA()->GetBody()->GetEntityType() == 1)
    {
        //type 1 is sticky wall
        if (contact->GetFixtureB()->GetBody()->GetEntityType() == 3)
        {
            ECS::GetComponent<Arrow>(entB).SetFrozen(true);
        }
    }
    if (contact->GetFixtureA()->GetBody()->GetEntityType() == 4)
    {
        //4 is level goal
        if (entB == EntityIdentifier::MainPlayer())
        {
            ECS::GetComponent<Player>(entB).SetContactingGoal(true);
        }
    }
    else if(contact->GetFixtureB()->GetBody()->GetEntityType()==4)
    {
        //4 is level goal
        if (entA == EntityIdentifier::MainPlayer())
        {
            ECS::GetComponent<Player>(entA).SetContactingGoal(true);
        }
    }
    if (contact->GetFixtureA()->GetBody()->GetEntityType() == 3)
    {
        //3 is arrow
        if (entB != EntityIdentifier::MainPlayer())
        {
            ECS::GetComponent<Arrow>(entA).ArrCollide();
        }
    }
    else if (contact->GetFixtureB()->GetBody()->GetEntityType() == 3)
    {
        //3 is arrow
        if (entA != EntityIdentifier::MainPlayer())
        {
            ECS::GetComponent<Arrow>(entB).ArrCollide();
        }
    }
    if (contact->GetFixtureA()->GetBody()->GetEntityType() == 7 && contact->GetFixtureB()->GetBody()->GetEntityType()==3)
    {
        ECS::GetComponent<Target>(entA).SetHit();
        ECS::GetComponent<PhysicsBody>(entA).GetBody()->GetFixtureList()->SetSensor(true);
    }
    else if (contact->GetFixtureB()->GetBody()->GetEntityType() == 7 && contact->GetFixtureA()->GetBody()->GetEntityType() == 3)
    {
        ECS::GetComponent<Target>(entB).SetHit();
        ECS::GetComponent<PhysicsBody>(entB).GetBody()->GetFixtureList()->SetSensor(true);
    }
    if (contact->GetFixtureA()->GetBody()->GetEntityType() == 8 && contact->GetFixtureB()->GetBody()->GetEntityType() != 3)
    {
        ECS::GetComponent<PressurePlate>(entA).PressOn();
    }
    else if (contact->GetFixtureB()->GetBody()->GetEntityType() == 8 && contact->GetFixtureA()->GetBody()->GetEntityType() != 3)
    {
        ECS::GetComponent<PressurePlate>(entB).PressOn();
    }
    
}

void ContactListener::EndContact(b2Contact* contact)
{

    int entA = (contact->GetFixtureA()->GetBody()->GetEntityNumber());
    int entB = (contact->GetFixtureB()->GetBody()->GetEntityNumber());
    if (contact->GetFixtureA()->IsSensor())
    {
        void* fixtureUserData = contact->GetFixtureA()->GetUserData();
        if ((int)fixtureUserData == 1)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndContacted();
        }
        if ((int)fixtureUserData == 2)
        {
            if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndLeft();
            }
        }
        if ((int)fixtureUserData == 3)
        {
            if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndRight();
            }
        }
    }
    if (contact->GetFixtureB()->IsSensor())
    {
        void* fixtureUserData = contact->GetFixtureB()->GetUserData();
        if ((int)fixtureUserData == 1)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndContacted();
        }
        if ((int)fixtureUserData == 2)
        {
            if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndLeft();
            }
        }
        if ((int)fixtureUserData == 3)
        {
            if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndRight();
            }
        }
    }
    if (contact->GetFixtureA()->GetBody()->GetEntityType() == 4)
    {
        if (entB == EntityIdentifier::MainPlayer())
        {
            ECS::GetComponent<Player>(entB).SetContactingGoal(false);
        }
    }
    else if (contact->GetFixtureB()->GetBody()->GetEntityType() == 4)
    {
        if (entA == EntityIdentifier::MainPlayer())
        {
            ECS::GetComponent<Player>(entA).SetContactingGoal(false);
        }
    }
    if (contact->GetFixtureA()->GetBody()->GetEntityType() == 8 && contact->GetFixtureB()->GetBody()->GetEntityType() != 3)
    {
        ECS::GetComponent<PressurePlate>(entA).PressOff();
    }
    else if (contact->GetFixtureB()->GetBody()->GetEntityType() == 8 && contact->GetFixtureA()->GetBody()->GetEntityType() != 3)
    {
        ECS::GetComponent<PressurePlate>(entB).PressOff();
    }
   
}
