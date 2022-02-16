#ifndef DEF_CAMERA
#define DEF_CAMERA
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
public:
	Camera(float currentFrame);
	~Camera();
	void processInputCamera(GLFWwindow* window, float currentFrame, glm::vec3 cameraFront, glm::vec3 cameraUp, glm::vec3 cameraPos);
private:
	float deltaTime;
	float lastFrame;
	float currentFrame2;
};

#endif // !1

