#include "animsprite.h"
#include "transform.h"
#include <raylib.h>
#include <stdlib.h>


AnimspriteComponent animspriteComponents = {0};


void AddAnimspriteComponent(Entity entity_id, 
    float w, 
    float h, 
    int cell_w,
    int cell_h,
    int* cell_counts,
    Texture2D* texture){

    animspriteComponents.x_offset[entity_id] = 0;
    animspriteComponents.y_offset[entity_id] = 0;
    animspriteComponents.r_offset[entity_id] = 0;

    animspriteComponents.w[entity_id] = w;
    animspriteComponents.h[entity_id] = h;
    
    animspriteComponents.cell_w[entity_id] = cell_w;
    animspriteComponents.cell_h[entity_id] = cell_h;
    free(animspriteComponents.cell_counts[entity_id]);
    animspriteComponents.cell_counts[entity_id] = cell_counts;

    animspriteComponents.current_row[entity_id] = 0;
    animspriteComponents.current_column[entity_id] = 0;

    animspriteComponents.speed[entity_id] = 1.0f;
    animspriteComponents.lastTime[entity_id] = GetTime();

    animspriteComponents.texture[entity_id] = texture;
    
    animspriteComponents.has[entity_id] = true;
    animspriteComponents.generation[entity_id] = entityGeneration[entity_id];


    }
void RenderAnimspriteComponent(Entity entity_id){
    Rectangle sourceRect = {
        (int)animspriteComponents.current_column[entity_id]*animspriteComponents.cell_w[entity_id],
        (int)animspriteComponents.current_row[entity_id]*animspriteComponents.cell_h[entity_id],
        (int)animspriteComponents.cell_w[entity_id],
        (int)animspriteComponents.cell_h[entity_id]
    };

    Rectangle targetRect = {
        transformComponents.x[entity_id]+animspriteComponents.x_offset[entity_id],
        transformComponents.y[entity_id]+animspriteComponents.y_offset[entity_id],
        animspriteComponents.w[entity_id],
        animspriteComponents.h[entity_id]    
    };

    DrawTexturePro(
        *(animspriteComponents.texture[entity_id]),
        sourceRect,
        targetRect,
        (Vector2){0.0f, 0.0f},
        transformComponents.r[entity_id],
        WHITE
    );

    if(GetTime()-animspriteComponents.lastTime[entity_id] >= (1.0/animspriteComponents.speed[entity_id])/animspriteComponents.cell_counts[entity_id][animspriteComponents.current_row[entity_id]]){
        animspriteComponents.current_column[entity_id]++;
        if (animspriteComponents.current_column[entity_id] > animspriteComponents.cell_counts[entity_id][animspriteComponents.current_row[entity_id]]){
            animspriteComponents.current_column[entity_id]  = 0;
        }
        animspriteComponents.lastTime[entity_id] = GetTime();
    }


}