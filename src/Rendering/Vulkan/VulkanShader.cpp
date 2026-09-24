#include "VulkanShader.h"

Slang::ComPtr<slang::IGlobalSession> SLANG_GLOBAL_SESSION = nullptr;


//===================================//
//              SLANG                //
//===================================//
//
//
//
void fSlang::initialize()
{
    createGlobalSession(SLANG_GLOBAL_SESSION.writeRef());
}
//
//
//
bool fSlang::compile_and_write_shader_to_file(const vk::raii::Device &logicalDevice, const char *slangPath, const char *spirvPath, Shader_Metadata &out_metadata)
{
    //===================================//
    // COMPILATION                       //
    //===================================//
    //
    std::vector<SlangStage> uniformsShaderStages{};
    std::string buffer = Internal::get_slang_buffer(slangPath, uniformsShaderStages);

    // Create Session
    //
    slang::TargetDesc targetDesc =
    {
        .format = SLANG_SPIRV,
        .profile = SLANG_GLOBAL_SESSION->findProfile("spirv_1_4")
    };

    slang::SessionDesc sessionDesc =
    {
        .targets = &targetDesc,
        .targetCount = 1,
        .defaultMatrixLayoutMode = SlangMatrixLayoutMode::SLANG_MATRIX_LAYOUT_COLUMN_MAJOR
    };


    std::array<slang::CompilerOptionEntry, 2> options =
    {
        slang::CompilerOptionEntry
        {
            slang::CompilerOptionName::EmitSpirvDirectly,
            { slang::CompilerOptionValueKind::String, 1, 0, nullptr, nullptr },
        },
        slang::CompilerOptionEntry
        {
            slang::CompilerOptionName::VulkanUseEntryPointName,
            { slang::CompilerOptionValueKind::String, 1, 0, nullptr, nullptr },
        },
    };

    sessionDesc.compilerOptionEntries    = options.data();
    sessionDesc.compilerOptionEntryCount = (uint32_t)options.size();

    Slang::ComPtr<slang::ISession> session;
    SLANG_GLOBAL_SESSION->createSession(sessionDesc, session.writeRef());


    // Load module
    //
    const char *moduleName = tFile::get_name_without_extension(slangPath);
    std::string modulePath = tFile::get_name(slangPath);

    Slang::ComPtr<slang::IModule> slangModule;
    {
        Slang::ComPtr<slang::IBlob> diagnosticsBlob;
        slangModule = session->loadModuleFromSourceString
        (
            moduleName,
            modulePath.data(),
            buffer.data(),             // Shader source code
            diagnosticsBlob.writeRef() // Optional diagnostic container
        );

        if (!slangModule)
        {
            printf("[ERROR] - Compilation Failed - [ %s ] - \n", slangPath);
            Internal::diagnose(diagnosticsBlob);
            return false;
        }
    }


    // Query Entry Points
    //
    std::vector<const char *> entryPointsNames;
    std::vector<Slang::ComPtr<slang::IEntryPoint>> entry_points;
    for (size_t poStageIdx = 0; poStageIdx < POSSIBLE_SHADER_STAGES_COUNT; poStageIdx++)
    {
        Slang::ComPtr<slang::IEntryPoint> entryPoint;
        Slang::ComPtr<slang::IBlob> diagnosticsBlob;
        slangModule->findEntryPointByName(POSSIBLE_SHADER_STAGES[poStageIdx], entryPoint.writeRef());

        if (entryPoint)
        {
            entryPointsNames.emplace_back(POSSIBLE_SHADER_STAGES[poStageIdx]);
            entry_points.emplace_back(entryPoint);
        }
    }

    // 5. Compose Modules + Entry Points
    //     
    // @note I reserve 8 even though there may be just 2
    //
    std::array<slang::IComponentType *, 8> components;
    components[0] = slangModule;
    for (size_t i = 0; i < entry_points.size(); i++) { components[i + 1] = entry_points[i]; }


    Slang::ComPtr<slang::IComponentType> composedProgram;
    {
        Slang::ComPtr<slang::IBlob> diagnosticsBlob;
        SlangResult result = session->createCompositeComponentType
        (
            components.data(),
            entry_points.size() + 1,
            composedProgram.writeRef(),
            diagnosticsBlob.writeRef()
        );


        if (SLANG_FAILED(result))
        {
            Internal::diagnose(diagnosticsBlob);
            return false;
        }
    }


    // 6. Link
    //
    Slang::ComPtr<slang::IComponentType> linkedProgram;
    {
        Slang::ComPtr<slang::IBlob> diagnosticsBlob;
        SlangResult result = composedProgram->link(linkedProgram.writeRef(), diagnosticsBlob.writeRef());

        if (SLANG_FAILED(result))
        {
            Internal::diagnose(diagnosticsBlob);
            return false;
        }
    }

    // 7. Get Target Kernel Code    
    //
    Slang::ComPtr<slang::IBlob> spirvCode;
    {
        Slang::ComPtr<slang::IBlob> diagnosticsBlob;
        SlangResult result = linkedProgram->getTargetCode(0, spirvCode.writeRef(), diagnosticsBlob.writeRef());
        if (SLANG_FAILED(result))
        {
            Internal::diagnose(diagnosticsBlob);
            return false;
        }
    }


    //========================//
    // Write .spv             //
    //========================//
    //
    Internal::write_compiled_spirV_to_file(spirvPath, (char *)spirvCode->getBufferPointer(), (uint32_t)spirvCode->getBufferSize());

    //========================//
    // Create Shader Metadata //
    //========================//
    //
    out_metadata = Internal::create_shader_meta_data(logicalDevice, slangPath, spirvPath, linkedProgram->getLayout(), entryPointsNames, uniformsShaderStages);


    return true;
}
//
// @note The out slang stages get every variable present on the shader. Uniforms, push constants etc...
//
std::string fSlang::Internal::get_slang_buffer(const char *path, std::vector<SlangStage> &out_slang_stages)
{
    std::ifstream file(path);
    std::string line   = "";
    std::string buffer = "";

    uint32_t leftOpaqueIdx  = 0;
    uint32_t rightOpaqueIdx = 0;

    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = fUtil::TokenizeLine(line, ' ', '<', '(');

        if (tokens.size() > 0)
        {
            if (!tokens[0].compare("ConstantBuffer"))
            {
                out_slang_stages.emplace_back(SLANG_STAGE_NONE);
                rightOpaqueIdx++;
            }
        }

        // This assigns all the stages to their parameter and you can't shuffle parameters around. They are all read in sequence
        // so ALL the vertex parameters are done in one go, all the fragment parameters are done in one go etc...
        //
        if (tokens.size() > 1)
        {
            if (!tokens[1].compare(VERTEX_SHADER_ENTRY_POINT_NAME))
            {
                for (size_t i = leftOpaqueIdx; i < rightOpaqueIdx; i++) { out_slang_stages[i] = SlangStage::SLANG_STAGE_VERTEX; }
                leftOpaqueIdx = rightOpaqueIdx;
            }

            if (!tokens[1].compare(COMPUTE_SHADER_ENTRY_POINT_NAME))
            {
                for (size_t i = leftOpaqueIdx; i < rightOpaqueIdx; i++) { out_slang_stages[i] = SlangStage::SLANG_STAGE_COMPUTE; }
                leftOpaqueIdx = rightOpaqueIdx;
            }

            if (!tokens[1].compare(FRAGMENT_SHADER_ENTRY_POINT_NAME))
            {
                for (size_t i = leftOpaqueIdx; i < rightOpaqueIdx; i++) { out_slang_stages[i] = SlangStage::SLANG_STAGE_FRAGMENT; }
                leftOpaqueIdx = rightOpaqueIdx;
            }
        }

        buffer += line + "\n";
    }

    file.close();

    return buffer;
}


Shader_Metadata fSlang::Internal::create_shader_meta_data(const vk::raii::Device &logical_device, const char *slang_path, const char *spirv_path, slang::ProgramLayout *program_layout, std::vector<const char *> &entry_points, std::vector<SlangStage> &parameter_stages)
{
    // All the uniforms used in the shader
    //
    uint32_t parameterCount = program_layout->getParameterCount();
    uint32_t uniforms_count = 0;

    // Segragate all the regular uniforms from the push constants, and check how many unique entry points there are
    //
    for (uint32_t i = 0; i < parameterCount; i++)
    {
        slang::VariableLayoutReflection *parameter = program_layout->getParameterByIndex(i);
        SlangParameterCategory           category = SlangParameterCategory(parameter->getCategory());


        if (category != SlangParameterCategory::SLANG_PARAMETER_CATEGORY_PUSH_CONSTANT_BUFFER)
        {
            uniforms_count++;
        }
    }

    Shader_Metadata metadata              = {};
    metadata.shader_buffer                = bFile::load_spirv_shader(spirv_path);
    metadata.entry_points                 = (vk::ShaderStageFlagBits *)malloc(sizeof(vk::ShaderStageFlagBits) * entry_points.size());
    metadata.entry_points_count           = (uint32_t)entry_points.size();

    metadata.uniforms                     = (Uniform *)malloc(sizeof(Uniform) * uniforms_count);
    metadata.uniforms_count               = uniforms_count;
    metadata.uniform_required_buffer_size = 0;

    for (size_t entry_point_idx = 0; entry_point_idx < entry_points.size(); entry_point_idx++) { metadata.entry_points[entry_point_idx] = get_vulkan_shader_stage_equivalent(entry_points[entry_point_idx]); }

    uint32_t uniform_idx = 0;

    for (uint32_t i = 0; i < parameterCount; i++)
    {
        uint32_t                         uniform_type_size  = 0;
        slang::VariableLayoutReflection *parameter          = program_layout->getParameterByIndex(i);
        slang::TypeReflection           *type               = program_layout->findTypeByName(parameter->getType()->getElementType()->getName()); // Ex. model_view_projection_ubo        
        SlangParameterCategory           parameter_category = SlangParameterCategory(parameter->getCategory());

        // Regular descriptor slots
        //
        if (type != nullptr && parameter_category != SlangParameterCategory::SLANG_PARAMETER_CATEGORY_PUSH_CONSTANT_BUFFER)
        {
            uniform_type_size += analyze_type_and_get_size(type);

            // The first one is always 0 that's why I do this
            //
            if (uniform_idx + 1 < metadata.uniforms_count) { metadata.uniforms[uniform_idx + 1].offset = uniform_type_size; }

            metadata.uniforms[uniform_idx].shader_stage = Internal::get_vulkan_shader_stage_equivalent(parameter_stages[i]);
            metadata.uniforms[uniform_idx].type         = vk::DescriptorType::eUniformBuffer;
            metadata.uniform_required_buffer_size      += uniform_type_size;

            uniform_idx++;
        }
    }


    // @important I need to store all the parameteres not just the uniform buffers.
    // So the texture slots and all of that
    //
    for (size_t i = 0; i < metadata.uniforms_count; i++)
    {
        vk::DescriptorSetLayoutBinding binding =
        {
            .binding = (uint32_t)i,
            .descriptorType = metadata.uniforms[i].type,
            .descriptorCount = 1,
            .stageFlags = metadata.uniforms[i].shader_stage,
        };

        metadata.bindings.emplace_back(binding);
    }



    return metadata;
}

void fSlang::Internal::write_compiled_spirV_to_file(const char *spirvPath, char *spirvCodeBufferPointer, uint32_t spirvBufferSize)
{
    std::ofstream outFile(spirvPath, std::ios::binary);
    for (size_t i = 0; i < spirvBufferSize; i++)
    {
        outFile << *spirvCodeBufferPointer++;
    }
}
//
//
//
uint32_t fSlang::Internal::size_of(std::string &type)
{
    if (!type.compare("int"))     { return sizeof(int);        }
    if (!type.compare("float"))   { return sizeof(float);      }

    if (!type.compare("vector2")) { return sizeof(float) * 2;  }
    if (!type.compare("vector3")) { return sizeof(float) * 3;  }
    if (!type.compare("vector4")) { return sizeof(float) * 4;  }

    if (!type.compare("matrix3")) { return sizeof(float) * 9;  }
    if (!type.compare("matrix4")) { return sizeof(float) * 16; }

    return 0;
}

uint32_t fSlang::Internal::analyze_type_and_get_size(slang::TypeReflection *type)
{
    const char *name = type->getName();
    slang::TypeReflection::Kind kind = type->getKind();
    uint32_t offsetSize = 0;

    switch (kind)
    {
    case slang::TypeReflection::Kind::Struct:
    {
        for (uint32_t i = 0; i < type->getFieldCount(); i++)
        {
            slang::VariableReflection *member = type->getFieldByIndex(i);
            slang::TypeReflection::Kind kind  = type->getFieldByIndex(i)->getType()->getKind();
            std::string parameter             = "";

            if      (kind == slang::TypeReflection::Kind::Scalar) { parameter = member->getType()->getName(); }
            else if (kind == slang::TypeReflection::Kind::Vector) { parameter = "vector" + std::to_string(member->getType()->getElementCount()); }
            else if (kind == slang::TypeReflection::Kind::Matrix) { parameter = "matrix" + std::to_string(member->getType()->getColumnCount()); }

            offsetSize += size_of(parameter);
        }

    }break;

    case slang::TypeReflection::Kind::Scalar:
    {
        if (strcmp(name, "int"))        { offsetSize += sizeof(int); }
        else if (strcmp(name, "float")) { offsetSize += sizeof(float); };
    }
    }

    return offsetSize;
}

vk::ShaderStageFlagBits fSlang::Internal::get_vulkan_shader_stage_equivalent(SlangStage slangStage)
{
    switch (slangStage)
    {
        case SLANG_STAGE_VERTEX:   { return vk::ShaderStageFlagBits::eVertex;   }break;
        case SLANG_STAGE_FRAGMENT: { return vk::ShaderStageFlagBits::eFragment; }break;
        case SLANG_STAGE_COMPUTE:  { return vk::ShaderStageFlagBits::eCompute;  }break;
    }

    std::cout << "[ERROR] - Function Name - GetVulkanShaderStageEquivalent - Couldn't find a vulkan shader stage equivalent\n";
    return (vk::ShaderStageFlagBits)(-1);
}

vk::ShaderStageFlagBits fSlang::Internal::get_vulkan_shader_stage_equivalent(const char *shaderStageName)
{
    if      (!strcmp(shaderStageName, VERTEX_SHADER_ENTRY_POINT_NAME))   { return vk::ShaderStageFlagBits::eVertex;   }
    else if (!strcmp(shaderStageName, FRAGMENT_SHADER_ENTRY_POINT_NAME)) { return vk::ShaderStageFlagBits::eFragment; }


    return (vk::ShaderStageFlagBits)(-1);
}

void fSlang::Internal::diagnose(slang::IBlob *diagnosticsBlob)
{
    std::cout << (const char *)diagnosticsBlob->getBufferPointer() << std::endl;
    printf("==================================================================================\n");
}
//
//============//
// New Shader //      
//============//
//
Shader_VK::Shader_VK(const vk::raii::Device &logical_device, const char *slang_path, Shader_Metadata &out_metadata)
{
    std::string file_name  = tFile::get_name_without_extension(slang_path);
    std::string spirv_path = SHADER_COMPILED_SPIRV_DEFAULT_PATH + file_name + ".spv";    
    
    if (tFile::Exists(spirv_path.data()))
    {
        if (!load_already_compiled_shader_and_get_metadata_from_its_PSMB(logical_device, spirv_path.data(), out_metadata))
        {
            printf("[INFO] - Failed to load already compiled [%s] shader. Loading BAD_COMPILATION_SHADER\n", file_name.data()); 
            if (!load_already_compiled_shader_and_get_metadata_from_its_PSMB(logical_device, BAD_COMPILATION_SPIRV_PATH, out_metadata))
            {
                printf("[FATAL] - Failed to load 'BAD_COMPILATION_SHADER'\n");
            }
        }
    }
    else
    {                        
        if (!fSlang::compile_and_write_shader_to_file(logical_device, slang_path, spirv_path.data(), out_metadata))
        {        
            printf("[INFO] - Failed to compile [%s] shader, loading 'BAD_COMPILATION_SHADER'\n", file_name.data());            
            if (!load_already_compiled_shader_and_get_metadata_from_its_PSMB(logical_device, BAD_COMPILATION_SPIRV_PATH, out_metadata))
            {
                printf("[FATAL] - Failed to load 'BAD_COMPILATION_SHADER'\n");
            }
        }        
    }  

    strcpy(this->path, slang_path);
    this->module          = create_shader_module(logical_device, out_metadata.shader_buffer);
    this->last_write_time = tFile::get_last_write_time(slang_path);
    write_shader_PSMB_to_file(file_name.data(), out_metadata);
}
 
Shader_Metadata Shader_VK::load_shader_metadata_from_PSMB_file()
{
    Shader_Metadata out_metadata;

    std::string name       = tFile::get_name_without_extension(this->path);
    std::string spirv_path = SHADER_COMPILED_SPIRV_DEFAULT_PATH + name + ".spv";
    std::string slang_path = SHADER_SLANG_DEFAULT_PATH + name + ".slang";
    std::string spmb_path  = SHADER_COMPILED_PSMB_DEFAULT_PATH + name + ".psmb";
    std::ifstream file(spmb_path, std::ios::binary);
   
    if (!tFile::Exists(spmb_path.data())) 
    {
        printf("[INFO] - PSMB file doesn't exist. Returning empty metadata\n");
        return out_metadata;
    }

    // Load PSMB and Create shader metadata
    //
    std::vector<char> shader_byte_code_buffer = bFile::load_spirv_shader(spirv_path.data());    
    char *date                                = bFile::ReadString(file);
    long long lmt                             = bFile::read_size_of<long long>(file);    
    uint32_t entry_point_count                = bFile::read_size_of<uint32_t>(file);
    vk::ShaderStageFlagBits *entry_points     = bFile::read_array<vk::ShaderStageFlagBits>(file, entry_point_count);           
    uint32_t uniforms_count                   = bFile::read_size_of<uint32_t>(file);
    Uniform *uniforms                         = bFile::read_array<Uniform>(file, uniforms_count);    
    uint32_t uniform_required_buffer_size     = bFile::read_int(file);

       
    out_metadata.shader_buffer                = shader_byte_code_buffer;
    out_metadata.entry_points                 = (vk::ShaderStageFlagBits *)malloc(sizeof(vk::ShaderStageFlagBits) * entry_point_count);
    out_metadata.entry_points_count           = entry_point_count;
    out_metadata.uniforms                     = (Uniform *)malloc(sizeof(Uniform) * uniforms_count);
    out_metadata.uniforms_count               = uniforms_count;
    out_metadata.uniform_required_buffer_size = uniform_required_buffer_size;


    for (size_t entry_point_idx = 0; entry_point_idx < entry_point_count; entry_point_idx++) { out_metadata.entry_points[entry_point_idx] = entry_points[entry_point_idx]; }
    for (size_t uniforms_idx    = 0; uniforms_idx    < uniforms_count;     uniforms_idx++)    { out_metadata.uniforms[uniforms_idx]        = uniforms[uniforms_idx];        }


    free(entry_points);
    free(uniforms);    
    free(date);

    file.close();    

    return out_metadata;
}

void Shader_VK::update()
{
    long long new_time = std::filesystem::last_write_time((this->path)).time_since_epoch().count();
    if (this->last_write_time != new_time)
    {                
        this->forced_recompilation();
        this->last_write_time = new_time;
    }
}

void Shader_VK::set_associated_pipeline(Pipeline_VK &pipeline) { this->associated_pipeline = &pipeline; }
//
//==============================//
// Private Methods              //
//==============================//
//
void Shader_VK::forced_recompilation(){}

bool Shader_VK::load_already_compiled_shader_and_get_metadata_from_its_PSMB(const vk::raii::Device &logical_device, const char *spirv_path, Shader_Metadata &out_metadata)
{
    std::string name       = tFile::get_name_without_extension(spirv_path);
    std::string slang_path = SHADER_SLANG_DEFAULT_PATH + name + ".slang";
    std::string spmb_path  = SHADER_COMPILED_PSMB_DEFAULT_PATH + name + ".psmb";
    std::ifstream file(spmb_path, std::ios::binary);
   
    if (!tFile::Exists(spmb_path.data())) 
    {
        printf("[INFO] - PSMB file doesn't exist. Compilation Needed\n");
        return false; 
    }

    // Load PSMB and Create shader metadata
    //
    std::vector<char> shader_byte_code_buffer = bFile::load_spirv_shader(spirv_path);
    long long         slang_lmt               = tFile::get_last_write_time(slang_path.data());
    char             *date                    = bFile::ReadString(file);
    long long         lmt                     = bFile::read_size_of<long long>(file);

    if (slang_lmt != lmt)
    {
        printf("[INFO] - PSMB Out of Date - Recompilation Needed\n");        
        return false; 
    }

    uint32_t entry_point_count                = bFile::read_size_of<uint32_t>(file);
    vk::ShaderStageFlagBits *entry_points     = bFile::read_array<vk::ShaderStageFlagBits>(file, entry_point_count);           
    uint32_t uniforms_count                   = bFile::read_size_of<uint32_t>(file);
    Uniform *uniforms                         = bFile::read_array<Uniform>(file, uniforms_count);
    uint32_t uniform_required_buffer_size     = bFile::read_int(file);
    //
    //
    //
    out_metadata.shader_buffer                = shader_byte_code_buffer;
    out_metadata.entry_points                 = (vk::ShaderStageFlagBits *)malloc(sizeof(vk::ShaderStageFlagBits) * entry_point_count);
    out_metadata.entry_points_count           = entry_point_count;

    out_metadata.uniforms                     = (Uniform *)malloc(sizeof(Uniform) * uniforms_count);
    out_metadata.uniforms_count               = uniforms_count;
    out_metadata.uniform_required_buffer_size = uniform_required_buffer_size;    

    for (size_t entry_point_idx = 0; entry_point_idx < entry_point_count; entry_point_idx++) { out_metadata.entry_points[entry_point_idx] = entry_points[entry_point_idx]; }
    for (size_t uniforms_idx    = 0; uniforms_idx    < uniforms_count;     uniforms_idx++)   { out_metadata.uniforms[uniforms_idx]        = uniforms[uniforms_idx];        }
    //
    //
    //
    free(entry_points);
    free(uniforms);    
    free(date);

    file.close();    

    return true;
}

void Shader_VK::write_shader_PSMB_to_file(const char *file_name, Shader_Metadata &metadata)
{
    std::string file_path = SHADER_COMPILED_PSMB_DEFAULT_PATH; file_path += file_name; file_path += ".psmb";
    std::ofstream file(file_path, std::ios::binary);

    const auto now         = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    const char *date       = std::ctime(&time);
    int length             = (int)strlen(std::ctime(&time));

    file.write(reinterpret_cast<char *>(&length), sizeof(uint32_t));
    file.write(date, length);

    file.write(reinterpret_cast<char *>(&this->last_write_time), sizeof(long long));

    file.write(reinterpret_cast<char *>(&metadata.entry_points_count), sizeof(uint32_t));
    bFile::write_array<vk::ShaderStageFlagBits>(file, metadata.entry_points, metadata.entry_points_count);

    file.write(reinterpret_cast<char *>(&metadata.uniforms_count), sizeof(uint32_t));
    bFile::write_array<Uniform>(file, metadata.uniforms, metadata.uniforms_count);
    file.write(reinterpret_cast<char *>(&metadata.uniform_required_buffer_size), sizeof(uint32_t));

    file.close();    
}

vk::raii::ShaderModule Shader_VK::create_shader_module(const vk::raii::Device &logicalDevice, std::vector<char> &shaderBuffer)
{
    vk::ShaderModuleCreateInfo createInfo
    {
        .codeSize = (uint32_t)shaderBuffer.size(),
        .pCode    = reinterpret_cast<uint32_t *>(shaderBuffer.data())
    };

    return { logicalDevice, createInfo };
}

std::vector<uint32_t> fMetadata::get_uniform_sizes_list_in_bytes(const Shader_Metadata &metadata)
{
    std::vector<uint32_t> sizes;

    for (size_t i = 0; i < metadata.uniforms_count; i++)
    {
        sizes.emplace_back(metadata.uniforms[i].size);
    }

    return sizes;
}
