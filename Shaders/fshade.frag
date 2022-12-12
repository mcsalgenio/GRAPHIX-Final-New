#version 330 core 

in vec2 texCoord; 
uniform sampler2D tex0; 
uniform sampler2D norm_tex;

in vec3 normCoord;
in vec3 fragPos;

in mat3 TBN;

uniform vec3 lightPos; //Position of directional light source
uniform vec3 lightColor;
uniform vec3 ptLightPos; //position of point light source
uniform vec3 ptLightColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

out vec4 FragColor; 

void main()
{
	vec3 normal = texture(norm_tex, texCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0); 
	normal = normalize(TBN * normal);

	vec3 viewDir = normalize(cameraPos - fragPos);

	//Direction Light
	vec3 lightDir = normalize(-lightPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 ambientCol = ambientColor * ambientStr;
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);
	vec3 specColor = spec * specStr * lightColor;

	vec3 dirLight = (diffuse + ambientCol + specColor);

	//Point Light for ship
	vec3 ptLightDir = normalize(ptLightPos - fragPos); 
	diff = max(dot(normal, ptLightDir), 0.0);
	diffuse = diff * ptLightColor;
	ambientCol = ambientColor * ambientStr;
	reflectDir = reflect(-ptLightDir, normal);
	spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);
	specColor = spec * specStr * ptLightColor;

	//attenuation for point light
	float constant = 1.0f;
	float linear = 0.022f;
	float quadratic = 0.0019f;
	float distance = length(ptLightPos - fragPos);
	float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

	vec3 pointLight = (diffuse * attenuation + ambientCol * attenuation + specColor * attenuation);

	FragColor = vec4(dirLight + pointLight, 1.0f) * texture(tex0, texCoord);
}