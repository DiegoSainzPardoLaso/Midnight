#Vertex Shader
#version 330 core

layout(location = 0) in vec3 in_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(in_position, 1.0);
}

#Fragment Shader
#version 330 core

int fragment_screen_coords; 
int object_type_and_index;

uniform int in_object_type;
uniform int in_object_idx;

out uvec3 color;

void main()
{
    // This is explained inside the 'Picker.cpp'. Line 121 at the time I'm writting this.
    //
    // ======================================
    // Object Type And Index
    // ======================================
    // object_type_and_index = in_object_type;
    // object_type_and_index = object_type_and_index << 16;
    // object_type_and_index = object_type_and_index | (in_object_idx & 0x0000ffff);
    
    // ======================================
    // Fragment Coordinates in screen space
    // ======================================
    // fragment_screen_coords = int(gl_FragCoord.x);
    // fragment_screen_coords = fragment_screen_coords << 16;
    // fragment_screen_coords = fragment_screen_coords | (int(gl_FragCoord.y) & 0x0000ffff);           
    
    
    color = uvec3(in_object_type, in_object_idx, gl_PrimitiveID);
}


#END