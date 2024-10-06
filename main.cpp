#include "include/ft_scop.h"
#include "include/stb_image.h"
#include <cmath>
// #include <GL/gl.h>
// #include <GL/glext.h>


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

void processInput(GLFWwindow *window, float *x, float *y, float *z)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        *(x) = *x + 1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        *(y) = *y + 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        *(x) = *x - 1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        *(y) = *y - 1;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        *(z) = *z + 1;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        *(z) = *z - 1;

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

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
  
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

    Shader myShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    // Set the viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Define vertices
   float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };

    // float texCoords[] = {
    //     0.0f, 0.0f,
    //     1.0f, 0.0f,
    //     0.5f, 1.0f

    // };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Create VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // // Color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int EBO;
    glGenBuffers(1, &EBO);


    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("image.png", &width, &height, &nrChannels, 0);
    unsigned int texture;
        myShader.use();
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glEnableVertexAttribArray(2); 
    // Main loop


    int i = 0;
    float x, y , z = 0;
    while (!glfwWindowShouldClose(window)) {
        std::cout << x << std::endl;
        processInput(window, &x, &y, &z);

        glBindTexture(GL_TEXTURE_2D, texture);
        glClearColor(0.3f, 0.7f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
        
        unsigned int modelLoc = glGetUniformLocation(myShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(myShader.ID, "view");
        // int projectionLoc = glGetUniformLocation(myShader.ID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        // glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(model));
        myShader.setMat4("projection", projection);
       
       
        // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        // glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::rotate(trans, glm::radians(i + 1.0f), glm::vec3(0.0, 0.0, 1.0));
        // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
        // unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (i > 360)
            i = 0;
        i++;
    }

    // Clean up
    glfwTerminate();
    return 0;
}
