#ifndef FT_SCOP_H
#define FT_SCOP_H
#include "Camera.h"
#include "Shader.h"
#include "Scene.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "stb_image.h"
#include <cmath>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string.h>
#include <vector>

#include "defines.h"

extern const char *vertexShaderSource;

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif
