#include "../include/ft_scop.h"
extern bool mode;
extern bool firstMouse;
extern float deltaTime0f;
extern float lastFrame0f;
extern float lastX, lastY;
extern float yaw, pitch;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if(cam->fov>= 1.0f && cam->fov <= 45.0f)
        cam->fov -= yoffset;
    if(cam->fov <= 1.0f)
        cam->fov= 1.0f;
    if(cam->fov >= 45.0f)
        cam->fov = 1.0f;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if(pitch > 89.0f)
        pitch = 89.0f; 
    if(pitch < -89.0f)
        pitch = -89.0f;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
 if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
    {
        if(mode == 1)
            (mode) = 0;
        else
            (mode) = 1;
    }
}