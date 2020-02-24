#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    int entA = (contact->GetFixtureA()->GetBody()->GetEntityNumber());
    int entB = (contact->GetFixtureB()->GetBody()->GetEntityNumber());
    if (entA == EntityIdentifier::MainPlayer())
    {
        ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).Contacted();
    }
    else if (entB == EntityIdentifier::MainPlayer())
    {
        ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).Contacted();
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
            printf("arrow hit sticky wall");
            
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
    if (entA == EntityIdentifier::MainPlayer())
    {
        ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndContacted();
    }
    else if (entB == EntityIdentifier::MainPlayer())
    {
        ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).EndContacted();
    }
}
