#include "../../includes/Includes.h"

DescriptorManager::DescriptorManager() {}

DescriptorManager::~DescriptorManager() {}

void DescriptorManager::createDescriptorPool(
    VkDevice device, std::vector<VkImage> swapChainImages) {
  VkDescriptorPoolSize poolSize{};
  poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSize.descriptorCount = static_cast<uint32_t>(swapChainImages.size());

  VkDescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = 1;
  poolInfo.pPoolSizes = &poolSize;
  poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

  if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) !=
      VK_SUCCESS) {
    throw std::runtime_error("Failed to create Pool Descriptor");
  }
}

void DescriptorManager::createDescriptorSet(
    VkDevice device, VkDescriptorSetLayout descriptorSetLayout,
    BufferManager bufferManager, std::vector<VkImage> swapChainImages,
    std::vector<VkImageView> swapChainImageViews) {
  std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(),
                                             descriptorSetLayout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
  allocInfo.pSetLayouts = layouts.data();

  descriptorSets.resize(swapChainImages.size());

  std::vector<BufferInfo> uniformBuffers = bufferManager.getUniformBuffers();
  
  if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) !=
      VK_SUCCESS) {
    throw std::runtime_error("echec de l'allocation d'un set de descripteurs!");
  }

  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffers[i].buffer;
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = descriptorSets[i];
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pBufferInfo = &bufferInfo;
    descriptorWrite.pImageInfo = nullptr;
    descriptorWrite.pTexelBufferView = nullptr;
    vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
  }
}

void DescriptorManager::init(
    VkDevice device, VkPhysicalDevice physicalDevice,
    VkDescriptorSetLayout descriptorSetLayout, BufferManager bufferManager,
    const std::vector<VkImage> &swapChainImages,
    const std::vector<VkImageView> &swapChainImageViews) {
  createDescriptorPool(device, swapChainImages);
  createDescriptorSet(device, descriptorSetLayout, bufferManager,
                      swapChainImages, swapChainImageViews);
}