#include <iostream>
#include <string>
#include "refresh_color.h"
#include "compileShaders.h"
#include "AddBuffer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define KEY_A 97



bool firstMouse = true;
float Yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float Pitch = 0.0f;
float LastXPos = 800.0f / 2.0;
float LastYPos = 600.0 / 2.0;
float fov = 45.0f;
float sensivity = 0.05f;

glm::vec3 frontCallback;
glm::vec3 upCallback;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)xoffset * sensivity;
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}
void mouse_callback(GLFWwindow* window, double xposIN, double yposIN) {
    float xoffset = static_cast<float>(xposIN - LastXPos);
    float yoffset = static_cast<float>(LastYPos - yposIN);

    LastXPos = static_cast<float>(xposIN);
    LastYPos = static_cast<float>(yposIN);

    xoffset *= sensivity;
    yoffset *= sensivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f) { Pitch = 89.0f; }
    if (Pitch < -89.0f) { Pitch = -89.0f; }
    
    frontCallback.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    frontCallback.y = sin(glm::radians(Pitch));
    frontCallback.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    


}
void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, 2560, 1440);
}
void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
int main() {
    std::string a;
    std::cout << " polygon mode 1: ou normal mode 2:" << std::endl;
    int resX = 1920, resY = 1080;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    int resX2 = 2560;
    int resY2 = 1440;
    float resFx = 2560;
    float resFy = 1440;
    GLFWwindow* window = glfwCreateWindow(resX2, resY2, "opengl_anis", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return-1;
    }
    glViewport(0, 0, resX2, resY2);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
    //
    float vertecies[] = {

        // position         // color
       // positions         // colors
    -0.5f, -0.5f, -0.5f,   0.2f, 0.6f, 0.9f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.9f, 0.6f, 0.2f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.5f, 0.6f, 0.9f,1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.7f, 0.6f, 0.8f,1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.1f, 0.6f, 0.9f,0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.3f, 0.6f, 0.1f,0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.2f, 0.1f, 0.9f,0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.9f, 0.6f, 0.9f,1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.2f, 0.2f, 0.9f,1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.3f, 0.6f, 0.1f,1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.2f, 0.3f, 0.9f,0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.2f, 0.6f, 0.9f,0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f,  0.9f, 0.1f, 0.2f,1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.4f, 0.6f, 0.8f,1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.4f,0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.1f, 0.2f, 0.8f,0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.6f, 0.6f, 0.9f,0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.3f,1.0f, 0.0f,

        0.5f,  0.5f,  0.5f, 0.3f, 0.9f, 0.9f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 0.9f, 0.4f, 0.3f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.1f, 0.6f, 0.9f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.7f, 0.1f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 0.2f, 0.4f, 0.1f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 0.7f, 0.9f, 0.0f, 1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f, 0.7f, 0.6f, 0.8f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.5f, 0.4f, 0.1f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 0.6f, 0.6f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 0.9f, 0.3f, 0.2f, 1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f, 0.1f, 0.9f, 0.7f, 0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f, 0.2f, 0.1f, 0.9f, 0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 0.4f, 0.7f, 0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 0.2f, 0.4f, 0.6f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 0.3f, 0.3f, 0.6f, 1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, 0.9f, 0.9f, 0.1f, 0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f, 0.1f, 0.1f, 0.4f, 0.0f, 1.0f
    };
    float vertecies2[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f,  // top 
        0.10, 0.5, 0.4
    };
    glm::vec3 cubePosition[] = {
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
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3// premier triangle 
    };
    unsigned int indices2[] = {
        1, 0, 2 // premier triangle 
    };
    compileShaders compile("C:/Users/anise/source/repos/openGL1/vertex.txt", "C:/Users/anise/source/repos/openGL1/frag.txt");
    unsigned int VAO[1], VBO[2];
    unsigned int EBO[2];
    unsigned int VAO2, VBO2;
    unsigned int EBO2;
    std::vector<unsigned int> VAO_vec;
    VAO_vec.push_back(0);
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &EBO[0]);
    glGenBuffers(1, &VBO[0]);

    // 1. attacher le Vertex Array Object
    glBindVertexArray(VAO[0]);

    // 2. copier les sommets dans un VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

    // 3. copier le tableau d?indices dans un tampon d??l?ments
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4. ?tablir les pointeurs d?attributs de sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // generation du 2eme VAO
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &EBO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    const char* v = "C:/Users/anise/source/repos/openGL1/vertex.txt";
    const char* f = "C:/Users/anise/source/repos/openGL1/fragment.txt";
    compile.Load_file_shaderPath(v, f);
    compile.load_file();
    buffer::AddBuffer ADD;
    std::vector<GLuint*> vec2;
    std::vector<GLuint*> vec1;
    float pos = 0;
    int success;
    float borederColor[] = { 0.9f, 1.0f,0.2f, 0.5f };
    int width, height, nrChanels, width2, height2, nrChanels2;
    // textures 
    GLuint texture1;
    GLuint texture2;
    // tex 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borederColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("img/containerBois.jpg", &width, &height, &nrChanels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    //
        // fin de la texture1
//tex 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load(("img/containerBois2.jpg"), &width, &height, &nrChanels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << " erreur lors de la generation des textures " << std::endl;
    }
    stbi_image_free(data);

    // light VAO

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // allocation des samplers dans les shaders
    compile.Use_second_program_shader();
    glUniform1i(glGetUniformLocation(compile.get_shader(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(compile.get_shader(), "texture2"), 1);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glUniformMatrix3fv(glGetUniformLocation(compile.get_shader(), "lightColor"), 1, GL_FALSE, glm::value_ptr(lightColor));
    //
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    unsigned int transformLoc = glGetUniformLocation(compile.get_shader(), "transform");
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    int modelLoc = glGetUniformLocation(compile.get_shader(), "model");
    int projectionLoc = glGetUniformLocation(compile.get_shader(), "projection");
    int viewLoc = glGetUniformLocation(compile.get_shader(), "view");
    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    float camY = tan(glfwGetTime()) * radius;
    float currentFrame = 0, deltaTime = 0, lastFrame = 0; float frame = 0;
    Camera camera(currentFrame);
    // camera object
    float xpos = 400; float ypos = 400;
    float sensivity = 0.10f;
    float Yaw; float Pitch;
    while (!glfwWindowShouldClose(window)) // boucle de rendu
    {
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetCursorPosCallback(window, mouse_callback);

        frame++;
        camera.setCamFront(frontCallback);
        projection = glm::mat4(1.0f);
        transform = glm::mat4(1.0f);
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
         // make sure to initialize matrix to identity matrix first
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            transform = glm::translate(transform, glm::vec3(0.0f, -0.0f, 1.0f));
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.5f, 0.0f, 0.7f));
        }
        else {
            transform = glm::translate(transform, glm::vec3(0.0f, -0.0f, 0.0f));
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 1.0f));
        }
        camera.processInputCamera(window, deltaTime);
        pos += 0.00030;
        process_input(window);
        glClearColor(0.9f, 0.93f, 0.25f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        compile.Use_second_program_shader();
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glBindVertexArray(VAO[0]);
        glUniform1f(glGetUniformLocation(compile.get_shader(), "position"), pos);
        projection = glm::perspective(glm::radians(fov), (float)resFx / (float)resFy, 0.1f, 100.0f);

        for (int i(0); i < 10; i++) {
            model = glm::mat4(1.0f);
            view = glm::mat4(1.0f);
            radius = 10.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            float camY = sin(glfwGetTime()) * radius;
            model = glm::translate(model, cubePosition[i]);
            float angle = 20.0f * i;
            if (camera.getCamPos() == glm::vec3(1.0f)) {
                std::cout << " failure " << std::endl;
            }
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            view = glm::lookAt(camera.getCamPos(), camera.getCamPos() - camera.getFrontCam(), camera.getUpCam());
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // now with the uniform matrix being replaced with new transformations, draw it again.
        ImGui::Begin("Dev_ninis");
        ImGui::Button("ANIS LE PROG"); ImGui::Button("G"); ImGui::Button("B");
        ImGui::Text("Anis");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glEnable(GL_DEPTH_TEST);
        
        framebuffer_size_callback(window, resX2, resY2);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO[0]);
    glDeleteBuffers(1, &VBO[0]);
    compile.~compileShaders();
    glfwTerminate();

}
