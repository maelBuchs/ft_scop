#pragma once

#include "../Libs.h"
class BufferManager;
class DescriptorManager {
public:
  DescriptorManager();
  ~DescriptorManager();
  void init(VkDevice device, VkPhysicalDevice physicalDevice,
            VkDescriptorSetLayout descriptorSetLayout,
            BufferManager bufferManager,
            const std::vector<VkImage> &swapChainImages,
            const std::vector<VkImageView> &swapChainImageViews);
  std::vector<VkDescriptorSet> getDescriptorSets() const {
    return descriptorSets;
  }
  VkDescriptorPool getDescriptorPool() const { return descriptorPool; }

private:
  void createDescriptorPool(VkDevice device,
                            std::vector<VkImage> swapChainImages);
  void createDescriptorSet(VkDevice device,
                           VkDescriptorSetLayout descriptorSetLayout,
                           BufferManager bufferManager,
                           std::vector<VkImage> swapChainImages,
                           std::vector<VkImageView> swapChainImageViews);
  VkDescriptorPool descriptorPool;
  std::vector<VkDescriptorSet> descriptorSets;
};
