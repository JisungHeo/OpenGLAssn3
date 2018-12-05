#version 440 core
// flatFS.glsl

flat in vec4 color;
void main () 
{
  gl_FragColor = color;
}