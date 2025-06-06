#pragma once
#include "Libs.h"

class Device {
public:
  Device();
  ~Device();

private:
  VkPhysicalDevice physicalDevice;
  VkDevice device;
  VkQueue graphicsQueue;
  VkQueue presentQueue;
};
