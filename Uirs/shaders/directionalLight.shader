#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCord;

uniform mat4 u_look;
uniform mat4 u_proj;
uniform mat4 u_model;


out vec3 v_normal;
out vec3 v_coord;
out vec2 v_tCord;
//vertex shader
void main() {
	gl_Position = u_proj * u_look *u_model*vec4(pos, 1);
	v_coord = pos;
	v_normal = mat3(transpose(inverse(u_model))) * normal;
	v_tCord = texCord;
}


#shader fragment
#version 330 core
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 v_normal;
in vec3 v_coord;
in vec2 v_tCord;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{

	//float len = length(v_coord - light.position);
	//float attenuation = 1.0 / (light.constant + light.linear * distance +
		//light.quadratic * (distance * distance));

	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, v_tCord).rgb;

	// diffuse 
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(-light.position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, v_tCord).rgb;

	// specular
	vec3 viewDir = normalize(viewPos - v_coord);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, v_tCord).rgb;

	vec3 result = ambient + diffuse + specular;
	//result *= attenuation;

	FragColor = vec4(result, 1.0);

}