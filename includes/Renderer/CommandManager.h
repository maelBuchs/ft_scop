#pragma once

#include "../Libs.h"
#include <vulkan/vulkan_core.h>

class CommandManager {
public:
  CommandManager();
  ~CommandManager();
  void init(VkDevice device, VkPhysicalDevice physicalDevice,
            VkSurfaceKHR surface);
  VkCommandPool getCommandPool(void) { return commandPool; }
  void createCommandBuffers(std::vector<VkFramebuffer> swapChainFramebuffers,
                            VkRenderPass renderPass,
                            VkPipeline graphicsPipeline, VkBuffer vertexBuffer,
                            VkBuffer indexBuffer,
                            VkPipelineLayout pipelineLayout,
                            std::vector<VkDescriptorSet> descriptorSets,
                            VkExtent2D swapChainExtent, VkDevice device);
  std::vector<VkCommandBuffer> getCommandBuffers() const {
    return commandBuffers;
  }

private:
  void createCommandPool(VkDevice device, VkPhysicalDevice physicalDevice,
                         VkSurfaceKHR surface);
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;
};
