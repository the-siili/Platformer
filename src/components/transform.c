#include "transform.h"
#include "rigidbody.h"
#include "../engine.h"
#include <box2d/box2d.h>


//The script should always take in the entity id and nothing else

TransformComponent transformComponents = {0};

void AddTransformComponent(Entity entity_id, float x, float y, float r){
    transformComponents.x[entity_id] = x;
    transformComponents.y[entity_id] = y;
    transformComponents.r[entity_id] = r;

    transformComponents.has[entity_id] = true;
    transformComponents.generation[entity_id] = entityGeneration[entity_id];
}


void MoveTransform(Entity entity_id, float x, float y){
    transformComponents.x[entity_id] = x;
    transformComponents.y[entity_id] = y;
    rigidbodyComponents.bodyDef[entity_id].position = (b2Vec2){x, y};

}
