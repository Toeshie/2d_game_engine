#version 450 core

// Input from vertex shader
in vec3 Color;
in vec2 TextureCoords;
in float TextureIndex;

// Uniform samplers
uniform sampler2D Textures[32];

// Output color
out vec4 outColor;

void main()
{
    // Convert texture index to integer for array access
    int index = int(TextureIndex);
    vec4 texColor = texture(Textures[index], TextureCoords);
    
    // Magenta color key for transparency (1, 0, 1)
    const float epsilon = 0.001;
    if (abs(texColor.r - 1.0) < epsilon && 
        abs(texColor.g) < epsilon && 
        abs(texColor.b - 1.0) < epsilon) 
    {
        discard;
    }
    
    outColor = texColor;
}