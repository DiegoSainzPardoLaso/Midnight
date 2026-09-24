#include "DebugShapes.h"

DebugShape fDebugShape::Create(DEBUG_SHAPE_TYPE kind)
{
	DebugShape shape;
	switch (kind)
	{
		case DEBUG_LINE:
		{
			shape.id		  = 0;
			shape.kind	      = kind;
			shape.mesh.vertices = reinterpret_cast<dVertex*>(malloc(sizeof(dVertex) * 2));
			shape.mesh.vertex_count = 2;
			shape.mesh.total_vertices_byte_size  = 2 * 6;
			shape.shader	  = fShader::Create("C:/Midnight/shaders/glsl/Debug/debug.shader");

			fUtil::CopyArray<dVertex>(shape.mesh.vertices, &Internal::debugLine[0], 2);

			OGL_Util::Create_Line_VAO_VBO(shape.id, shape.mesh.VAO, shape.mesh.VBO, shape.mesh.vertices, shape.mesh.total_vertices_byte_size, GL_DYNAMIC_DRAW);

		}break;

		case DEBUG_PLANE:
		{
			shape.id	    = 0;
			shape.kind	    = kind;
			shape.mesh      = fMesh::Create<DebugMesh, dVertex>(4, 6, Internal::debugPlaneMesh, Internal::debugPlaneIndices);
			shape.shader    = fShader::Create("C:/Midnight/shaders/glsl/Debug/debug.shader");
			shape.transform = fTransform::Initialize();
			OGL_Util::CreateDebugObject_VAO_VBO_EBO(shape.id, shape.mesh.VAO, shape.mesh.VBO, shape.mesh.EBO, shape.mesh.vertices, shape.mesh.total_vertices_byte_size, shape.mesh.indices, shape.mesh.index_count, GL_DYNAMIC_DRAW);
		} break;

		case DEBUG_CUBE:
		{
			shape.id	 = 0;
			shape.kind	 = kind;
			shape.mesh   = fMesh::Create<DebugMesh, dVertex>(24, 36, Internal::debugCubeMesh, Internal::debugCubeIndices);
			shape.shader = fShader::Create("C:/Midnight/shaders/glsl/Debug/debug.shader");
			OGL_Util::CreateDebugObject_VAO_VBO_EBO(shape.id, shape.mesh.VAO, shape.mesh.VBO, shape.mesh.EBO, shape.mesh.vertices, shape.mesh.total_vertices_byte_size, shape.mesh.indices, shape.mesh.index_count, GL_DYNAMIC_DRAW);
		}break;

		case DEBUG_SPHERE:
		{

		}break;
		
		case DEBUG_GIZMOS:
		{
			shape.id	  = 0;
			shape.kind   = kind;
			shape.mesh   = fMesh::Create<DebugMesh, dVertex>(432, 432, Internal::debugGizmosMesh, Internal::debugGizmosIndices);
			shape.shader = fShader::Create("C:/Midnight/shaders/glsl/Debug/debug.shader");
			OGL_Util::CreateDebugObject_VAO_VBO_EBO(shape.id, shape.mesh.VAO, shape.mesh.VBO, shape.mesh.EBO, shape.mesh.vertices, shape.mesh.total_vertices_byte_size, shape.mesh.indices, shape.mesh.index_count, GL_DYNAMIC_DRAW);
		}break;
	}
	
	return shape;
}

DebugShape fDebugShape::CreateLine(Vec3 &v0, Vec3 &v1, Vec3 &color)
{
	DebugShape shape;
	shape.id		  = 0;
	shape.kind		  = DEBUG_SHAPE_TYPE::DEBUG_LINE;
	shape.mesh.vertices = reinterpret_cast<dVertex *>(malloc(sizeof(dVertex) * 2));
	shape.mesh.vertex_count = 2;
	shape.mesh.total_vertices_byte_size  = 2 * 6;
	shape.shader	  = fShader::Create("C:/Midnight/shaders/Debug/debug.shader");
	
	shape.mesh.vertices[0].position = v0;
	shape.mesh.vertices[1].position = v1;
	shape.mesh.vertices[0].color    = color;
	shape.mesh.vertices[1].color	  = color;

	OGL_Util::Create_Line_VAO_VBO(shape.id, shape.mesh.VAO, shape.mesh.VBO, shape.mesh.vertices, shape.mesh.total_vertices_byte_size, GL_DYNAMIC_DRAW);
	return shape;
}

DebugShape fDebugShape::CreateLine(Vec3 &v0, Vec3 &v1, Vec3 color)
{
	DebugShape shape;
	shape.id					   = 0;
	shape.kind					   = DEBUG_SHAPE_TYPE::DEBUG_LINE;
	shape.mesh.vertices			   = reinterpret_cast<dVertex*>(malloc(sizeof(dVertex) * 2));
	shape.mesh.vertex_count			   = 2;
	shape.mesh.total_vertices_byte_size			   = 2 * 6;
	shape.shader				   = fShader::Create("C:/Midnight/shaders/Debug/debug.shader");
	
	shape.mesh.vertices[0].position = v0;
	shape.mesh.vertices[1].position = v1;
	shape.mesh.vertices[0].color    = color;
	shape.mesh.vertices[1].color	  = color;

	OGL_Util::Create_Line_VAO_VBO(shape.id, shape.mesh.VAO, shape.mesh.VBO, shape.mesh.vertices, shape.mesh.total_vertices_byte_size, GL_DYNAMIC_DRAW);
	
	return shape;
}

DebugShape fDebugShape::CreateLine(Vec3 v0, Vec3 v1, Vec3 color)
{
	DebugShape shape;
	shape.id = 0;
	shape.kind = DEBUG_SHAPE_TYPE::DEBUG_LINE;
	shape.mesh.vertices = reinterpret_cast<dVertex *>(malloc(sizeof(dVertex) * 2));
	shape.mesh.vertex_count = 2;
	shape.mesh.total_vertices_byte_size = 2 * 6;
	shape.shader = fShader::Create("C:/Midnight/shaders/glsl/Debug/debug.shader");

	shape.mesh.vertices[0].position = v0;
	shape.mesh.vertices[1].position = v1;
	shape.mesh.vertices[0].color = color;
	shape.mesh.vertices[1].color = color;

	OGL_Util::Create_Line_VAO_VBO(shape.id, shape.mesh.VAO, shape.mesh.VBO, shape.mesh.vertices, shape.mesh.total_vertices_byte_size, GL_DYNAMIC_DRAW);

	return shape;
}

DebugShape fDebugShape::CreatePlane(float size)
{
	DebugShape shape;
	shape.id         = 0;
	shape.kind       = DEBUG_PLANE;
	shape.mesh       = fMesh::Create<DebugMesh, dVertex>(4, 6, Internal::debugPlaneMesh, Internal::debugPlaneIndices);
	shape.shader     = fShader::Create("C:/Midnight/shaders/glsl/Debug/debug.shader");
	shape.transform  = fTransform::Initialize({0,0,0}, { 0,0,0 }, {size, size, size});
	OGL_Util::CreateDebugObject_VAO_VBO_EBO(shape.id, shape.mesh.VAO, shape.mesh.VBO, shape.mesh.EBO, shape.mesh.vertices, shape.mesh.total_vertices_byte_size, shape.mesh.indices, shape.mesh.index_count, GL_DYNAMIC_DRAW);
	return shape;
}

