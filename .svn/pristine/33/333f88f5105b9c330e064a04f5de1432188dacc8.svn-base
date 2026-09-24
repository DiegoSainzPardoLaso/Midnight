#include "Shader.h"

Shader fShader::Create(const char* source)
{
    auto start = std::chrono::high_resolution_clock::now();

    Shader shader{};
    int vertexShader   = Internal::CreateVertexShader  (source, true);
    int fragmentShader = Internal::CreateFragmentShader(source, true);

    
    shader.program     = Internal::CreateShaderProgram(vertexShader, fragmentShader);
    strcpy(shader.filePath, source);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::filesystem::file_time_type newTime = std::filesystem::last_write_time((shader.filePath));
    shader.lastModifiedTime                  = newTime.time_since_epoch().count();

    auto end       = std::chrono::high_resolution_clock::now();    
    float duration = std::chrono::duration<float, std::chrono::milliseconds::period>(end - start).count();

    if (vertexShader > -1 && fragmentShader > -1)  
    {
        std::string mess = "Shader Successfully Compiled [ " + std::to_string(duration) + " ms ]";
        Message::Info(mess.data(), source);
    }

    return shader;
}    

Shader fShader::Create(const char* vSource, const char* fSource)
{
    Shader shader{};
    int vertexShader   = Internal::CreateVertexShader(vSource, false);
    int fragmentShader = Internal::CreateFragmentShader(fSource, false);
    shader.program     = Internal::CreateShaderProgram(vertexShader, fragmentShader);
        
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shader;
}



void fShader::Update(Shader& shader)
{
    /*
#if _WIN32

    std::string oPath = shader.filePath;

    // Convert to wide string
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, oPath.c_str(), -1, NULL, 0);
    std::wstring wtest(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, oPath.c_str(), -1, &wtest[0], size_needed);

    WIN32_FIND_DATA fileData;

    // Use the wide string as LPCWSTR
    LPCWSTR path      = wtest.c_str();
    HANDLE fileHandle = FindFirstFile(path, &fileData);

    if (fileHandle == INVALID_HANDLE_VALUE) 
    {
        Message::Error("Shader not found", shader.filePath);
        return;
    }

    // Compare file times
    if (CompareFileTime(&shader.lastUpdatedTime, &fileData.ftLastWriteTime) == -1) 
    {
        glDeleteProgram(shader.program);

        shader = CreateShader(shader.filePath);
        shader.lastUpdatedTime = fileData.ftLastWriteTime;
    }

    FindClose(fileHandle);

#endif
*/
     
    long long newTime = std::filesystem::last_write_time((shader.filePath)).time_since_epoch().count();
    if (shader.lastModifiedTime != newTime)
    {
        glDeleteProgram(shader.program);

        shader = Create(shader.filePath);
        shader.lastModifiedTime = newTime;
    }
}

int fShader::Internal::CreateVertexShader(const char* path, bool oneSource)
{
    unsigned int vertexShader;
    const char*  vertexSource;
    
    if (!oneSource){ vertexSource = tFile::Load(path);                                       }
    else           { vertexSource = tFile::Load(path, "#Vertex Shader", "#Fragment Shader", '/'); }
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);    

    int exception = CheckVertexExceptions(vertexShader, path) ? -1 : 1;
    
    return vertexShader * exception;
}

int fShader::Internal::CreateFragmentShader(const char* path, bool oneSource)
{
    unsigned int fragmentShader;
    const char*  fragmentSource;

    if (!oneSource) { fragmentSource = tFile::Load(path);                             }
    else            { fragmentSource = tFile::Load(path, "#Fragment Shader", "#END", '/'); }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource (fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    int exception = CheckFragmentExceptions(fragmentShader, path) ? -1 : 1;
    
    return fragmentShader * exception;
}

int fShader::Internal::CreateShaderProgram(int& vertexShader, int& fragmentShader)
{
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram (shaderProgram); 

    int exception = CheckShaderProgramExceptions(shaderProgram) ? -1 : 1;
    
    return shaderProgram * exception;
} 


bool fShader::Internal::CheckVertexExceptions(unsigned int vertexShader, const char* path)
{
    int  success;
    char message[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        
    if (!success)
    {
        std::string fileName = tFile::get_name(path);
        std::string mess = "Vertex shader [ " + fileName + " ]";

        glGetShaderInfoLog(vertexShader, 512, NULL, message);
        Message::Error(mess.data(), message);
        return true;
    }    

    return false;
}    

bool fShader::Internal::CheckFragmentExceptions(unsigned int fragmentShader, const char* path)
{
    int  success;
    char message[512];

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        std::string fileName = tFile::get_name(path);
        std::string mess = "Fragment shader [ " + fileName + " ]";

        glGetShaderInfoLog(fragmentShader, 512, NULL, message);
        Message::Error(mess.data(), message);
        return true;
    }

    return false;
}    

bool fShader::Internal::CheckShaderProgramExceptions(unsigned int shaderProgram)
{
    int  success;
    char message[512];

    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
        
    if (!success)
    {      
        glGetProgramInfoLog(shaderProgram, 512, NULL, message);
        Message::Error("Shader Program --- ", message);
        return true;
    }        

    return false;
}   
