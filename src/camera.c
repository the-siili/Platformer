#include "settings.h"
#include <raylib.h>


Camera2D camera = {0};
void InitializeCamera(){
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

}