#include "../../includes/Includes.h"
#include <vector>
#include <vulkan/vulkan_core.h>

BufferManager::BufferManager() {}

BufferManager::~BufferManager() {}

void BufferManager::createIndexBuffer(VkDevice device,
                                      VkPhysicalDevice physicalDevice,
                                      VkQueue graphicsQueue,
                                      VkCommandPool commandPool) {
  VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
               stagingBuffer, stagingBufferMemory, device, physicalDevice);

  void *data;
  vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, indices.data(), (size_t)bufferSize);
  vkUnmapMemory(device, stagingBufferMemory);

  createBuffer(bufferSize,
               VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                   VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
               VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer,
               indexBufferMemory, device, physicalDevice);

  copyBuffer(stagingBuffer, indexBuffer, bufferSize, commandPool, device,
             graphicsQueue);

  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void BufferManager::createUniformBuffers(std::vector<VkImage> swapChainImages,
                                         VkDevice device,
                                         VkPhysicalDevice physicalDevice) {
  VkDeviceSize bufferSize = sizeof(UniformBufferObject);

  uniformBuffers.resize(swapChainImages.size());
  uniformBuffersMemory.resize(swapChainImages.size());

  for (size_t i = 0; i < swapChainImages.size(); i++) {
    createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 uniformBuffers[i], uniformBuffersMemory[i], device,
                 physicalDevice);
  }
}

void BufferManager::createVertexBuffer(VkDevice device,
                                       VkPhysicalDevice physicalDevice,
                                       VkCommandPool commandPool,
                                       VkQueue graphicsQueue) {
  VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;

  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
               stagingBuffer, stagingBufferMemory, device, physicalDevice);
  void *data;
  vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, vertices.data(), (size_t)bufferSize);
  vkUnmapMemory(device, stagingBufferMemory);
  createBuffer(bufferSize,
               VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                   VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
               VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer,
               vertexBufferMemory, device, physicalDevice);

  copyBuffer(stagingBuffer, vertexBuffer, bufferSize, commandPool, device,
             graphicsQueue);
  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void BufferManager::init(VkDevice device, VkPhysicalDevice physicalDevice,
                         VkCommandPool commandPool, VkQueue graphicsQueue,
                         std::vector<VkImage> swapChainImages) {
  createVertexBuffer(device, physicalDevice, commandPool, graphicsQueue);
  createIndexBuffer(device, physicalDevice, graphicsQueue, commandPool);
  createUniformBuffers(swapChainImages, device, physicalDevice);
  std::cout << "BufferManager initialized successfully!" << std::endl;
}
