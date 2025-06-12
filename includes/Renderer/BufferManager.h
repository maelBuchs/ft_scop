#pragma once

#include "../Libs.h"

class BufferManager {
public:
  BufferManager();
  ~BufferManager();
  void init(VkDevice device, VkPhysicalDevice physicalDevice,
            VkCommandPool commandPool, VkQueue graphicsQueue,
            std::vector<VkImage> swapChainImages);
  std::vector<VkBuffer> getUniformBuffers() const { return uniformBuffers; }
  VkBuffer getVertexBuffer() const { return vertexBuffer; }
  VkBuffer getIndexBuffer() const { return indexBuffer; }
  std::vector<VkDeviceMemory> getUniformBuffersMemory() {
    return uniformBuffersMemory;
  }
  void createUniformBuffers(std::vector<VkImage> swapChainImages,
                            VkDevice device, VkPhysicalDevice physicalDevice);
  VkDeviceMemory getIndexBufferMemory() const { return indexBufferMemory; }
  void cleanup(VkDevice device) {
    vkDestroyBuffer(device, indexBuffer, nullptr);
    vkFreeMemory(device, indexBufferMemory, nullptr);
    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);
  }

private:
  void createVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice,
                          VkCommandPool commandPool, VkQueue graphicsQueue);
  void createIndexBuffer(VkDevice device, VkPhysicalDevice physicalDevice,
                         VkQueue graphicsQueue, VkCommandPool commandPool);
  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkBuffer indexBuffer;
  VkDeviceMemory indexBufferMemory;
  std::vector<VkBuffer> uniformBuffers;
  std::vector<VkDeviceMemory> uniformBuffersMemory;
};
