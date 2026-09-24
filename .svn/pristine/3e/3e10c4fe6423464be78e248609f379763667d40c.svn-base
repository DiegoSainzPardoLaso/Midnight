#include "File.h"

const char *tFile::Load(const char* path)
{    
    std::ifstream fileStream(path);

    std::string line   = "";
    std::string source = "";
    
    while(std::getline(fileStream, line))
    {
        source += line + "\n";
    }
    
    fileStream.close();    
    source += "\0";   

    char* fSource = static_cast<char*>(malloc(source.size()));
    strcpy(fSource, source.data());

    return fSource;
}


std::vector<char> bFile::load_spirv_shader(const char *path)
{    
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    std::vector<char> buffer(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));

    file.close();
    
    return buffer;
}




uint32_t bFile::get_buffer_size(const char *path)
{
    uint32_t size = 0;
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    
    std::vector<char> buffer(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    file.close();
    return buffer.size();

}


const char *tFile::Load(const char* path, std::string regex)
{
    std::ifstream file(path);

    std::string line           = "";
    std::string source         = "";
    
    while(std::getline(file, line) && line.compare(regex))
    {
	    source += line + "\n";
    }
    
    file.close();
    source += "\0";

    char* fSource = static_cast<char*>(malloc(source.size()));
    strcpy(fSource, source.data());

    return fSource;
}   


const char *tFile::Load(const char* path, std::string regexToStartWriting, std::string regexToStopWriting, char skipLineRegex)
{
    std::ifstream file(path);

    std::string line           = "";
    std::string source         = "";

    bool startWriting = false;
    
    while(std::getline(file, line))
    {
	    if (!line.compare(regexToStopWriting))  { break;               }
	    if (!line.compare(regexToStartWriting)) { startWriting = true; }
        
	    if (startWriting && line.compare(regexToStartWriting) && line.compare(regexToStopWriting) && line[0] != skipLineRegex)
        {
	        source += line + "\n ";   
	    }	
    }
        
    file.close();
    source += "\0";
    
    // @note Don't need the + 1, 'cause i manually add \0 to the source string
    char* fSource = static_cast<char *>(malloc(source.size()));
    strcpy(fSource, source.data());

    // @note When returning .data() I was really returning a dangling pointer 'cause it was a stack variable and 
    // the .data() is removed at the end of the scope
    // So what i was really reading is just stack memory until I hit a \0
    return fSource;
}

const char *tFile::get_extension(const char* path)
{
    std::filesystem::path file(path);
    char* ext = static_cast<char*>(malloc(file.extension().string().size()));
    strcpy(ext, file.extension().string().data());

    return ext;
}

bool tFile::compare_extension(const char* path, std::string ext)
{
    std::filesystem::path file(path);
    return !file.extension().string().compare(ext);
}

bool tFile::Exists(const char *path)
{
    std::ifstream file(path);   
    bool good = file.good();
    file.close();

    return good;
}

const char *tFile::get_name(const char* path)
{
    std::filesystem::path file(path);
    char* ext = static_cast<char*>(malloc(file.filename().string().size()));
    strcpy(ext, file.filename().string().data());

    return ext;
}

const char *tFile::get_name_without_extension(const char *path)
{
    std::filesystem::path file(path);
    std::string nameWitheExtension = file.filename().string();
    char *c                        = &nameWitheExtension[nameWitheExtension.size()];
    uint32_t nameWitheExtensionLength = nameWitheExtension.size();

    while (*c-- != '.') { nameWitheExtensionLength--; }    

    char *ext = static_cast<char *>(malloc(sizeof(char) * nameWitheExtensionLength));
    std::string name = nameWitheExtension.substr(0, nameWitheExtensionLength);
    strcpy(ext, name.data());

    return ext;
}

void tFile::Check(const char* data)
{
    std::cout << "--- FILE DATA RETRIEVE CHECK START ---" << '\n' << '\n';       

    while (*data != '\0')
    {
        std::cout << *data;
        data++;
    }
    
    std::cout << "--- FILE DATA RETRIEVE END ---" << '\n' << '\n';;       
}

long long tFile::get_last_write_time(const char *path)
{
    std::filesystem::file_time_type writeTime = std::filesystem::last_write_time(path);
    return (long long)(writeTime.time_since_epoch().count());
}

 

int bFile::read_int(std::ifstream& file)
{
    int value;
    file.read(reinterpret_cast<char*>(&value), sizeof(int));
    return value;
}

float bFile::ReadFloat(std::ifstream& file)
{
    float value;
    file.read(reinterpret_cast<char*>(&value), sizeof(float));
    return value;
}

// It reads the length of the string, and then the string
//
char *bFile::ReadString(std::ifstream& file)
{
    int length = 0;
    file.read(reinterpret_cast<char*>(&length), sizeof(int));
    char* str = reinterpret_cast<char*>(malloc(sizeof(char) * length));
    file.read(str, length);

    return str;
}

char *bFile::ReadString(std::ifstream& file, int length)
{    
    char* string = nullptr;
    file.read(string, length);

    return string;
}
