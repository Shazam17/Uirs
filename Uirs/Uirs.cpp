
#define GLEW_STATIC
#include <GLFW/glew.h>

#include <string>


#include "Shader.h"
#include "Camera.h"
#include "VBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Mesh.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#define Log(x) std::cout << x << std::endl

using namespace std;
using namespace glm;

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f 
};

Camera camera;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	camera.processKeys(key, action);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera.processMouse(xpos, ypos);
}


void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}


GLFWwindow* createWindow() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "glfw init failed" << std::endl;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1600, 1200, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "window failes" << std::endl;
	}


	glfwMakeContextCurrent(window);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "glew error" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	return window;
}


glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
void checkGLError()
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << err << std::endl;
	}
}
int main(void)
{
	GLFWwindow* window = createWindow();
	camera = Camera(window);

	//Shader shad("shaders/phongCheck.shader");
	Shader shadLighter("shaders/lightCube.shader");
	//Shader dirLight("shaders/directionalLight.shader");

	//Shader pointLight("shaders/pointLight.shader");
	Shader spotLight("shaders/spotLight.shader");
	Shader spotLightModed("shaders/spotLightWithDistances.shader");
	Shader allLights("shaders/complexShader.shader");
	

	Shader allLights1("shaders/allLight.shader");


	Texture txt("txts/container2.png");
	Texture containerSpecular("txts/container2_specular.png");

	VBO vb(vertices, sizeof(vertices));
	
	VAO::Layout la;
	la.add<float>(3);
	la.add<float>(3);
	la.add<float>(2);

	Mesh cubeContainer(vertices, sizeof(vertices), la);

	auto lookMat = glm::lookAt(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	auto projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);


	auto ident = glm::mat4(1.0f);
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 lightColor(1.0f);

	Material mat;
	mat.shininess = 32.0f;
	mat.diffBlock = 0;
	mat.specBlock = 1;

	Light light;
	light.ambient = vec3(0.2f, 0.2f, 0.2f);
	light.diffuse = vec3(0.5f, 0.5f, 0.5f);
	light.specular = vec3(1.0f, 1.0f, 1.0f);
	light.pos = lightPos;
	light.constant = 1.0;
	light.linear = 0.09f;
	light.quadratic = 0.032f;
	light.dist = vec3(1.0f, 0.09f, 0.032f);



	Mesh cubeLight(vertices,sizeof(vertices),la);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.3f));

	shadLighter.setUniform4m("u_model", model);
	shadLighter.setUniform4m("u_proj", projMat);
	shadLighter.setUniform4m("u_look", lookMat);
	
	//spotLightModed.setUniform4m("u_proj", projMat);
	//spotLightModed.setUniform4m("u_look", lookMat);
	//spotLightModed.setUniform4m("u_model", ident);
	//spotLightModed.setMaterial("material", mat);
	//spotLightModed.setLight("light", light);

	//spotLightModed.setUniform1f("cutOff", glm::cos(glm::radians(12.5f)));
	//spotLightModed.setUniform1f("outerCutOff", glm::cos(glm::radians(17.5f)));
	//spotLightModed.setUniformVec3("distanses", light.dist);
	

	allLights.setUniform4m("u_model", model);
	allLights.setUniform4m("u_proj", projMat);
	allLights.setUniform4m("u_look", lookMat);


	vec3 dir(-0.2f, -1.0f, -0.3f);
	vec3 ambDir(0.05f, 0.05f, 0.05f);
	vec3 difDir(0.4f, 0.4f, 0.4f);
	vec3 specDir(0.5f, 0.5f, 0.5f);


	allLights.setUniformVec3("dirLight.direction", dir);
	allLights.setUniformVec3("dirLight.ambient",  ambDir);
	allLights.setUniformVec3("dirLight.diffuse", difDir);
	allLights.setUniformVec3("dirLight.specular", specDir);


	allLights.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	allLights.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
	allLights.setUniformVec3("spotLight.distanses", light.dist);


	vec3 spotAmb(0.0f, 0.0f, 0.0f);
	vec3 spotDiff(1.0f, 1.0f, 1.0f);
	vec3 spotSpec(1.0f, 1.0f, 1.0f);

	allLights.setUniformVec3("spotLight.ambient", ambDir);
	allLights.setUniformVec3("spotLight.diffuse", difDir);
	allLights.setUniformVec3("spotLight.specular", specDir);

	glm::vec3 pointLightPositions[] = {

		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)

	};


	vec3 pointAmb(0.05f, 0.05f, 0.05f);
	vec3 pointDiff(0.8f, 0.8f, 0.8f);
	vec3 pointSpec(1.0f, 1.0f, 1.0f);



	for(int i = 0; i < 4; i++) {
		std::stringstream ss;
		ss << i;
		string posLoc = "points[" + ss.str() + "].position";
		string distLoc = "points[" + ss.str() + "].distanses";
		string ambLoc = "points[" + ss.str() + "].ambient";
		string difLoc = "points[" + ss.str() + "].diffuse";
		string specLoc = "points[" + ss.str() + "].specular";

		allLights.setUniformVec3(posLoc.c_str(), pointLightPositions[i]);

		allLights.setUniformVec3(distLoc.c_str(), light.dist);
		allLights.setUniformVec3(ambLoc.c_str(), pointAmb);
		allLights.setUniformVec3(difLoc.c_str(), pointDiff);
		allLights.setUniformVec3(specLoc.c_str(), pointSpec);

	}

	while (!glfwWindowShouldClose(window))
	{
		checkGLError();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.getViewMatrix();
		glm::vec3 pos = camera.getPosition();
		glm::vec3 dir = camera.cameraFront;

		shadLighter.setUniform4m("u_look", view);
		allLights.setUniform4m("u_look", view);
		allLights.setUniformVec3("viewPos", pos);

		allLights.setUniformVec3("spotLight.direction", dir);
		allLights.setUniformVec3("spotLight.position", pos);

		txt.bind(0);
		containerSpecular.bind(1);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			allLights.setUniform4m("u_model", model);

			cubeContainer.draw(allLights, 36);
		}


		for (int i = 0; i < 4; i++) {
			glm::mat4 model(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			shadLighter.setUniform4m("u_model", model);
			cubeLight.draw(shadLighter, 36);
		}

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}