#include "sprite.h"
#include "transform.h"
#include "../engine.h"
#include <raylib.h>


//The script should always take in the entity id and nothing else

SpriteComponent spriteComponents = {0};

void AddSpriteComponent(Entity entity_id, float w, float h, Texture2D* texture){
    spriteComponents.x_offset[entity_id] = 0;
    spriteComponents.y_offset[entity_id] = 0;
    spriteComponents.r_offset[entity_id] = 0;

    spriteComponents.w[entity_id] = w;
    spriteComponents.h[entity_id] = h;
    spriteComponents.texture[entity_id] = texture;

    spriteComponents.has[entity_id] = true;
    spriteComponents.generation[entity_id] = entityGeneration[entity_id];
}


void RenderSpriteComponent(Entity entity_id){
    DrawTexturePro(*(spriteComponents.texture[entity_id]),
        (Rectangle){0, 0, spriteComponents.texture[entity_id]->width, spriteComponents.texture[entity_id]->height},
        (Rectangle){
            transformComponents.x[entity_id]+spriteComponents.x_offset[entity_id], 
            transformComponents.y[entity_id]+spriteComponents.y_offset[entity_id],
            spriteComponents.w[entity_id],
            spriteComponents.h[entity_id]
        },
        (Vector2){0, 0},
        transformComponents.r[entity_id],
        WHITE
    );
}
