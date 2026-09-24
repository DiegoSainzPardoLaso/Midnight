#pragma once

#include "../Rendering/Renderer.h"
#include "../Rendering/OpenGL/RenderableObjectsManager.h"    // @note Change this one to be like the include above

#include "../Time/Time.h"
#include "../Inputs/Inputs.h"
#include "../Platform/Platform.h"

#include "../Grid/Grid.h"
#include "../Scene/Scene.h"
#include "../Console/Console.h"
#include "../Camera/CameraSystem.h"
#include "../Entity/EntityManager.h"

#include "../EngineTools/Gizmos.h"
#include "../Viewport/Viewport.h"

#include "../Engine/Core.h"
#include "../Engine/EngineConfig.h"


namespace Midnight { namespace Engine 
{
    inline Midnight_Engine_Core *core;
    
    void Run();
        
    void Initialize();
    void Update();
    void Terminate();
    
}}

