#include "GeometryFunctions.h"

// @note The VAO VBO and EBO creation has to be done outside this function
//
GUIMesh fGeometry::CreateScreenSpaceQuad(float x, float y, float width, float height, Vec3 color)
{
    GUIMesh quad{};
    quad.total_vertices_byte_size  = sizeof(gVertex) * 4;
    quad.vertex_count = 4;
    quad.index_count = 6;

    quad.vertices  = reinterpret_cast<gVertex*>(malloc(sizeof(gVertex) * 4));
    quad.indices = reinterpret_cast<int*>(malloc(sizeof(int) * 6));

    Vec2 v0 = { x, y };
    Vec2 v1 = { x + width, y + height };

    // Top Left
    //
    quad.vertices[0].position = { v0.x, v0.y };
    quad.vertices[0].color    = color;
    quad.vertices[0].uv       = { 0,    0 };

    // Top Right
    //
    quad.vertices[1].position = { v1.x, v0.y };
    quad.vertices[1].color    = color;
    quad.vertices[1].uv       = { 0,    1 };

    // Bottom Left
    //
    quad.vertices[2].position = { v0.x, v1.y };
    quad.vertices[2].color    = color;
    quad.vertices[2].uv       = { 1,    1 };

    // Bottom Right
    //
    quad.vertices[3].position = { v1.x, v1.y };
    quad.vertices[3].color    = color;
    quad.vertices[3].uv       = { 1,    0 };


    quad.indices[0] = 0;
    quad.indices[1] = 1;
    quad.indices[2] = 2;

    quad.indices[3] = 2;
    quad.indices[4] = 1;
    quad.indices[5] = 3;   

    return quad;
}

GUI_Mesh_Quad fGeometry::CreateScreenSpaceQuadHeapFree(float x, float y, float width, float height, Vec3 color)
{
    GUI_Mesh_Quad quad{};
    quad.total_vertices_byte_size = sizeof(gVertex) * 4;
    quad.vertex_count = 4;
    quad.index_count = 6;
    
    Vec2 v0 = { x, y };
    Vec2 v1 = { x + width, y + height };

    // Top Left
    //
    quad.vertices[0].position = { v0.x, v0.y };
    quad.vertices[0].color = color;
    quad.vertices[0].uv = { 0,    0 };

    // Top Right
    //
    quad.vertices[1].position = { v1.x, v0.y };
    quad.vertices[1].color = color;
    quad.vertices[1].uv = { 0,    1 };

    // Bottom Left
    //
    quad.vertices[2].position = { v0.x, v1.y };
    quad.vertices[2].color = color;
    quad.vertices[2].uv = { 1,    1 };

    // Bottom Right
    //
    quad.vertices[3].position = { v1.x, v1.y };
    quad.vertices[3].color = color;
    quad.vertices[3].uv = { 1,    0 };


    quad.indices[0] = 0;
    quad.indices[1] = 1;
    quad.indices[2] = 2;

    quad.indices[3] = 2;
    quad.indices[4] = 1;
    quad.indices[5] = 3;

    return quad;
}



// @note The VAO VBO and EBO creation has to be done outside this function
//
GUIMesh fGeometry::CreateScreenSpaceQuad(float x, float y, float width, float height, float U0, float V0, float U1, float V1)
{
    GUIMesh quad{};
    quad.total_vertices_byte_size  = sizeof(gVertex) * 4;
    quad.vertex_count  = 4;
    quad.index_count   = 6;
    quad.vertices  = reinterpret_cast<gVertex*>(malloc(sizeof(gVertex) * 4));
    quad.indices = reinterpret_cast<int*>(malloc(sizeof(int) * 6));

    Vec2 v0 = { x, y };
    Vec2 v1 = { x + width, y + height };

    // Top Left
    //
    quad.vertices[0].position = { v0.x, v0.y };
    quad.vertices[0].color    = { 1,  1,  1  };
    quad.vertices[0].uv       = { U0,     V0 };

    // Top Right
    //
    quad.vertices[1].position = { v1.x, v0.y };
    quad.vertices[1].color    = { 1,  1,  1  };
    quad.vertices[1].uv       = { U1,     V0 };

    // Bottom Left
    //
    quad.vertices[3].position = { v0.x, v1.y };
    quad.vertices[3].color    = { 1,  1,   1 };
    quad.vertices[3].uv       = { U0,     V1 };

    // Bottom Right
    //
    quad.vertices[2].position = { v1.x, v1.y };
    quad.vertices[2].color    = { 1,  1,  1  };
    quad.vertices[2].uv       = { U1,     V1 };


    unsigned int indices[6] =
    {
        0, 1, 2,
        2, 1, 3,
    };

    for (size_t i = 0; i < 6; i++) { quad.indices[i] = indices[i]; }


    return quad;
}