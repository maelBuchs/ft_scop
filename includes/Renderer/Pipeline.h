#pragma once

#include "../Libs.h"

class Pipeline {
public:
  Pipeline();
  ~Pipeline();

private:
  VkRenderPass renderPass;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  VkDescriptorSetLayout descriptorSetLayout;
};
