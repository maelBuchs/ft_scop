#pragma once

#include "../Libs.h"
#include "../Scene.h"
class CommandManager {
public:
  CommandManager();
  ~CommandManager();
  void init(VkDevice device, VkPhysicalDevice physicalDevice,
            VkSurfaceKHR surface);
  VkCommandPool getCommandPool(void) { return commandPool; }
  void
  createCommandBuffers(const std::vector<VkFramebuffer> &swapChainFramebuffers,
                       VkRenderPass renderPass, VkPipeline graphicsPipeline,
                       VkPipelineLayout pipelineLayout,
                       const std::vector<VkDescriptorSet> &descriptorSets,
                       VkExtent2D swapChainExtent, VkDevice device,
                       const Scene &scene, BufferManager bufferManager);

  std::vector<VkCommandBuffer> getCommandBuffers() const {
    return commandBuffers;
  }

private:
  void createCommandPool(VkDevice device, VkPhysicalDevice physicalDevice,
                         VkSurfaceKHR surface);
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;
};
