#pragma once

#include "../Libs.h"

class DescriptorManager {
public:
  DescriptorManager();
  ~DescriptorManager();

private:
  VkDescriptorPool descriptorPool;
  std::vector<VkDescriptorSet> descriptorSets;
};
