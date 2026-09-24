#pragma once

#include <iostream>
#include <vector>

#include <glad/gl.h>

#include "RenderableObject.h"
#include "RenderableObjectsManager.h"

#include "../shared/enums.h"

#include "../../Grid/Grid.h"
#include "../../Geometry/DebugShapes.h"

#include "../../GUI/MGUI.h"
#include "../../Time/Time.h"

#include "../../EngineTools/Gizmos.h"

#include "../../Entity/EntityManager.h"

#include "../../Camera/CameraSystem.h"
#include "../../Camera/Camera.h"

#include "../../Console/Console.h"

#include "../../Animation/Animation.h"
#include "../../ResourceHandling/MAFLoader.h"

#include "../../Physics/Types/Ray.h"



namespace fRenderer
{
    inline Vec4 backgroundColor             = { 0.2f, 0.2f, 0.4f, 1.0f };
    inline Vec4 selectionObjectOutlineColor = { 0.9f, 0.4f, 1.0f, 1 };
    inline bool toggleDebugShapes;

    


    namespace Internal
    {
        inline Shader         OUTLINE_SHADER;
        inline RENDERING_MODE CURRENT_RENDER_MODE;        
    }

    // ====================================
    // TEST 
    // ====================================
    inline Entity::Animated *tstEntity;        
    // ====================================
  
    void Initialize();
    
    void Draw
    (
        Vec2                       &windowDimensions, 
        CameraSystem              *&camera_system, 
        Console                   *&console, 
        Grid                      *&grid, 
        Gizmos                    *&gizmos,
        RenderNodeSystem_OGL *&renderableManger
    );
    
    void UpdateDrawMode();

    void RestoreDrawMode(RENDERING_MODE mode);

    void DrawEntities(std::vector<Entity::Animated*> &entities, Camera &activeCamera);
    
    void DrawCameras(CameraSystem *&camera_system, std::vector<StaticRendereableObjectOpenGL> &RO_cameras);

    void DrawGizmos(Gizmos *&gizmos, Camera *&camera);

    void DrawScreenSpaceGUIText(Text *&text, Vec2 windowDimensions);

    void DrawGrid(Grid *&grid, Camera *&activeCamera);

    void DrawDebugShapes(DebugShape &shape, Camera *&activeCamera);

    void DrawCommandConsole(Console *&console, Vec2 windowDimensions);


    void DrawSelectedObjectsOutline(Gizmos *&gizmos, CameraSystem *&camera_system, RenderNodeSystem_OGL *&renderableManager);


    void DrawGUIData(GUIData &guiData, Vec2 windowDimensions);

    void RenderGenericGUI(unsigned int& shaderProgram, unsigned int& VAO, float x, float y, float width, float height, int index_count, Vec2 &windowDimensions);
}
