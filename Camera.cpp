#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(float currentFrame) : currentFrame2(currentFrame) {
 lastFrame = 0.0f; deltaTime = 1.0f; 
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
		camPos = cameraPos;
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		cameraPos -= cameraFront * CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_Q)) {
		camPos = cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		camPos = cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * CameraSpeed;
	}
}
// get value
float Camera::getdeltaTime() { return deltaTime; }
float Camera::getcurrentFrame2() { return currentFrame2; }
float Camera::getlastFrame() { return lastFrame; }

glm::vec3 Camera::getCamPos() { return camPos; }
glm::vec3 Camera::getUpCam() { return UpCam; }
glm::vec3 Camera::getFrontCam() { return FrontCam; }