#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

typedef struct {
    Rectangle srcRect;
    Rectangle targetRect;
    int id;

} TileBtn;

bool IsTileBtnPressed(TileBtn* tilebtn){
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), tilebtn->targetRect);
}

//Layer must be 0-9
typedef  struct {
    Rectangle srcRect;
    Vector2 position;
    unsigned int layer;
}Tile;


TileBtn* CreateTileButtons(Texture2D tileset, int tilesize, float tileBtnSize){

    TileBtn* tileBtns;
    int tileBtnsLen = 0;

    for(int x = 0; x < tileset.width/tilesize; x++){

        for(int y = 0; y < tileset.height/tilesize; y++){
            tileBtnsLen++;
            if(tileBtnsLen == 1){
                tileBtns = malloc(sizeof(TileBtn));
            }
            else{
                tileBtns = realloc(tileBtns, tileBtnsLen*sizeof(TileBtn));
            }

            tileBtns[tileBtnsLen-1] = (TileBtn){(Rectangle){x*tilesize, y*tilesize, tilesize, tilesize}, 
            (Rectangle){x*tileBtnSize, 64+y*tileBtnSize, tileBtnSize, tileBtnSize},
            tileBtnsLen};

        }

    }
    tileBtns = realloc(tileBtns, (tileBtnsLen+1)*sizeof(TileBtn));
    tileBtns[tileBtnsLen] = (TileBtn){(Rectangle){0, 0, 0, 0}, 
                                    (Rectangle){0, 0, 0, 0},
                                    -1};

    return tileBtns;
}

int round_to_nearest_tile(int n, int ts) {
    if (n >= 0)
        return ((n + ts/2) / ts) * ts;
    else
        return ((n - ts/2) / ts) * ts;
}
Vector2 GetMouseWorldPos(Camera2D* camera, int tilesize){
    Vector2 mp = GetMousePosition();

    mp.x = (mp.x-camera->offset.x)/camera->zoom-tilesize/2.0;
    mp.y = (mp.y-camera->offset.y)/camera->zoom-tilesize/2.0;
    

    mp.x = round_to_nearest_tile(mp.x, tilesize);
    mp.y = round_to_nearest_tile(mp.y, tilesize);

    return mp;
}




int main(){
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "TileMaker");


    //SetTargetFPS(244);


    Texture2D tileset = LoadTexture("res/tileset.png");
    int tilesize = 16;
    int mapSizeX = 64;
    int mapSizeY = 64;

    float tileBtnSize = 32.0f;
    TileBtn* tileBtns = CreateTileButtons(tileset, tilesize, tileBtnSize);

    RenderTexture2D screen = LoadRenderTexture(mapSizeX*tilesize, mapSizeY*tilesize);

    Camera2D camera = {0};
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){0, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    Vector2 lastMousePos = GetMousePosition();


    Rectangle currentTileSrcRect = {0, 0, tilesize, tilesize};

    Tile* tiles;
    int tilesSize = 0;

    bool showOnlyCurrentLayer = false;
    unsigned int currentLayer = 0;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   
        
        Vector2 mp = GetMouseWorldPos(&camera, tilesize);

        if(IsKeyPressed(KEY_L)){
            showOnlyCurrentLayer = !showOnlyCurrentLayer;
        }
        

        int pressedNum = GetKeyPressed()-48;
        if(pressedNum >= 0 && pressedNum <= 9){
            currentLayer = pressedNum;
        }


        if (GetMouseWheelMove() < 0){
            camera.zoom = camera.zoom/1.1;
        }
        else if(GetMouseWheelMove() > 0){
            camera.zoom = camera.zoom*1.1;
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
            camera.offset.x -= Normalize(lastMousePos.x-GetMousePosition().x, 0, 1);
            camera.offset.y -= Normalize(lastMousePos.y-GetMousePosition().y, 0, 1);
        }

        bool onTileBtn = false;
        for(int i = 0; tileBtns[i].id != -1; i++){
            if(IsTileBtnPressed(&tileBtns[i])){
                currentTileSrcRect = tileBtns[i].srcRect;
                
            }
            if(CheckCollisionPointRec(GetMousePosition(), tileBtns[i].targetRect)){
                onTileBtn = true;
            }
            
        }

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && onTileBtn == false){

            int removeIndex = -1;

            for(int i = 0; i < tilesSize; i++){
                if(mp.x == tiles[i].position.x && mp.y == tiles[i].position.y && tiles[i].layer == currentLayer){
                    removeIndex = i;
                }
            }
            if(removeIndex != -1){
                Tile* newTiles = malloc(sizeof(Tile)*tilesSize-1);
                for(int i = 0; i < removeIndex; i++){
                    newTiles[i] = tiles[i];
                }
                for(int i = removeIndex+1; i < tilesSize; i++){
                    newTiles[i-1] = tiles[i];
                }
                tilesSize--;
                free(tiles);
                tiles = newTiles;
            }
            
            if(tilesSize == 0){tiles = malloc(sizeof(Tile));}
            else{tiles = realloc(tiles, (tilesSize+1)*sizeof(Tile));}
            tilesSize++;
            tiles[tilesSize-1] = (Tile){currentTileSrcRect, mp, currentLayer};
        }

        if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && onTileBtn == false){
            int removeIndex = -1;

            for(int i = 0; i < tilesSize; i++){
                if(mp.x == tiles[i].position.x && mp.y == tiles[i].position.y && tiles[i].layer == currentLayer){
                    removeIndex = i;
                }
            }
            if(removeIndex != -1){
                Tile* newTiles = malloc(sizeof(Tile)*tilesSize-1);
                for(int i = 0; i < removeIndex; i++){
                    newTiles[i] = tiles[i];
                }
                for(int i = removeIndex+1; i < tilesSize; i++){
                    newTiles[i-1] = tiles[i];
                }
                tilesSize--;
                free(tiles);
                tiles = newTiles;
            }
        }


        lastMousePos = GetMousePosition();
        
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            BeginMode2D(camera);
                for(int x = -mapSizeX/2; x <= mapSizeX/2; x++){
                    DrawLine(x*tilesize, -(mapSizeY/2)*tilesize, x*tilesize, (mapSizeY/2)*tilesize, GRAY);
                }
                for(int y = -mapSizeY/2; y <= mapSizeY/2; y++){
                    DrawLine(-(mapSizeX/2)*tilesize, y*tilesize, (mapSizeX/2)*tilesize, y*tilesize, GRAY);
                }

                int indexLayers[10][1000] = {{-1}};
                int indexLayerSizes[10] = {0};
                
                for(int i = 0; i < tilesSize; i++){

                    indexLayers[tiles[i].layer][indexLayerSizes[tiles[i].layer]] = i;
                    indexLayerSizes[tiles[i].layer]++;

                }
                if(!showOnlyCurrentLayer){
                    for(int i = 0; i <= 9; i++){
                        for(int j = 0; j < indexLayerSizes[i]; j++){
                            DrawTexturePro(tileset, 
                                tiles[indexLayers[i][j]].srcRect, 
                                (Rectangle){tiles[indexLayers[i][j]].position.x, tiles[indexLayers[i][j]].position.y, tilesize, tilesize}, 
                                (Vector2){0, 0}, 
                                0, 
                                WHITE);
                        }
                    }
                }
                else{
                    for(int i = 0; i < indexLayerSizes[currentLayer]; i++){
                        DrawTexturePro(tileset, 
                            tiles[indexLayers[currentLayer][i]].srcRect, 
                            (Rectangle){tiles[indexLayers[currentLayer][i]].position.x, tiles[indexLayers[currentLayer][i]].position.y, tilesize, tilesize}, 
                            (Vector2){0, 0}, 
                            0, 
                            WHITE);
                    }
                }


            EndMode2D();

            DrawText(TextFormat("Zoom: %4.2f", camera.zoom), 0, 0, 20, WHITE);
            DrawText(TextFormat("FPS: %i", GetFPS()), 120, 0, 20, WHITE);
            DrawText(TextFormat("Layer: %i", currentLayer), 240, 0, 20, WHITE);
            
            for(int i = 0; tileBtns[i].id != -1; i++ ){
                DrawTexturePro(tileset, tileBtns[i].srcRect, tileBtns[i].targetRect, (Vector2){0, 0},0,  WHITE);
            }
            


        EndDrawing();
    }

    CloseWindow();

    return 0;
}







