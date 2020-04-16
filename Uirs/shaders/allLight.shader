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
	v_coord = (u_model *vec4(pos, 1)).xyz;
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
	//vec3 distanses;
};

in vec3 v_normal;
in vec3 v_coord;
in vec2 v_tCord;

uniform vec3 viewPos;


uniform Material material;

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 distanses;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 direction;
	vec3 position;
	vec3 distanses;

	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


#define lightLen 4

uniform DirLight dirLight;
uniform PointLight points[lightLen];
uniform SpotLight spotLight;

vec3 calcDirLight(vec3 norm, vec3 viewDir) {
	vec3 lightDir = normalize(-dirLight.direction);

	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);


	vec3 ambient = dirLight.ambient * texture(material.diffuse, v_tCord).rgb;
	vec3 diffuse = dirLight.diffuse * diff * texture(material.diffuse, v_tCord).rgb;
	vec3 specular = dirLight.specular * spec * texture(material.specular, v_tCord).rgb;

	vec3 result = ambient + diffuse + specular;
	return result;
}

vec3 calcPointLight(PointLight light,vec3 norm, vec3 viewDir) {

	float distance = length(light.position - v_coord);
	float attenuation = 1.0 / (light.distanses.x + light.distanses.y * distance + light.distanses.z * (distance * distance));

	vec3 ambient = light.ambient * texture(material.diffuse, v_tCord).rgb;
	
	vec3 lightDir = normalize(light.position - v_coord);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, v_tCord).rgb;

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, v_tCord).rgb;


	vec3 result = ambient + diffuse + specular;
	return result;
}

vec3 calcSpotLight(vec3 norm, vec3 viewDir) {

	float distance = length(spotLight.position - v_coord);
	float attenuation = 1.0 / (spotLight.distanses.x + spotLight.distanses.y * distance + spotLight.distanses.z * (distance * distance));


	vec3 ambient = spotLight.ambient * texture(material.diffuse, v_tCord).rgb;
	vec3 lightDir = normalize(spotLight.position - v_coord);
	// ambient


	float theta = dot(lightDir, normalize(-spotLight.direction));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensivity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

	// diffuse 


	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, v_tCord).rgb;
	
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spotLight.specular * spec * texture(material.specular, v_tCord).rgb;

	diffuse *= intensivity;
	specular *= intensivity;

	vec3 result = ambient + diffuse + specular;
	result *= attenuation;

	return result;
}

// calculates the color when using a point light.
vec3 CalcPointLight2(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.distanses.x + light.distanses.y *distance + light.distanses.z * (distance * distance));
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_tCord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_tCord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, v_tCord));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

void main()
{


	vec3 viewDir = normalize(viewPos - v_coord);
	vec3 norm = normalize(v_normal);

	//vec3 result = calcDirLight(norm, viewDir);
	vec3 result = vec3(0.0f);

	for (int i = 0; i < lightLen; i++) 
		//result += CalcPointLight2(points[i], norm, v_coord, viewDir);
	


	result += calcSpotLight(norm, viewDir);

	FragColor = vec4(result, 1.0);
	// specular


}