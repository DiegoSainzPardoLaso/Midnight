#include "MOFLoader.h" 

MOFLoader::Data MOFLoader::LoadMesh(const char* path)
{		

	if (tFile::compare_extension(path, __MOF__))  { return Internal::LoadBinary(path); }
	if (tFile::compare_extension(path, __MOFT__)) { return Internal::LoadASCII(path);  }
	
	const char* fileName = tFile::get_name(path);
	Message::Error("Unidentified file format. Returning empty mesh", fileName);
	return Data();
}

MOFLoader::Data MOFLoader::Internal::LoadBinary(const char* path)
{
	Data  data{};
	int   vertex_count;
	int   stride;
	char* name;
	char* date;

	Vec3 minimumCoordinates{};
	Vec3 maximumCoordinates{};

	std::ifstream file(path, std::ios::binary | std::ios::in);
	
	// Mesh
	//     
	date   = bFile::ReadString(file);
	name   = bFile::ReadString(file);	
	vertex_count = bFile::read_int(file);
	stride = bFile::read_int(file);

	if (stride <= 0)
	{
		Message::Error("Failed to Load Mesh Wrong Stride Value Retrieved", std::to_string(stride).data());
		return Data{}; 
	}

	if (vertex_count <= 0 || vertex_count == 0xCCCCCCCC)
	{
		Message::Error("Failed to Load Mesh Wrong Vertex Count Value Retrieved", std::to_string(vertex_count).data());
		return Data{};
	}
	

	if (stride == 11)
	{
		data.staticMesh.vertex_count   = vertex_count;
		data.staticMesh.total_vertices_byte_size    = vertex_count * sizeof(sVertex);
		data.staticMesh.vertices = reinterpret_cast<sVertex*>(malloc(sizeof(sVertex) * data.staticMesh.vertex_count));
	
		for (unsigned int i = 0; i < data.staticMesh.vertex_count; i++)
		{		
			data.staticMesh.vertices[i].position = bFile::read_size_of<Vec3>(file);			
			data.staticMesh.vertices[i].color    = bFile::read_size_of<Vec3>(file);
			data.staticMesh.vertices[i].normal   = bFile::read_size_of<Vec3>(file);
			data.staticMesh.vertices[i].uv	     = bFile::read_size_of<Vec2>(file);


			// Find Bounding Box
			//
			Vec3 &position = data.staticMesh.vertices[i].position;
			
			minimumCoordinates.x = minimumCoordinates.x >= position.x ? position.x : minimumCoordinates.x;
			minimumCoordinates.y = minimumCoordinates.y >= position.y ? position.y : minimumCoordinates.y;
			minimumCoordinates.z = minimumCoordinates.z >= position.z ? position.z : minimumCoordinates.z;
			
			maximumCoordinates.x = maximumCoordinates.x <= position.x ? position.x : maximumCoordinates.x;
			maximumCoordinates.y = maximumCoordinates.y <= position.y ? position.y : maximumCoordinates.y;
			maximumCoordinates.z = maximumCoordinates.z <= position.z ? position.z : maximumCoordinates.z;
		}
	
#if CURRENT_RENDERING_API == OPENGL
		data.boundingBox = fAABB::Create(minimumCoordinates, maximumCoordinates, { 1, 1, 1 });
#endif

		data.staticMesh.index_count  = bFile::read_int(file);
		data.staticMesh.indices = reinterpret_cast<int*>(malloc(sizeof(int) * data.staticMesh.index_count));

		for (U32 i = 0; i < data.staticMesh.index_count; i++)
		{
			data.staticMesh.indices[i] = bFile::read_int(file);
		}
									
		data.successReading = true;	
	}
	else
	{
		data.mesh.vertex_count   = vertex_count;
		data.mesh.total_vertices_byte_size    = data.mesh.vertex_count * stride;
		data.mesh.vertices = reinterpret_cast<aVertex*>(malloc(sizeof(aVertex) * data.mesh.vertex_count));
	
		for (unsigned int i = 0; i < data.mesh.vertex_count; i++)
		{		
			data.mesh.vertices[i].position         = bFile::read_size_of<Vec3>(file);
			data.mesh.vertices[i].color            = bFile::read_size_of<Vec3>(file);
			data.mesh.vertices[i].normal           = bFile::read_size_of<Vec3>(file);
			data.mesh.vertices[i].uv               = bFile::read_size_of<Vec2>(file);
			data.mesh.vertices[i].influenceIndices = bFile::read_size_of<IVec4>(file);
			data.mesh.vertices[i].weights          = bFile::read_size_of<Vec4>(file);


			// Find Bounding Box
			//
			Vec3 &position = data.mesh.vertices[i].position;

			minimumCoordinates.x = minimumCoordinates.x >= position.x ? position.x : minimumCoordinates.x;
			minimumCoordinates.y = minimumCoordinates.y >= position.y ? position.y : minimumCoordinates.y;
			minimumCoordinates.z = minimumCoordinates.z >= position.z ? position.z : minimumCoordinates.z;
			
			maximumCoordinates.x = maximumCoordinates.x <= position.x ? position.x : maximumCoordinates.x;
			maximumCoordinates.y = maximumCoordinates.y <= position.y ? position.y : maximumCoordinates.y;
			maximumCoordinates.z = maximumCoordinates.z <= position.z ? position.z : maximumCoordinates.z;
		}
	
		data.boundingBox  = fAABB::Create(minimumCoordinates, maximumCoordinates, { 1, 1, 1 });

		data.mesh.index_count  = bFile::read_int(file);
		data.mesh.indices = reinterpret_cast<int*>(malloc(sizeof(int) * data.mesh.index_count));

		for (U32 i = 0; i < data.mesh.index_count; i++)
		{
			data.mesh.indices[i] = bFile::read_int(file);
		}
		
		U32 jointCount = 0;		
		jointCount     = bFile::read_int(file);
		data.skeleton  = fSkeleton::Create(jointCount);
		

				
		for (U32 i = 0; i < jointCount; i++)
		{
			Joint		     joint{};
			int              parentIdx;
		 				
			joint.name       = bFile::ReadString(file);
			joint.idx        = bFile::read_int(file);
			parentIdx        = bFile::read_int(file);
			joint.parent	 = fSkeleton::GetJoint(data.skeleton, parentIdx);
			joint.childCount = bFile::read_int(file);
			joint.children   = reinterpret_cast<Joint**>(malloc(sizeof(Joint) * joint.childCount));

			for (unsigned int c = 0; c < joint.childCount; c++)
			{			
				joint.children[c] = &data.skeleton.joints[bFile::read_int(file)];
			}

			joint.position          = bFile::read_size_of<Vec3>(file);
			joint.orientation       = bFile::read_size_of<Quat>(file);
			joint.scale             = bFile::read_size_of<Vec3>(file);
			joint.originalTransform = MILA::BuildModelSpaceTransform(joint.position, joint.orientation, joint.scale);

			fSkeleton::AddJoint(data.skeleton, joint, i);
		}
	
		data.skeleton.root = &data.skeleton.joints[0];	
	
		fTransform::Initialize(data.skeleton.transform);
		
		data.successReading = true;	
	}
	
	free(name);
	free(date);

	file.close();

	return data;
}

MOFLoader::Data MOFLoader::Internal::LoadASCII(const char* path)
{
	Data	 data{};    
	Joint	 tmpJoint{};
	
    std::string line            = "";    
    std::string name            = "";
    int         strideLength    = 0;        
    bool		readingVertices = false;
    bool		readingIndices  = false;
    bool		readingSkeleton = false;
	uint32_t    iIdx            = 0;
    uint32_t    vIdx            = 0;

	Vec3		minimumCoordinates{};
	Vec3		maximumCoordinates{};
    	
    std::ifstream file(path, std::ios::in);
    while(std::getline(file, line))
    {		
        std::vector<std::string> tokens = fUtil::TokenizeLine(line, ' ', NULL, NULL);
		 				        
        if (!tokens[0].compare("name:") && name.size() <= 0)
		{			
			bool startReading = false;
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == '\n' || line[i] == '-') { break; }
				if (startReading)   { name += line[i]; }
				if (line[i] == ':') { startReading = true; }
			}
		}
        
        if (!tokens[0].compare("stride")) 
        {
            strideLength = std::stoi(tokens[2]); 

			if (strideLength <= 0)
			{
				Message::Error("Failed to Load Animated Mesh Wrong Stride Value Retrieved", std::to_string(strideLength).data());
				return Data{};
			}
			
            data.mesh.total_vertices_byte_size  = strideLength * data.mesh.vertex_count;
        }
        
		if (strideLength == 19)
		{

			if (!tokens[0].compare("vertex"))
			{
				data.mesh.vertex_count   = std::stoi(tokens[2]);

				if (data.mesh.vertex_count <= 0 || data.mesh.vertex_count == 0xCCCCCCCC)
				{
					Message::Error("Failed to Load Animated Mesh Wrong Vertex Count Value Retrieved", std::to_string(data.mesh.vertex_count).data());
					return Data{};
				}

				data.mesh.vertices = reinterpret_cast<aVertex*>(malloc(sizeof(aVertex) * data.mesh.vertex_count));
			}
                                
			if (!tokens[0].compare("v0:") || (readingVertices && vIdx < data.mesh.vertex_count))
			{
				aVertex v{};
				v.position  	         = { std::stof(tokens[2]),  std::stof(tokens[3]), std::stof(tokens[4])                          };
				v.color 		         = { std::stof(tokens[5]),  std::stof(tokens[6]), std::stof(tokens[7])                          };
				v.normal		         = { std::stof(tokens[8]),  std::stof(tokens[9]), std::stof(tokens[10])                         };
				v.uv			         = { std::stof(tokens[11]), std::stof(tokens[12])                                               };
				v.influenceIndices       = { std::stoi(tokens[13]), std::stoi(tokens[14]), std::stoi(tokens[15]), std::stoi(tokens[16]) };
				v.weights                = { std::stof(tokens[17]), std::stof(tokens[18]), std::stof(tokens[19]), std::stof(tokens[20]) };
				data.mesh.vertices[vIdx] = v;
				readingVertices          = true;

				Vec3 &position = v.position;

				minimumCoordinates.x = minimumCoordinates.x >= position.x ? position.x : minimumCoordinates.x;
				minimumCoordinates.y = minimumCoordinates.y >= position.y ? position.y : minimumCoordinates.y;
				minimumCoordinates.z = minimumCoordinates.z >= position.z ? position.z : minimumCoordinates.z;

				maximumCoordinates.x = maximumCoordinates.x <= position.x ? position.x : maximumCoordinates.x;
				maximumCoordinates.y = maximumCoordinates.y <= position.y ? position.y : maximumCoordinates.y;
				maximumCoordinates.z = maximumCoordinates.z <= position.z ? position.z : maximumCoordinates.z;

				vIdx++;
			}      
        
			if (readingIndices && iIdx < data.mesh.index_count)
			{
				data.mesh.indices[iIdx + 0] = std::stoi(tokens[0]);
				data.mesh.indices[iIdx + 1] = std::stoi(tokens[1]);
				data.mesh.indices[iIdx + 2] = std::stoi(tokens[2]);
            
				iIdx += 3;
			}
                       
			if (readingSkeleton)
			{									
				// name: Bone - index: 0 - parent index: 0 - children count: 1 - children indices { 1 }
				//
				if (!tokens[0].compare("name:"))
				{
					int  kind                 = -1;
					bool reading              = false;
					std::string retrievedData = "";

					for (unsigned int i = 0; i < line.size(); i++)
					{
						if (line[i] == '-' || line[i] == '}')
						{										
							if (kind == 0)
							{
								tmpJoint.name = reinterpret_cast<char*>(malloc(retrievedData.size()));
								strcpy(tmpJoint.name, retrievedData.data());
							}
							if (kind == 1) { tmpJoint.idx    = std::stoi(retrievedData);                                }
							if (kind == 2) { tmpJoint.parent = fSkeleton::GetJoint(data.skeleton, std::stoi(retrievedData)); }
							if (kind == 3) 
							{
								tmpJoint.childCount = std::stoi(retrievedData);
								tmpJoint.children   = reinterpret_cast<Joint**>(malloc(sizeof(Joint) * tmpJoint.childCount));
							}
					
							// Child Indices
							//
							if (kind == 4) 
							{
								std::vector<std::string> childTokens = fUtil::TokenizeLine(retrievedData, ' ', NULL, NULL);
							
								for (int c = 0; c < childTokens.size() - 1; c++)
								{
									tmpJoint.children[c] = &data.skeleton.joints[std::stoi(childTokens[c])];
								}																			
							}
														
							reading = false; 
							retrievedData    = "";
						}				

						if (reading) { retrievedData += line[i]; }
				
						if (line[i] == ':' || line[i] == '{')
						{
							i++;										
							reading = true;
							kind++;
						}
					}
				}

				if (!tokens[0].compare("position:"))    { tmpJoint.position    = { std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]) };						  }
				if (!tokens[0].compare("orientation:")) { tmpJoint.orientation = { std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]) }; }
				if (!tokens[0].compare("scale:"))       
				{
					tmpJoint.scale			   = { std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]) };			
					tmpJoint.originalTransform = MILA::BuildModelSpaceTransform(tmpJoint.position, tmpJoint.orientation, tmpJoint.scale);
					fSkeleton::AddJoint(data.skeleton, tmpJoint, tmpJoint.idx);
				}
			}

			if (!tokens[0].compare("armature"))
			{
				data.skeleton   = fSkeleton::Create(std::stoi(tokens[3]));
				readingSkeleton = true;
				readingIndices  = false;
			}
		
			if (!tokens[0].compare("indices")) 
			{
				data.mesh.index_count  = std::stoi(tokens[2]); 
				data.mesh.indices = reinterpret_cast<int*>(malloc(sizeof(int) * data.mesh.index_count));
				readingVertices   = false;
				readingIndices    = true;
			}
		}
		else
		{
			if (!tokens[0].compare("vertex"))
			{
				data.staticMesh.vertex_count   = std::stoi(tokens[2]);

				if (data.staticMesh.vertex_count <= 0 || data.staticMesh.vertex_count == 0xCCCCCCCC)
				{
					Message::Error("Failed to Load Animated Mesh Wrong Vertex Count Value Retrieved", std::to_string(data.staticMesh.vertex_count).data());
					return Data{};
				}

				data.staticMesh.vertices = reinterpret_cast<sVertex*>(malloc(sizeof(sVertex) * data.staticMesh.vertex_count));
			}
                                
			if (!tokens[0].compare("v0:") || (readingVertices && vIdx < data.staticMesh.vertex_count))
			{
				sVertex v{};
				v.position  	         = { std::stof(tokens[2]),  std::stof(tokens[3]), std::stof(tokens[4])  };
				v.color 		         = { std::stof(tokens[5]),  std::stof(tokens[6]), std::stof(tokens[7])  };
				v.normal		         = { std::stof(tokens[8]),  std::stof(tokens[9]), std::stof(tokens[10]) };
				v.uv			         = { std::stof(tokens[11]), std::stof(tokens[12])                       };				

				data.staticMesh.vertices[vIdx] = v;
				readingVertices              = true;

				Vec3 &position = v.position;

				minimumCoordinates.x = minimumCoordinates.x >= position.x ? position.x : minimumCoordinates.x;
				minimumCoordinates.y = minimumCoordinates.y >= position.y ? position.y : minimumCoordinates.y;
				minimumCoordinates.z = minimumCoordinates.z >= position.z ? position.z : minimumCoordinates.z;

				maximumCoordinates.x = maximumCoordinates.x <= position.x ? position.x : maximumCoordinates.x;
				maximumCoordinates.y = maximumCoordinates.y <= position.y ? position.y : maximumCoordinates.y;
				maximumCoordinates.z = maximumCoordinates.z <= position.z ? position.z : maximumCoordinates.z;

				vIdx++;
			}      
        
			if (readingIndices && iIdx < data.staticMesh.index_count)
			{
				data.staticMesh.indices[iIdx + 0] = std::stoi(tokens[0]);
				data.staticMesh.indices[iIdx + 1] = std::stoi(tokens[1]);
				data.staticMesh.indices[iIdx + 2] = std::stoi(tokens[2]);
            
				iIdx += 3;
			}

			if (!tokens[0].compare("indices"))
			{
				data.staticMesh.index_count  = std::stoi(tokens[2]);
				data.staticMesh.indices = reinterpret_cast<int *>(malloc(sizeof(int) * data.staticMesh.index_count));
				readingVertices         = false;
				readingIndices          = true;
			}
		}
    }

	data.boundingBox = fAABB::Create(minimumCoordinates, maximumCoordinates, { 1, 1, 1 });

	data.skeleton.root  = &data.skeleton.joints[0];
	fTransform::Initialize(data.skeleton.transform);

	file.close();

	data.successReading = true;
	
    return data;
}