#include "engine.h"
#include "components/transform.h"
#include "components/animsprite.h"
#include "components/script.h"
#include "components/rigidbody.h"
#include "player.h"
#include "textures.h"
#include "camera.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>
#include <box2d/box2d.h>

void UpdatePlayer(Entity e){

    bool moved = false;
    
    if(IsKeyDown(KEY_A)){
        b2Body_SetLinearVelocity(rigidbodyComponents.bodyId[e], (b2Vec2){-20, b2Body_GetLinearVelocity(rigidbodyComponents.bodyId[e]).y});
        moved = true;
    }
    if(IsKeyDown(KEY_D)){
        
        b2Body_SetLinearVelocity(rigidbodyComponents.bodyId[e], (b2Vec2){20, b2Body_GetLinearVelocity(rigidbodyComponents.bodyId[e]).y});
        moved = true;
    }
    if(IsKeyPressed(KEY_W)){
        b2Body_ApplyLinearImpulseToCenter(rigidbodyComponents.bodyId[e], (b2Vec2){ 0, 4000}, true);
        moved = true;
    }
    if (!moved){
        b2Body_SetLinearVelocity(rigidbodyComponents.bodyId[e], (b2Vec2){b2Body_GetLinearVelocity(rigidbodyComponents.bodyId[e]).x/(1+GetFrameTime()*5), b2Body_GetLinearVelocity(rigidbodyComponents.bodyId[e]).y});
        animspriteComponents.current_row[e] = 3;
        animspriteComponents.current_column[e] = 0;
    }
    else{
        animspriteComponents.current_row[e] = 0;
    }

    float mouse_movement = GetMouseWheelMove();
    if(mouse_movement > 0){
        camera.zoom = camera.zoom/2;
    }
    else if(mouse_movement < 0){
        camera.zoom = camera.zoom*2;
    }

}

Entity player;
Entity SpawnPlayer(float x, float y){
    player = NewEntity();

    AddTransformComponent(player, x, y, 0);
    int* cell_counts = malloc(sizeof(int)*4);
    cell_counts[0] = 3;
    cell_counts[1] = 4;
    cell_counts[2] = 4;
    cell_counts[3] = 1;

    AddRigidbodyComponent(player, 10, 10);

    AddAnimspriteComponent(player, 
        32, 
        32, 
        8, 8,
        cell_counts,
        &playerSheetTexture);
    animspriteComponents.speed[player] = 3;
    AddScriptComponent(player, &UpdatePlayer);

    return player;
}