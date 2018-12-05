#version 440 core
// myVS.glsl

layout (location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vNormal;

out vec2 TexCoords;
out vec3 fN;
out vec4 vPosition;
out vec3 FragPos;
uniform mat4 View;
uniform mat4 Model;
uniform mat4 Projection;
//uniform vec4 fragmentColor;
uniform mat4 rotateMatrix;

void main()
{
	fN =vec3(rotateMatrix*vec4(vNormal,1.0f));// vec3(Model * vec4(vNormal, 1.0f));
	//gl_Position = Projection*View*Model*vPosition;  //**gl position vs fE Â÷ÀÌ
	vPosition = vec4(vertexPosition, 1);
	gl_Position = Projection * View * Model * vec4(vertexPosition, 1);
	TexCoords = vertexUV;
	FragPos = vec3(Model * vPosition);
}