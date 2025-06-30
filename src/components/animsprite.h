
#ifndef ANIMSPRITE_H
#define ANIMSPRITE_H
#include "../settings.h"
#include "../engine.h"
#include <raylib.h>


//CELL_COUNTS IS A DYNAMIC ARRAY AND MUST BE SET LIKE SO
// int* cell_counts = malloc(sizeof(int)*AMOUNT OF ROWS);
// THEN SET THE CORRECT AMOUNT OF ROWS FOR EACH ONE
// cell_counts[0] = 3;
// cell_counts[1] = 4;
// cell_counts[2] = 4;
// cell_counts[3] = 1;

typedef struct {
    float x_offset[MAX_ENTITIES];
    float y_offset[MAX_ENTITIES];
    float r_offset[MAX_ENTITIES];

    float w[MAX_ENTITIES];
    float h[MAX_ENTITIES];

    int cell_w[MAX_ENTITIES];
    int cell_h[MAX_ENTITIES];

    int* cell_counts[MAX_ENTITIES];
    
    int current_row[MAX_ENTITIES];
    int current_column[MAX_ENTITIES];

    float speed[MAX_ENTITIES];
    float lastTime[MAX_ENTITIES];

    Texture2D* texture[MAX_ENTITIES];

    bool has[MAX_ENTITIES];
    int generation[MAX_ENTITIES];
} AnimspriteComponent;


extern AnimspriteComponent animspriteComponents;


void AddAnimspriteComponent(Entity entity_id, 
    float w, 
    float h, 
    int cell_w,
    int cell_h,
    int *cell_counts,
    Texture2D* texture);
void RenderAnimspriteComponent(Entity entity_id);

#endif