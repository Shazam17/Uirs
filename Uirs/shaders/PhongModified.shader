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
	gl_Position = u_proj * u_look *vec4(pos, 1);
	v_coord = pos;
	v_normal =  mat3(transpose(inverse(u_model))) * normal ;
	v_tCord = texCord;
}

#shader fragment
#version 330 core

struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;
uniform Material material;

uniform vec3 viewPos;

out vec4 color;
in vec3 v_normal;
in vec3 v_coord;
in vec2 v_tCord;

//fragment shader
void main() {
	//float specularStrength = 1.0f;
	//float ambientStrength = 0.1f;


	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_tCord));


	//diffuse
	vec3 normal = normalize(v_normal);
	vec3 lightDir = normalize(light.position - v_coord);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, v_tCord)));


	//specular
	vec3 viewDir = normalize(viewPos - v_coord);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * (vec3(0.0f) + texture(material.specular, v_tCord).rgb);

	//vec3 ambient = ambientStrength * lightColor;
	//vec3 tColor = texture(ourTexture, v_texCord).rgb;

	color = vec4((ambient + diffuse + specular), 1.0f);

}

