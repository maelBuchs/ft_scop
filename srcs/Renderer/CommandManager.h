#pragma once

#include "../Libs.h"

class CommandManager {
public:
  CommandManager();
  ~CommandManager();

private:
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;
};
