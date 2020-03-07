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
        }
        if ((int)fixtureUserData == 2)
        {
            if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactLeft();
            }
            if (Btype == 5)
            {
                printf("player touched enemy on side");
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
        if ((int)fixtureUserData == 3)
        {   
            if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactRight();
            }
            if (Btype==5)
            {
                printf("player touched enemy on side");
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
        }
        if ((int)fixtureUserData == 2)
        {
            if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactLeft();
            }
            if (Atype == 5)
            {
                printf("player touched enemy on side");
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
        if ((int)fixtureUserData == 3)
        {
            if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody)
            {
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactRight();
            }
            if (Atype == 5)
            {
                printf("player touched enemy on side");
                ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).SetKill();
            }
        }
    }
   
    if (contact->GetFixtureB()->GetBody()->GetEntityType() == 5)
    {
        //type 5 is block enemy
        ECS::GetComponent<BlockEnemy>(entB).SetIsLeft(!ECS::GetComponent<BlockEnemy>(entB).GetIsLeft());
    }
    else if (contact->GetFixtureA()->GetBody()->GetEntityType() == 5)
    {
        //type 5 is block enemy
        ECS::GetComponent<BlockEnemy>(entA).SetIsLeft(!ECS::GetComponent<BlockEnemy>(entA).GetIsLeft());
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
   
}
