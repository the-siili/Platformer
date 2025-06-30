
#ifndef SCRIPT_H
#define SCRIPT_H
#include "../settings.h"
#include "../engine.h"


typedef void (*ScriptFunction)(Entity);

typedef struct {
    ScriptFunction function[MAX_ENTITIES];
    bool has[MAX_ENTITIES];
    int generation[MAX_ENTITIES];
} ScriptComponent;


extern ScriptComponent scriptComponents;


void AddScriptComponent(Entity entity_id, ScriptFunction function);
void UpdateScriptComponent(Entity entity_id);


#endif