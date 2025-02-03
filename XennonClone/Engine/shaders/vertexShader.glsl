#version 450 core

// Input vertex attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 textureCoords;
layout(location = 3) in float textureIndex;

// Output to fragment shader
out vec3 Color;
out vec2 TextureCoords;
out float TextureIndex;

void main()
{
	Color = color;
	TextureCoords = textureCoords;
	TextureIndex = textureIndex;
	gl_Position = vec4(position, 1.0);
};