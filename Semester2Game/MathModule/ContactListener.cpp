#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    int entA = (contact->GetFixtureA()->GetBody()->GetEntityNumber());
    int entB = (contact->GetFixtureB()->GetBody()->GetEntityNumber());
    if (entA == EntityIdentifier::MainPlayer())
    {
        ECS::GetComponent<Player>(EntityIdentifier::MainPlayer()).Contacted();
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
