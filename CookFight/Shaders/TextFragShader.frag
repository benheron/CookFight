#version 330 core
in vec2 UV;

out vec4 colour;


uniform sampler2D myTextureSampler;

void main(){
    colour = texture( myTextureSampler, UV );
  // colour = vec4(1,0,0,1);
}