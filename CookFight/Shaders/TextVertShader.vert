#version 330 core


layout(location = 0) in vec2 vertPosScreenSpace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(){

    // Output position of the vertex, in clip space
    // map [0..800][0..600] to [-1..1][-1..1]

	vec2 vertPosHomSpace = vertPosScreenSpace;
	


		
	vertPosHomSpace -= vec2(400,300);
	vertPosHomSpace /= vec2(400,300);

	

	//vertPosHomSpace.y = -vertPosHomSpace.y;

    gl_Position =  vec4(vertPosHomSpace,0,1);

    // UV of the vertex. No special space for this one.
    UV.x = vertexUV.x;
	UV.y = vertexUV.y;
}