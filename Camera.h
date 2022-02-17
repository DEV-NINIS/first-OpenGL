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
	// getting value
	glm::vec3 getCamPos();
	glm::vec3 getUpCam();
	glm::vec3 getFrontCam();

	float getdeltaTime();
	float getlastFrame();
	float getcurrentFrame2();
private:
	float deltaTime;
	float lastFrame;
	float currentFrame2;
	glm::vec3 camPos;
	glm::vec3 UpCam;
	glm::vec3 FrontCam;
};

#endif // !1

