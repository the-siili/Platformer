#include <box2d/types.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <box2d/box2d.h>
#include <stdio.h>
#include "engine.h"
#include "textures.h"

#include "components/transform.h"
#include "components/rigidbody.h"
#include "components/script.h"
#include "components/sprite.h"
#include "components/animsprite.h"
#include "settings.h"

#include "player.h"


Entity nextEntityId = 0;
bool aliveEntities[MAX_ENTITIES] = {false};
Entity availableEntityIds[MAX_ENTITIES] = {0};
int availableEntityIds_size = -1;

int entityGeneration[MAX_ENTITIES] = {0};


Entity NewEntity(){
    Entity newEntityId = 0;
    if (availableEntityIds_size > -1){
        newEntityId = availableEntityIds[availableEntityIds_size];
        availableEntityIds[availableEntityIds_size] = 0;
        availableEntityIds_size--;
    }
    else{
        newEntityId = nextEntityId++;
    }

    entityGeneration[newEntityId]++;
    aliveEntities[newEntityId] = true;
    return newEntityId;
}


void RemoveEntity(Entity entity_id){
    availableEntityIds_size++;
    availableEntityIds[availableEntityIds_size] = entity_id;
    aliveEntities[entity_id] = false;
}




b2WorldDef worldDef;
b2WorldId worldId;

void Start(){

    worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -100.0f};
    worldId = b2CreateWorld(&worldDef);


    LoadTextures();
    Entity player1 = SpawnPlayer(0, 0);

    Entity floor = NewEntity();
    AddTransformComponent(floor, 0, -20, 0);
    AddSpriteComponent(floor, 100, 10, &playerSheetTexture);

    AddRigidbodyComponent(floor, 1000, 10);
    b2Body_SetType(rigidbodyComponents.bodyId[floor], b2_staticBody);
}


void Update(){
    for(Entity entity_id = 0; entity_id < nextEntityId; ++entity_id){
        
        //dont update this object if it is dead
        if (aliveEntities[entity_id] == false){ return; }
        //printf("\n%i", entity_id);
        if(scriptComponents.has[entity_id]){
            UpdateScriptComponent(entity_id);
        }
    }
}


void FixedUpdate(){
     b2World_Step(worldId, PHYSICS_TIME_STEP, 4);

    for(Entity entity_id = 0; entity_id < nextEntityId; ++entity_id){
        
        //dont update this object if it is dead
        if (aliveEntities[entity_id] == false){ return; }
        //printf("\n%i", entity_id);
        if(rigidbodyComponents.has[entity_id]){
            FixedUpdateRigidbodyComponent(entity_id);

        }
    }

}
void Render(){
    for(Entity entity_id = 0; entity_id < nextEntityId; ++entity_id){
        
        //dont update this object if it is dead
        if (aliveEntities[entity_id] == false){ return; }
        //printf("\n%i", entity_id);
        if(spriteComponents.has[entity_id]){
            RenderSpriteComponent(entity_id);
        }
        if(animspriteComponents.has[entity_id]){
            RenderAnimspriteComponent(entity_id);
        }
    }
    
}

void RenderHUD(){
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, BLACK);
}