#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
//layout(location = 1) in vec2 texCord;
layout(location = 1) in vec3 normal;

uniform mat4 u_look;
uniform mat4 u_proj;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;


out vec3 v_diffuse;
out vec3 v_specular;
out vec3 v_ambient;

void main() {
	gl_Position = u_proj * u_look *vec4(pos, 1);

	float specularStrength = 1.0f;
	float ambientStrength = 0.1f;


	vec3 lightDir = normalize(lightPos - pos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 ambient = ambientStrength * lightColor;

	v_diffuse = diffuse;
	v_specular = specular;
	v_ambient = ambient;
}

#shader fragment
#version 330 core

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;


out vec4 color;


in vec3 v_diffuse;
in vec3 v_specular;
in vec3 v_ambient;

void main() {
	



	//vec3 tColor = texture(ourTexture, v_texCord).rgb;

	color = vec4((v_ambient + v_diffuse + v_specular) *vec3(1.0f, 0.2f, 0.2f), 1.0f);

}

