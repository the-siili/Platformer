#include "script.h"
#include "../engine.h"



//The script should always take in the entity id and nothing else

ScriptComponent scriptComponents = {0};

void AddScriptComponent(Entity entity_id, ScriptFunction function){
    scriptComponents.function[entity_id] = function;
    scriptComponents.has[entity_id] = true;
    scriptComponents.generation[entity_id] = entityGeneration[entity_id];
}

void UpdateScriptComponent(Entity entity_id){
    if (entityGeneration[entity_id] != scriptComponents.generation[entity_id]) { return; }

    scriptComponents.function[entity_id](entity_id);
}