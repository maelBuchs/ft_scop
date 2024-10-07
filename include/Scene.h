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

// Mesh class
typedef struct t_triangle {
  glm::vec3 pos;
  // glm::vec3 normal;
  glm::vec2 textureCoords;
} Triangle;

class Mesh {
  
  std::vector<Triangle> triangles;
  std::vector<glm::vec3> indices;
  glm::mat4 model = glm::mat4(1.0f);
  bool is_displayed;
};

// Texture

class Texture {
  unsigned int ID;
  unsigned int width;
  unsigned int height;


};


// Light
class Light{

};

// Scene
class Scene {

  std::vector<Triangle> triangles; 
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