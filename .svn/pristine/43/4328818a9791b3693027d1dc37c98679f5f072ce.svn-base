#include "OGLUtilities.hpp"


void OGL_Util::Create_Line_VAO_VBO(int& index, unsigned int& VAO, unsigned int& VBO, dVertex*& data, int total_vertices_byte_size, GLenum usage)
{
    int strideLength = 6;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, total_vertices_byte_size * sizeof(float), data, usage);
    
    // Position
    //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideLength * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    // Color
    //        
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, strideLength * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, index);
    glBindVertexArray(index);
}

void OGL_Util::CreateDebugObject_VAO_VBO_EBO(int& index, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, dVertex*& data, int total_vertices_byte_size, int*& indices, int iSize, GLenum usage)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, total_vertices_byte_size * sizeof(float), data, usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(int), indices, usage);

    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));

    glBindBuffer(GL_ARRAY_BUFFER, index);
    glBindVertexArray(index);
}

