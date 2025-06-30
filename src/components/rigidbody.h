#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "../settings.h"
#include "../engine.h"
#include <box2d/box2d.h>

typedef struct {
    b2BodyDef bodyDef[MAX_ENTITIES];
    b2BodyId bodyId[MAX_ENTITIES];
    b2Polygon dynamicBox[MAX_ENTITIES];
    b2ShapeDef shapeDef[MAX_ENTITIES];

    bool has[MAX_ENTITIES];
    int generation[MAX_ENTITIES];
} RigidbodyComponent;


extern RigidbodyComponent rigidbodyComponents;


void AddRigidbodyComponent(Entity entity_id, float w, float h);
void FixedUpdateRigidbodyComponent(Entity entity_id);
#endif