#include "../../includes/Includes.h"
#include <vector>
#include <vulkan/vulkan_core.h>

BufferManager::BufferManager() {}

BufferManager::~BufferManager() {}

// BufferID createVertexBuffer(const void *vertices, size_t size) BufferID;
// BufferID createUniformBuffers(size_t size);

BufferID
BufferManager::createIndexBuffer(const std::vector<uint16_t> &indices) {
  if (indices.empty()) {
    std::cerr << "Warning: Tried to create empty index buffer" << std::endl;
    return INVALID_BUFFER_ID;
  }

  VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
  VkBuffer indexBuffer;
  VkDeviceMemory indexBufferMemory;
  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  BufferInfo bufferInfo;
  bufferInfo.id = nextID++;

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
  bufferInfo.buffer = indexBuffer;
  bufferInfo.memory = indexBufferMemory;
  buffers[bufferInfo.id] = bufferInfo;
  return bufferInfo.id;
}

std::vector<BufferID> BufferManager::createUniformBuffers() {
  VkDeviceSize bufferSize = sizeof(UniformBufferObject);

  std::cout << swapChainImages.size() << "\n";
  for (size_t i = 0; i < swapChainImages.size(); i++) {
    BufferInfo bufferInfo;
    bufferInfo.id = nextID++;
    createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 bufferInfo.buffer, bufferInfo.memory, device, physicalDevice);
    buffers[bufferInfo.id] = bufferInfo;
    uniformBufferIDs.push_back(bufferInfo.id);
    std::cout << "uniform buffer id size : " << uniformBufferIDs.size()
              << std::endl;
  }

  return uniformBufferIDs;
}

BufferID BufferManager::createVertexBuffer(const std::vector<Vertex> vertices) {
  VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  BufferInfo bufferInfo;
  bufferInfo.id = nextID++;

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
  bufferInfo.buffer = vertexBuffer;
  bufferInfo.memory = vertexBufferMemory;
  buffers[bufferInfo.id] = bufferInfo;
  return bufferInfo.id;
}

std::vector<BufferInfo> BufferManager::getUniformBuffers() const {
  std::vector<BufferInfo> uniformBuffers;
  for (const auto &id : uniformBufferIDs) {
    auto it = buffers.find(id);
    if (it != buffers.end()) {
      uniformBuffers.push_back(it->second);
    } else {
      std::cerr << "Warning: Uniform buffer ID " << id
                << " not found in BufferManager." << std::endl;
    }
  }
  return uniformBuffers;
}

void BufferManager::init(VkDevice device, VkPhysicalDevice physicalDevice,
                         VkCommandPool commandPool, VkQueue graphicsQueue,
                         std::vector<VkImage> swapChainImages) {
  // createVertexBuffer(device, physicalDevice, commandPool, graphicsQueue);
  // createIndexBuffer(device, physicalDevice, graphicsQueue, commandPool);
  // TODO - Send the meshes to BufferManager
  this->device = device;
  this->physicalDevice = physicalDevice;
  this->commandPool = commandPool;
  this->graphicsQueue = graphicsQueue;
  this->swapChainImages = swapChainImages;
  uniformBufferIDs = createUniformBuffers();
  std::cout << "BufferManager initialized successfully!" << std::endl;
}
