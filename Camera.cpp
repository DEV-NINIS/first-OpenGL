#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(float currentFrame) : currentFrame2(currentFrame) {
	lastFrame = 0.0f; deltaTime = 1.0f; camPos = glm::vec3(0.0f, 0.0f, -3.0f); UpCam = glm::vec3(0.0f, 1.0f, 0.0f); FrontCam = glm::vec3(0.0f, 0.0f, 1.0f);
}
Camera::~Camera() {}

void Camera::processInputCamera(GLFWwindow* window, float deltatime2) 
{
	float CameraSpeed = 9.5f * deltatime2;
	if (glfwGetKey(window, GLFW_KEY_E)) {
		camPos += FrontCam * CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		camPos -= FrontCam * CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_F)) {
		camPos = camPos -= glm::normalize(glm::cross(FrontCam, UpCam)) * CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		camPos = camPos += glm::normalize(glm::cross(FrontCam, UpCam)) * CameraSpeed;
	}
}
// get value
float Camera::getdeltaTime() { return deltaTime; }
float Camera::getcurrentFrame2() { return currentFrame2; }
float Camera::getlastFrame() { return lastFrame; }

glm::vec3 Camera::getCamPos() { return camPos; }
glm::vec3 Camera::getUpCam() { return UpCam; }
glm::vec3 Camera::getFrontCam() { return FrontCam; }