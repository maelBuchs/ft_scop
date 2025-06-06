#pragma once

#include "../Libs.h"

class BufferManager {
public:
  BufferManager();
  ~BufferManager();

private:
  VkBuffer vertexBuffer;
  VkDeviceMemory indexBufferMemory;
  VkBuffer indexBuffer;
  VkDeviceMemory vertexBufferMemory;
  std::vector<VkBuffer> uniformBuffers;
  std::vector<VkDeviceMemory> uniformBuffersMemory;
};
