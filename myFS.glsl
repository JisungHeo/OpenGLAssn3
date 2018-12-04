#version 440 core
// myFS.glsl
in vec2 UV;
out vec3 color;
uniform vec4 fragmentColor;
uniform sampler2D myTextureSampler;
uniform int textureExist;
void main()
{
	if(textureExist==1)
		color = texture(myTextureSampler,UV).rgb;
	else
		color = fragmentColor.rgb;
		//gl_FragColor = fragmentColor;
	
}
 