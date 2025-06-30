#include "rigidbody.h"
#include "transform.h"
#include "../engine.h"
#include <box2d/box2d.h>
#include <stdio.h>

//The script should always take in the entity id and nothing else

RigidbodyComponent rigidbodyComponents = {0};

void AddRigidbodyComponent(Entity entity_id, float w, float h){
    rigidbodyComponents.bodyDef[entity_id] = b2DefaultBodyDef();
    rigidbodyComponents.bodyDef[entity_id].type = b2_dynamicBody;
    rigidbodyComponents.bodyDef[entity_id].position = (b2Vec2){transformComponents.x[entity_id], transformComponents.y[entity_id]};

    rigidbodyComponents.bodyId[entity_id] = b2CreateBody(worldId, &(rigidbodyComponents.bodyDef[entity_id]));

    rigidbodyComponents.dynamicBox[entity_id] = b2MakeBox(w/2, h/2);

    rigidbodyComponents.shapeDef[entity_id] = b2DefaultShapeDef();
    rigidbodyComponents.shapeDef[entity_id].density = 1.0f;
    rigidbodyComponents.shapeDef[entity_id].material.friction = 0.3f;

    b2CreatePolygonShape(rigidbodyComponents.bodyId[entity_id], 
        &rigidbodyComponents.shapeDef[entity_id], 
        &rigidbodyComponents.dynamicBox[entity_id]);

    rigidbodyComponents.has[entity_id] = true;
    rigidbodyComponents.generation[entity_id] = entityGeneration[entity_id];
}


void FixedUpdateRigidbodyComponent(Entity entity_id){
    transformComponents.x[entity_id] = b2Body_GetPosition(rigidbodyComponents.bodyId[entity_id]).x*10;
    transformComponents.y[entity_id] = -b2Body_GetPosition(rigidbodyComponents.bodyId[entity_id]).y*10;
    printf("\n%f", transformComponents.y[entity_id]);
    printf("%4.2f", b2Body_GetPosition(rigidbodyComponents.bodyId[entity_id]).y);
}