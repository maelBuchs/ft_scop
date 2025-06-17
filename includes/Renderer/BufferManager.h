#pragma once

#include "../Libs.h"
#include <sys/types.h>
#include <unordered_map>
#include <vulkan/vulkan_core.h>

class BufferManager {
public:
  static constexpr BufferID INVALID_BUFFER_ID = -1;

  BufferManager();
  ~BufferManager();

  void init(VkDevice device, VkPhysicalDevice physicalDevice,
            VkCommandPool commandPool, VkQueue graphicsQueue,
            std::vector<VkImage> swapChainImages);

  BufferID createVertexBuffer(const std::vector<Vertex> vertices);
  BufferID createIndexBuffer(const std::vector<uint16_t> &indices);
  std::vector<BufferID> createUniformBuffers();

  VkBuffer getBuffer(BufferID id) const {
    auto it = buffers.find(id);
    if (it != buffers.end()) {
      return it->second.buffer;
    }
    return VK_NULL_HANDLE;
  }
  VkDeviceMemory getBufferMemory(BufferID id) const {
    auto it = buffers.find(id);
    if (it != buffers.end()) {
      return it->second.memory;
    }
    return VK_NULL_HANDLE;
  }
  void destroyBuffer(BufferID id) {
    auto it = buffers.find(id);
    if (it != buffers.end()) {
      vkDestroyBuffer(device, it->second.buffer, nullptr);
      vkFreeMemory(device, it->second.memory, nullptr);
      buffers.erase(it);
    }
  }
  std::vector<BufferInfo> getUniformBuffers() const;
  void cleanup(VkDevice device) { return; }

private:
  std::unordered_map<BufferID, BufferInfo> buffers;
  BufferID nextID = 1;

  std::vector<BufferID> uniformBufferIDs;
  VkDevice device;
  VkPhysicalDevice physicalDevice;
  VkCommandPool commandPool;
  VkQueue graphicsQueue;
  std::vector<VkImage> swapChainImages;
};
