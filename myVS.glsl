/*#version 440 core
// myVS.glsl

layout (location = 0) in vec3 vertexPosition;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
    gl_Position = Projection * View * Model * vec4(vertexPosition, 1);
}*/
 
in vec4 vPosition;
in vec3 vNormal;

out vec3 fN;

uniform mat4 View;
uniform mat4 Model;
uniform mat4 Projection;
uniform vec4 fragmentColor;

void main()
{
	fN = vNormal;
	gl_Position = Projection*View*Model*vPosition;  //**gl position vs fE ����
}