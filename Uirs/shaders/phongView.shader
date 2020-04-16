#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
//layout(location = 1) in vec2 texCord;
layout(location = 1) in vec3 normal;

uniform mat4 u_look;
uniform mat4 u_proj;


out vec3 v_normal;
out vec4 v_coord;

void main() {
	gl_Position = u_proj * u_look *vec4(pos, 1);
	v_coord = u_look*vec4(pos, 1);
	v_normal = mat3(transpose(inverse(u_look))) * normal;
	//v_normal = (u_look*vec4(normal,1)).xyz;
}

#shader fragment
#version 330 core

uniform sampler2D ourTexture;

uniform mat4 u_look;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;


out vec4 color;

in vec3 v_normal;
in vec4 v_coord;

void main() {
	float specularStrength = 1.0f;
	float ambientStrength = 0.1f;

	vec3 lightPosView = (u_look*vec4(lightPos, 1)).xyz;
	vec3 viewPosView = vec3(0.0f);


	vec3 normal = normalize(v_normal);
	vec3 lightDir = normalize(lightPosView - v_coord.xyz);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPosView - v_coord.xyz);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 ambient = ambientStrength * lightColor;



	//vec3 tColor = texture(ourTexture, v_texCord).rgb;

	color = vec4((ambient + diffuse + specular) *vec3(1.0f, 0.2f, 0.2f), 1.0f);

}

