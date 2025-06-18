#pragma once
#include "Libs.h"
class Window;
class Device {
public:
  Device();
  ~Device();
  void pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
  void createLogicalDevice(VkSurfaceKHR surface);
  VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }
  VkDevice getDevice() const { return device; }
  VkQueue getGraphicsQueue() const { return graphicsQueue; }
  VkQueue getPresentQueue() const { return presentQueue; }

private:
  VkPhysicalDevice physicalDevice;
  VkDevice device;
  VkQueue graphicsQueue;
  VkQueue presentQueue;
};
