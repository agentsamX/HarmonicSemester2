#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    int entA = (contact->GetFixtureA()->GetBody()->GetEntityNumber());
    int entB = (contact->GetFixtureB()->GetBody()->GetEntityNumber());
    if (entA == EntityIdentifier::MainPlayer())
    {
        printf("contactoccurred");
        ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).Contacted();
    }
    if (contact->GetFixtureB()->GetBody()->GetEntityType() == 5)
    {
        //type 5 is block enemy
        ECS::GetComponent<BlockEnemy>(entB).SetIsLeft(!ECS::GetComponent<BlockEnemy>(entB).GetIsLeft());
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
}
