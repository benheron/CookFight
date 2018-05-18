#version 330 core

in vec2 UV;

uniform sampler2D textureSampler;
uniform vec4 blendColour;

out vec4 colour;


void main()
{
	colour = texture( textureSampler, UV );
	colour *= blendColour;
}