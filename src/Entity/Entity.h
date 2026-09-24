#pragma once

#include <iostream>

#include "../Rendering/Material.h"

#include "../Types/Mesh.h"
#include "../Types/Transform.h"
#include "../Animation/Animator.h"

#include "../Rendering/OpenGL/OGLUtilities.hpp"

#include "../ResourceHandling/MOFLoader.h"

namespace Entity
{
    struct Animated
    {
	    U32          id;

        AnimatedMesh mesh;
        Skeleton     skeleton;
        Transform    transform;
        Material_OGL material;
        Animator     animator;

        // Remove in release
        //
        char       meshFilePath[128];
        long long  lastMeshUpdatedTime;
    };

    Animated* Create(const char* meshPath, const char* shaderPath, std::vector<const char*>& textures, int id);
    void AddAnimation(Animated& entity, Animation& animation);
    void UpdateComponents(Animated*& entity);
    void UpdateMesh(Entity::Animated*& entity);
};


