#include "include/ft_scop.h"
#include <GL/gl.h>
#include <GL/glext.h>


// Vertex Shader Source
// const char *vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
std::string loadShader(const char* filePath) {
    std::ifstream shaderFile(filePath);
    
    if (!shaderFile.is_open()) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return "";  // Retourner une chaîne vide en cas d'erreur
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    // Vérifiez les caractères non imprimables
    return shaderStream.str();
}

int checkShaderCompil(unsigned int shader, std::string shaderName, std::string error)
{
    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::"<< shaderName<< "::" <<error << "_FAILED\n" << infoLog << std::endl;
        return -1;  // Exit if the shader compilation fails
    }
    return 0;
}

int initShaders(const char **vertexShaderSource, const char **fragmentShaderSource)
{
    std::string tmp = loadShader(VERTEX_SHADER_PATH);
    *vertexShaderSource = strdup(tmp.c_str());
    std::string tmp2 = loadShader(FRAGMENT_SHADER_PATH);
    *fragmentShaderSource = strdup(tmp2.c_str());
    return 1;
}

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    const char* vertexShaderSource = NULL;
    const char* fragmentShaderSource = NULL;
    initShaders(&vertexShaderSource, &fragmentShaderSource);
    
  
    // Create a window
    GLFWwindow *window = glfwCreateWindow(800, 600, "hello window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    if(checkShaderCompil(vertexShader, "VERTEX_SHADER", "COMPILATION"))
        exit(1);


    // Define vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Create VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    if(checkShaderCompil(fragmentShader, "FRAGMENT_SHADER", "COMPILATION"))
        exit(1);


    // Attach shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    if(checkShaderCompil(shaderProgram, "SHADER_PROGRAM", "LINK"))
       exit(1);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Main loop
    while (!glfwWindowShouldClose(window)) {

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();
    return 0;
}
