#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include "settings.h"
#include <box2d/box2d.h>


typedef unsigned int Entity;
extern Entity nextEntityId;

extern bool aliveEntities[MAX_ENTITIES];
extern Entity availableEntityIds[MAX_ENTITIES];
extern int availableEntityIds_size;

extern int entityGeneration[MAX_ENTITIES];


Entity NewEntity();
void RemoveEntity(Entity entity_id);

extern b2WorldDef worldDef;
extern b2WorldId worldId;


void Start();
void Update();
void FixedUpdate();
void Render();
void RenderHUD();


#endif