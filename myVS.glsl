#version 440 core
// myVS.glsl

layout (location = 0) in vec3 vertexPosition;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
    gl_Position = Projection * View * Model * vec4(vertexPosition, 1);
}
 