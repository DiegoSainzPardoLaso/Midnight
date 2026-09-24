#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


struct File
{
    char     *buffer;
    uint32_t  bufferSize;
};


namespace tFile
{
    const char *Load(const char *path);    
    const char *Load(const char *path, std::string regex);  // Same method, but it stops reading and returns the gathered file information when it hits said regex
    const char *Load(const char *path, std::string regexToStartWriting, std::string regexToStopWriting, char skipLineRegex);
    const char *get_name(const char *path);
    const char *get_name_without_extension(const char *path);
    const char *get_extension(const char *path);
    bool        compare_extension(const char *path, std::string extext);
    bool        Exists(const char *path);
    void        Check(const char *data);
    long long   get_last_write_time(const char *path);
}

namespace bFile
{
    std::vector<char> load_spirv_shader(const char *path);    
    uint32_t          get_buffer_size(const char *path);


    int    read_int   (std::ifstream &file);             
    float  ReadFloat (std::ifstream &file);             
    char  *ReadString(std::ifstream &file);              
    char  *ReadString(std::ifstream &file, int length); 

    template<typename T>
    T read_size_of(std::ifstream &file)
    {
        T data;
        file.read(reinterpret_cast<char *>(&data), sizeof(T));

        return data;
    }

    template <typename T>
    T *read_array(std::ifstream &file, uint32_t array_size)
    {
        T *array = (T *)malloc(sizeof(T) * array_size);

        for (size_t a_idx = 0; a_idx < array_size; a_idx++)
        {
            array[a_idx] = read_size_of<T>(file);
        }

        return array;
    }

    template<typename T>
    void write_array(std::ofstream &file, T *array, uint32_t elements_count)
    {
        for (uint32_t idx = 0; idx < elements_count; idx++)
        {
            file.write(reinterpret_cast<char *>(&array[idx]), sizeof(T));
        }
    }
}