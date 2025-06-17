#pragma once

#include "Renderer/BufferManager.h"
#include "Scene/Camera.h"
#include "Scene/Mesh.h"
#include "Scene/Obj3d.h"
#include "Scene/Transform.h"
#include <vector>

class Scene {
public:
  Scene() {};
  ~Scene();
  void createCube();

  BufferManager *bufferManager;

  std::vector<Obj3d> objs3d;
  std::vector<Mesh> meshes;

private:
  std::vector<Camera> cameras;
  std::vector<Transform> transforms;
};
