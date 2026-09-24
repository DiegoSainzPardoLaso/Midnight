#pragma once

#include <glad/gl.h>

#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>

#include "../../File/File.h"
#include "../../Utilities/Message/MessageUtils.h"

#include "../../Engine/EngineConfig.h"
    
struct Shader
{
    unsigned int program;                   
    char         filePath[128];

    long long    lastModifiedTime;
};

namespace fShader
{
    
    Shader Create(const char* source);                    // Used by the shader.shader structure
    Shader Create(const char* vpath, const char* fpath);  // Used by the shader.ver, shader.fra structure
    void   Update(Shader& shader);
            
    namespace Internal
    {
        int  CreateVertexShader(const char* path, bool oneSource);
        bool CheckVertexExceptions(unsigned int vertexShader, const char* path);

        int  CreateFragmentShader(const char* path, bool oneSource);
        bool CheckFragmentExceptions(unsigned int fragmentShader, const char* path);

        int  CreateShaderProgram(int& vertexShader, int& fragmentShader);
        bool CheckShaderProgramExceptions(unsigned int shaderProgram);

        // @note Give this idea some more thought
        // 
        // inline std::map<std::string, Shader> compiledShaders;

    }

}
   

  
