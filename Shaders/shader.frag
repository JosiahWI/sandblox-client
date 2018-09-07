#version 330 core
out vec4 outColor;

uniform sampler2D textureSampler;

in vec2 textureCoord;


void main(){
  outColor = texture(textureSampler, textureCoord);
}