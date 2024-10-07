#ifndef SCENE_H
#define SCENE_H
#include "Camera.h"
#include "Shader.h"
#include "defines.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <vector>
#include "stb_image.h"
// Texture

class Texture {

  public :
    Texture(std::string path);
    ~Texture();
    unsigned int ID = 0;
    int width;
    int height;

};


// Mesh class
typedef struct t_triangle {
  glm::vec3 pos;
  // glm::vec3 normal;
  glm::vec2 textureCoords;
} Triangle;

class Mesh {
  Mesh();
  ~Mesh();

  void addVertices(float x, float y, float z, float normal,float v, float n);
  void removeVertices();
  void addIndices(int a, int b, int c);
  std::vector<Triangle> triangles;
  std::vector<glm::vec3> indices;
  glm::mat4 model = glm::mat4(1.0f);
  bool is_displayed;
  Texture texture;
};



// Light
class Light{
  Light();
  ~Light();
};

// Scene
class Scene {

  Scene();
  ~Scene();
  void addCamera(Camera *newCam);
  void addMesh(Mesh *newMesh);
  // void addLight(Light *newLight);

  std::vector<Mesh *> meshes;
  std::vector<Camera *> cameras;
  // std::vector<Light*> lights;
  Shader shaders = Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
  int mainCamera;
};

#endif