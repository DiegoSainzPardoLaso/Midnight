#include "RenderableObject.h"

StaticRendereableObjectOpenGL fRenderableObject::Create(StaticMesh &mesh, Material &material)
{
    StaticRendereableObjectOpenGL rendereableObject
    {
        .material = fMaterial_OGL::Create(material.shaderPath)
    };

    int index = 0;
    OGL_Util::Create_VAO_VBO_EBO
    (
        index,
        rendereableObject.VAO,
        rendereableObject.VBO,
        rendereableObject.EBO,
        mesh.vertices,
        mesh.total_vertices_byte_size,
        mesh.indices,
        mesh.index_count,
        OGL_Util::Integrants::POSITION_COLOR_NORMALS_UV,
        GL_DYNAMIC_DRAW
    );

    return rendereableObject;
}


AnimatedRendereableObjectOpenGL fRenderableObject::Create(ENGINE_TYPE type, AnimatedMesh &mesh, Material &material)
{
    AnimatedRendereableObjectOpenGL rendereableObject
    {
        .objectType = type,
        .mesh       = &mesh,
        .material   = fMaterial_OGL::Create(material.shaderPath)
    };

    int index = 0;
    OGL_Util::Create_VAO_VBO_EBO
    (
        index,
        rendereableObject.VAO,
        rendereableObject.VBO,
        rendereableObject.EBO,
        rendereableObject.mesh->vertices,
        rendereableObject.mesh->total_vertices_byte_size,
        rendereableObject.mesh->indices,
        rendereableObject.mesh->index_count,
        OGL_Util::Integrants::POSITION_COLOR_NORMALS_UV,
        GL_DYNAMIC_DRAW
    );

    return rendereableObject;
}
