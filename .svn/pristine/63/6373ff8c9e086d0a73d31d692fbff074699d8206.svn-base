#pragma once

#include "Vertex.h"

template <typename Vertex_Type>
struct Mesh
{
    Vertex_Type *vertices;
    int         *indices;

    uint32_t     vertex_count;
    uint32_t     index_count;
    uint32_t     total_vertices_byte_size;
  
    Mesh()
    {
        vertices                 = nullptr;
        indices                  = nullptr;
        total_vertices_byte_size = 0;
        vertex_count             = 0;
        index_count              = 0;
    }

    Mesh(const Vertex_Type *vertices, const int *indices, uint32_t vertex_count, uint32_t index_count)
    {                
        this->vertex_count             = vertex_count;
        this->index_count              = index_count;
        this->total_vertices_byte_size = sizeof(Vertex_Type) * vertex_count;

        this->vertices = (Vertex_Type *)malloc(sizeof(Vertex_Type) * vertex_count);
        this->indices  = (int         *)malloc(sizeof(int        ) * index_count );


        for (size_t i = 0; i < this->index_count; i++)
        {
            if (i < this->vertex_count) { this->vertices[i] = vertices[i]; }
            this->indices[i] = indices[i];
        }
    }
};







struct DebugMesh
{
    dVertex *vertices;
    int     *indices;

    uint32_t total_vertices_byte_size;
    uint32_t vertex_count;
    uint32_t index_count;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    /*
    DebugMesh(const dVertex *vertices, const int *indices, uint32_t vertexCount, uint32_t indexCount)
    {
        //================
        // OPEN_GL Crap //
        //================
        //
        this->VAO = 0;
        this->VBO = 0;
        this->EBO = 0;
        //
        //================

        this->vCount   = vertexCount;
        this->iCount   = indexCount;
        this->dSize    = sizeof(dVertex) * vertexCount;

        this->vertices = (dVertex *)malloc(sizeof(dVertex) * vertexCount);
        this->indices  = (int     *)malloc(sizeof(int    ) * indexCount );


        for (size_t i = 0; i < this->iCount; i++)
        {
            if (i < this->vCount) { this->vertices[i] = vertices[i]; }
            this->indices[i] = indices[i];
        }
    }
    */
};

struct StaticMesh
{
    sVertex *vertices;
    int     *indices;

    uint32_t total_vertices_byte_size;
    uint32_t vertex_count;
    uint32_t index_count;

    unsigned int VAO;   // @note The cameras actually work without this. The gizmos doesn't, so I have to port the gizmos to use the new system.
    unsigned int VBO;   // @note The cameras actually work without this. The gizmos doesn't, so I have to port the gizmos to use the new system.
    unsigned int EBO;   // @note The cameras actually work without this. The gizmos doesn't, so I have to port the gizmos to use the new system.
};

struct AnimatedMesh
{
    aVertex *vertices;
    int     *indices;

    uint32_t total_vertices_byte_size;   
    uint32_t vertex_count;   
    uint32_t index_count;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

struct GUIMesh
{
    gVertex *vertices;
    int     *indices;

    uint32_t total_vertices_byte_size;
    uint32_t vertex_count;
    uint32_t index_count;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

struct GUI_Mesh_Quad
{
    gVertex vertices[4];
    int     indices[6];

    uint32_t total_vertices_byte_size;
    uint32_t vertex_count;
    uint32_t index_count;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};



namespace fMesh
{
    template<typename M, typename V>
    M Create(int vertex_count, int index_count, V *meshVertices, int *indices)
    {
        M mesh{};
        mesh.vertex_count  = vertex_count;
        mesh.index_count  = index_count;
        mesh.total_vertices_byte_size   = sizeof(V) * vertex_count;

        mesh.vertices  = reinterpret_cast<V*>  (malloc(sizeof(V)   * vertex_count));
        mesh.indices = reinterpret_cast<int*>(malloc(sizeof(int) * index_count));

        for (int v = 0; v < vertex_count; v++) { mesh.vertices[v]  = meshVertices[v]; }
        for (int i = 0; i < index_count; i++) { mesh.indices[i] = indices[i];      }

        return mesh;
    }    
}