#pragma once
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	bool keys[1024];
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400;
	float lastY = 300;


	bool isFirst = true;


	

	Camera(GLFWwindow*window) {
	}

	Camera() {

	}
	void processKeys(int key, int action)
	{

		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;

		float cameraSpeed = 0.05f;
		if (keys[GLFW_KEY_W])
			cameraPos += cameraSpeed * cameraFront;
		if (keys[GLFW_KEY_S])
			cameraPos -= cameraSpeed * cameraFront;
		if (keys[GLFW_KEY_A])
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (keys[GLFW_KEY_D])
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (keys[GLFW_KEY_E])
			cameraPos += cameraUp * cameraSpeed;
		if (keys[GLFW_KEY_Q])
			cameraPos -= cameraUp * cameraSpeed;

	}

	void processMouse(double xpos, double ypos) {

		if (isFirst) {
			lastX = xpos;
			lastY = ypos;
			isFirst = false;
		}
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // Обратный порядок вычитания потому что оконные Y-координаты возрастают с верху вниз 
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;


		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		cameraFront = glm::normalize(front);
	}


	glm::mat4 getViewMatrix() {
		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		return view;
	}

	glm::vec3 getPosition() {
		return cameraPos;
	}
};

class FPSCamera {

	bool keys[1024];
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400;
	float lastY = 300;

public:
	FPSCamera(GLFWwindow*window) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		lastX = xpos;
		lastY = ypos;
	}

	FPSCamera() {

	}
	void processKeys(int key, int action)
	{

		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;

		float cameraSpeed = 0.05f;
		if (keys[GLFW_KEY_W])
			cameraPos += cameraSpeed * cameraFront;
		if (keys[GLFW_KEY_S])
			cameraPos -= cameraSpeed * cameraFront;
		if (keys[GLFW_KEY_A])
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (keys[GLFW_KEY_D])
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (keys[GLFW_KEY_E])
			cameraPos += cameraUp * cameraSpeed;
		if (keys[GLFW_KEY_Q])
			cameraPos -= cameraUp * cameraSpeed;
		cameraPos.y = 0;
	}

	void processMouse(double xpos, double ypos) {

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // Обратный порядок вычитания потому что оконные Y-координаты возрастают с верху вниз 
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;


		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		cameraFront = glm::normalize(front);
	}


	glm::mat4 getViewMatrix() {
		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		return view;
	}
};