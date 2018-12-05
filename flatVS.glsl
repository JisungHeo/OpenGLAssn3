#version 440 core
in vec4 vPosition;
in vec3 vNormal;
flat out vec4 color; 

uniform mat4 View;
uniform mat4 Model;
uniform vec4 fragmentColor; //objectColor

uniform vec4 lightColor;
uniform PointLight pointLights[2];
uniform DirLight dirLight;
uniform vec3 viewPos; //camera position

void main()
{
	// Transform vertex position into eye coordinates
	vec3 pos = (View*Model* vPosition).xyz;
	vec3 V = normalize(viewPos - pos);
	vec3 N = normalize( View *Model* vec4(vNormal, 0.0) ).xyz;
	
	vec3 output = vec3(0.0);
	//Direct light
	output += CalcDirLight(dirLight, N,pos);

	//Point light
	for(int i = 0; i < 2; i++)
  		output += CalcPointLight(pointLights[i], N,pos);  
	color = vec4(output, 1.0) * lightColor * fragmentColor;

/*	//light
	vec4 lightColor = (¹¹·ÎÇÏÁö); //**
	//ambient
	float ambientStrength = 10; //**
	vec4 ambient = ambientStrength;
	
	//diffuse
	float Kd = max( dot(L, N), 0.0 );
	vec4 diffuse = Kd * lightColor;

	//specular
	int Shininess=10; //**
	float Ks = pow( max(dot(N, H), 0.0), Shininess );
	vec4 specular = Ks *specularStrength;
	if ( dot(L, N) < 0.0 ) 
		specular = vec4(0.0, 0.0, 0.0);

	gl_Position = Projection * View * Model * vPosition;
	color = (ambient + diffuse + specular) *lightColor* fragmentColor;
	color.a = 1.0; //**??*/
}

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