#version 330

#extension GL_ARB_enhanced_layouts : enable
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoord;

out vec2 textureCoord;

layout(binding = 1) uniform VP{
	mat4 view;
	mat4 proj;
}vp;

layout(binding = 2) uniform Model{
	mat4 model[512];
}model;


void main(){  
	mat4 MVP = vp.proj * vp.view * model.model[gl_InstanceID];
	gl_Position = MVP * vec4(inPosition, 1.0);

	textureCoord = inTextureCoord;
}