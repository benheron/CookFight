#version 330 core

layout(location = 0) in vec2 vertPosModelSpace;
layout(location = 1) in vec2 vertUV;

out vec2 UV;


uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;


uniform vec2 offsetUV;


void main()
{
	gl_Position = mvp * vec4(vertPosModelSpace, 1, 1);



    UV.x = vertUV.x + offsetUV.x;
	UV.y = vertUV.y + offsetUV.y;
}