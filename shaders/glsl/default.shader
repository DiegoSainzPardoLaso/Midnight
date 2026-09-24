#Vertex Shader
#version 330 core
// Note: I'm filtering the comments by using a / at the start of a comment :)
layout (location = 0) in vec3 in_vPos;
layout (location = 1) in vec3 in_vCol;
layout (location = 2) in vec3 in_norm;
layout (location = 3) in vec2 in_uv;
// Animated models | I should have a defaultAnimatedModels and a regular default for static meshes
layout (location = 4) in ivec4 jointInfluenceIdx;			
layout (location = 5) in vec4  weightInflueceValueIdx;		

// Constants
//
const int MAX_SKELETON_JOINT_COUNT = 128;
const int MAX_WEIGHTS_PER_VERTES   = 4;

// Pass this information as an SSBO instead of as a uniform,
// That way im no longer limited to the max_skeleton_joint_count
//
uniform mat4 jointTransforms[MAX_SKELETON_JOINT_COUNT];
uniform mat4 mvp; 
 
out vec3 pos;
out vec3 vertexColor;
out vec4 normalV;
out vec2 UVCoords;

void main()
{
	// Update vertex position and normal, based on the joints that exercise influence over it
	// 
	vec4 vertexPosition = vec4(in_vPos, 1);
    vec4 newAnimationPosePosition = vec4(0, 0, 0, 0);
	
	vec4 normal = vec4(in_norm, 0);
    vec4 newAnimationPoseNormal = vec4(0, 0, 0, 0);
	
	for (int idx = 0; idx < MAX_WEIGHTS_PER_VERTES; idx++)
	{
		vec4 p = jointTransforms[jointInfluenceIdx[idx]] * vertexPosition;
		newAnimationPosePosition += p * weightInflueceValueIdx[idx];
		
		vec4 np = jointTransforms[jointInfluenceIdx[idx]] * normal;
		newAnimationPoseNormal += np * weightInflueceValueIdx[idx];
	}	
	 
	gl_Position = mvp * newAnimationPosePosition;
		
	pos		    = vec3(newAnimationPosePosition.xyz);	
	vertexColor = in_vCol;
	normalV     = newAnimationPoseNormal;
	UVCoords    = in_uv;	
}

#Fragment Shader
#version 330 core
 
in vec3  pos;
in vec3  vertexColor; 
in vec4  normalV;
in vec2  UVCoords;

out vec4 outColor;

uniform sampler2D albedo;
uniform sampler2D normal;

vec3 SimpleLighting()
{
	vec3 lightPos      = vec3(0, 2, 5);
	vec3 L             = lightPos - pos;
	vec3 N             = normalize(normalV.xyz);
	float ambientValue = 0.0;
	return vec3(dot(L, N));
}
 
void main()
{	 
	//  
	vec3 col = SimpleLighting();
	outColor = normalize(vec4(normalV.xyz, 1.0) * vec4(col, 1.0) + 121.5) * vec4(0,0,0, 1.0); 
	
}
 
#END