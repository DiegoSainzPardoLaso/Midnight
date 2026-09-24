#Vertex Shader
#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 uv;

uniform vec4 color;
uniform vec2 screenRes;
uniform vec2 transformV; 

out vec2 UVCoords;
out vec4 testColor;
out vec2 fragPixelPos;
out vec2 dOffset;

void main()
{	
    vec2 movedPos = vPos.xy;

    vec3 nPosDVC;
    nPosDVC.x =        movedPos.x / screenRes.x * 2.0 - 1.0;
    nPosDVC.y = 1.0 - (movedPos.y / screenRes.y * 2.0);
	nPosDVC.z = 1.0;


    gl_Position = vec4(nPosDVC, 1.0);

    UVCoords     = uv; 
    testColor    = color;
    fragPixelPos = vPos.xy; // also update the pixel-space value passed to fragment
	
}

#Fragment Shader
#version 330 core

in vec3 vertexColor; 
in vec2 UVCoords;
in vec4 testColor;
in vec2 fragPixelPos;

out vec4 outColor;

uniform vec4 transform;
uniform sampler2D albedo;

uniform vec4 headerColor = vec4(0.5, 0.5, 0.5, 0.9);

float headerRadius 			  = 15.0; 
float headerRightCornerRadius = 100;
float footerRadius 			  = 8.0;

void main() 
{
    // These are now in absolute screen space — do NOT apply dOffset again
    vec2 topLeft      = vec2(transform.x + footerRadius, transform.y + transform.w - footerRadius);
    vec2 topRight     = vec2(transform.x + transform.z - footerRadius, transform.y + transform.w - footerRadius);
    vec2 bottomLeft   = vec2(transform.x + headerRadius, transform.y + headerRadius);
    vec2 bottomRight  = vec2(transform.x + transform.z - headerRadius, transform.y + headerRadius);

    // Curved corner clipping logic
    bool isOutsideTopLeft     = (fragPixelPos.x < topLeft.x)     && (fragPixelPos.y  > topLeft.y)     && (length(fragPixelPos - topLeft)     > footerRadius);    
    bool isOutsideTopRight    = (fragPixelPos.x > topRight.x)    && (fragPixelPos.y  > topRight.y)    && (length(fragPixelPos - topRight)    > footerRadius);  
    bool isOutsideBottomLeft  = (fragPixelPos.x < bottomLeft.x)  && (fragPixelPos.y  < bottomLeft.y)  && (length(fragPixelPos - bottomLeft)  > headerRadius);  
    bool isOutsideBottomRight = (fragPixelPos.x > bottomRight.x) && (fragPixelPos.y  < bottomRight.y) && (length(fragPixelPos - bottomRight) > headerRightCornerRadius);

    //if (isOutsideTopLeft || isOutsideTopRight || isOutsideBottomLeft || isOutsideBottomRight) { discard; } 

    
    if (fragPixelPos.y < transform.y + 40.0) // 40 = Header Height
    {
       outColor = headerColor;
    }
    else
    {
        outColor = testColor;
    }
}



#END