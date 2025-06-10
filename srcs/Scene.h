#pragma once

#include "Scene/Camera.h"
#include "Scene/Mesh.h"
#include "Scene/Obj3d.h"
#include "Scene/Transform.h"
#include <vector>

class Scene {
public:
  Scene();
  ~Scene();

private:
  std::vector<Obj3d> objs3d;
  std::vector<Camera> cameras;
  std::vector<Transform> transforms;
  std::vector<Mesh> meshes;
};
