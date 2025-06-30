#include <raylib.h>
#include <raymath.h>

#include "settings.h"
#include "engine.h"
#include "camera.h"
int main(){

    SetConfigFlags(WINDOW_FLAGS);
    InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "raylib [core] example - basic window");

    //if target fps == 0 we use unlimited fps
    if (TARGET_FPS != 0){
        SetTargetFPS(TARGET_FPS);
    }
    float updateFixer = 0.0;
    

    //calculate screen texture size and position for the display
    float aspect_ratio = (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT;
    RenderTexture2D screen = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    float h = GetMonitorHeight(GetCurrentMonitor());
    Rectangle screenTextureDestRect = (Rectangle){(GetMonitorWidth(GetCurrentMonitor())-(h*aspect_ratio))/2, 
                                            0.0f, 
                                            h*aspect_ratio,  
                                            h};


    
    InitializeCamera();
    Start();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   

        Update();

        //Calculate fixed update time and update accordingly
        updateFixer += GetFrameTime();
        if (updateFixer >= PHYSICS_TIME_STEP){
            FixedUpdate();
            updateFixer = 0.0f;
        }
        
        
            //Render the game on to the screen texture
            BeginTextureMode(screen);
                BeginMode2D(camera);
                    ClearBackground(WHITE);
                    Render();
                EndMode2D();
                RenderHUD();
            EndTextureMode();
        

        //Render the screen texture on to the window
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(screen.texture, 
                (Rectangle){0.0f, 0.0f, (float)screen.texture.width, -(float)screen.texture.height}, 
                screenTextureDestRect, 
                (Vector2){0.0f, 0.0f} , 
                0.0f, 
                WHITE);

        EndDrawing();
        
    }

    CloseWindow();

    return 0;
}