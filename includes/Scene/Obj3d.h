#pragma once

#include "../Libs.h"
#include "Mesh.h"
#include <glm/ext/matrix_float4x4.hpp>

class Obj3d {
public:
  Obj3d() {};
  ~Obj3d() {};
  void setMeshIndex(uint32_t in) { meshIndex = in; }
  uint32_t getMeshIndex(void) const { return meshIndex; }
  uint32_t getMeshIndex(void) { return meshIndex; }
  void setModelMatrix(glm::mat4 in) { modelMatrix = in; }

private:
  uint32_t meshIndex;
  glm::mat4 modelMatrix;
  VkDescriptorSet descriptorSet;
};
