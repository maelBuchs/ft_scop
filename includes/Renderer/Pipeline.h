#pragma once

#include "../Libs.h"

class Pipeline {
public:
  Pipeline();
  ~Pipeline();
  void init(VkDevice device, VkFormat swapChainImageFormat,
            VkExtent2D swapChainExtent, bool mode);
  VkRenderPass getRenderPass() const { return renderPass; }
  VkPipelineLayout getPipelineLayout() const { return pipelineLayout; }
  VkPipeline getGraphicsPipeline() const { return graphicsPipeline; }
  VkDescriptorSetLayout getDescriptorSetLayout() const {
    return descriptorSetLayout;
  }

private:
  void createRenderPass(VkDevice device, VkFormat swapChainImageFormat);
  void createDescriptorSetLayout(VkDevice device);
  void createGraphicsPipeline(VkDevice device, VkExtent2D swapChainExtent);
  VkRenderPass renderPass;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  VkDescriptorSetLayout descriptorSetLayout;
};
