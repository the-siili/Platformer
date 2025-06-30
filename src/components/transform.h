
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../settings.h"
#include "../engine.h"


typedef struct {
    float x[MAX_ENTITIES];
    float y[MAX_ENTITIES];
    float r[MAX_ENTITIES];

    bool has[MAX_ENTITIES];
    int generation[MAX_ENTITIES];
} TransformComponent;


extern TransformComponent transformComponents;


void AddTransformComponent(Entity entity_id, float x, float y, float r);
void MoveTransform(Entity entity_id, float x, float y);
#endif