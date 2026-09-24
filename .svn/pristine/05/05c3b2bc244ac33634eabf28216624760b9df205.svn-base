#pragma once

#include <iostream>
#include <vector>

#include "Entity.h"


namespace EntityManager
{
    // @note Inside a gloabal state?
    //
    inline std::vector<Entity::Animated*> entities;

    Entity::Animated* CreateEntity(const char* meshPath, const char* shaderPath, std::vector<const char*>& textures);
    void              Update();


    // void               GiveID(Entity::Container*& entity);

};
