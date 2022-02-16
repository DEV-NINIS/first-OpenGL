#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(float currentFrame) : currentFrame2(currentFrame) {
 lastFrame = 0.0f; deltaTime = 0.0f; 
}
Camera::~Camera() {}

void Camera::processInputCamera(GLFWwindow* window, float currentframe, glm::vec3 cameraFront, glm::vec3 cameraUp, glm::vec3 cameraPos) {
	currentFrame2 = currentframe;
	currentFrame2 = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame2 - lastFrame;
	lastFrame = currentFrame2;
	float CameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W)) {
		cameraPos += cameraFront * CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		cameraPos -= cameraFront * CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_Q)) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * CameraSpeed;
	}
}