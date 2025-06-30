#include <raylib.h>

#include "textures.h"


Texture2D playerTexture;
Texture2D playerSheetTexture;

void LoadTextures(){
    playerTexture = LoadTexture("res/player.png");
    playerSheetTexture = LoadTexture("res/playersheet.png");
}




