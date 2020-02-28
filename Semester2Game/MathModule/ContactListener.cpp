#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->IsSensor())
    {
        void* fixtureUserData = contact->GetFixtureA()->GetUserData();
        if ((int)fixtureUserData == 1)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).Contacted();
        }
        if ((int)fixtureUserData == 2)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactLeft();
        }
        if ((int)fixtureUserData == 3)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactRight();
        }
    }
    if (contact->GetFixtureB()->IsSensor())
    {
        void* fixtureUserData = contact->GetFixtureB()->GetUserData();
        if ((int)fixtureUserData == 1)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).Contacted();
        }
        if ((int)fixtureUserData == 2)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactLeft();
        }
        if ((int)fixtureUserData == 3)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).ContactRight();
        }
    }
    int entA = (contact->GetFixtureA()->GetBody()->GetEntityNumber());
    int entB = (contact->GetFixtureB()->GetBody()->GetEntityNumber());
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
            printf("arrow hit sticky wall");
            ECS::GetComponent<Arrow>(entA).SetFrozen(true);
        }
    }
    else if (contact->GetFixtureA()->GetBody()->GetEntityType() == 1)
    {
        //type 1 is sticky wall
        if (contact->GetFixtureB()->GetBody()->GetEntityType() == 3)
        {
            printf("arrow hit sticky wall");
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
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndLeft();
        }
        if ((int)fixtureUserData == 3)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndRight();
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
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndLeft();
        }
        if ((int)fixtureUserData == 3)
        {
            ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndRight();
        }
    }
   
}
