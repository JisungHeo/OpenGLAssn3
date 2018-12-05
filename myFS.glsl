
#version 440 core
in vec3 fN;
in vec2 TexCoords;
in vec4 vPosition;
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight {
    vec3 direction; //position
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

uniform mat4 View;
uniform mat4 Model;
//uniform vec4 fragmentColor; //objectColor

uniform vec4 lightColor;
//uniform PointLight pointLights[2];
uniform DirLight dirLight;
uniform Material material;
uniform vec3 viewPos;
vec3 CalcDirLight(DirLight light, vec3 N, vec3 pos);
vec3 CalcPointLight(PointLight light, vec3 N, vec3 pos);
void main()
{
	// Normalize the input lighting vectors
	vec3 pos = (View*Model* vPosition).xyz;
	vec3 N = normalize(fN);

	vec3 output2 = vec3(0.0);
	//Direct light
	output2 += CalcDirLight(dirLight, N, pos);

	//Point light
	//for(int i = 0; i < 2; i++)
	//	output2 += CalcPointLight(pointLights[i], N);  

	gl_FragColor = vec4(output2, 1.0) * lightColor;
} 

vec3 CalcDirLight(DirLight light, vec3 N, vec3 pos)
{
	vec3 V = normalize(viewPos - pos);
    vec3 L = normalize(-light.direction);
	vec3 R = reflect(-L,N);

    // diffuse shading
    float diff = max(dot(N, L), 0.0);

	//Specular
    float spec = pow(max(dot(V, R), 0.0), material.shininess);
	
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	if ( dot(L, N) < 0.0 ) 
		specular = vec3(0.0, 0.0, 0.0);
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 N, vec3 pos)
{
	vec3 V = normalize(viewPos - pos);
    vec3 L = normalize(light.position-pos);
	vec3 R = reflect(-L,N);
	
    // diffuse shading
    float diff = max(dot(L,N), 0.0);

    // specular shading
    float spec = pow(max(dot(R,V), 0.0), material.shininess);

    // attenuation
    float distance   = length(light.position - pos);
    float attenuation = min(1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance)),1.0);    

    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	if ( dot(L, N) < 0.0 ) 
		specular = vec3(0.0, 0.0, 0.0);
    return (ambient + diffuse + specular) * attenuation;
}


/*
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
	
}*/
