
#ifndef SPRITE_H
#define SPRITE_H
#include "../settings.h"
#include "../engine.h"
#include <raylib.h>

typedef struct {
    float x_offset[MAX_ENTITIES];
    float y_offset[MAX_ENTITIES];
    float r_offset[MAX_ENTITIES];

    float w[MAX_ENTITIES];
    float h[MAX_ENTITIES];

    Texture2D* texture[MAX_ENTITIES];

    bool has[MAX_ENTITIES];
    int generation[MAX_ENTITIES];
} SpriteComponent;


extern SpriteComponent spriteComponents;


void AddSpriteComponent(Entity entity_id, float w, float h, Texture2D* texture);
void RenderSpriteComponent(Entity entity_id);

#endif