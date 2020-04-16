#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
//layout(location = 1) in vec2 texCord;


uniform mat4 u_look;
uniform mat4 u_proj;
uniform mat4 u_model;

out vec2 v_texCord;

void main() {
	gl_Position = u_proj * u_look * u_model* vec4(pos, 1);
}

#shader fragment
#version 330 core

out vec4 color;
void main() {
	color = vec4(1.0f);

}