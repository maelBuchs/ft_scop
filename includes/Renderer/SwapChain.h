#pragma once

#include "../Libs.h"

class SwapChain {
public:
  SwapChain();
  ~SwapChain();
  void init(VkDevice device, VkPhysicalDevice physicalDevice,
            VkSurfaceKHR surface, GLFWwindow *window);

private:
  void createSwapChain(VkDevice device, VkPhysicalDevice physicalDevice,
                       VkSurfaceKHR surface, GLFWwindow *window);
  void createImageViews(VkDevice device);
  VkSwapchainKHR swapChain;
  VkExtent2D swapChainExtent;
  VkFormat swapChainImageFormat;
  std::vector<VkImage> swapChainImages;
  std::vector<VkImageView> swapChainImageViews;
  std::vector<VkFramebuffer> swapChainFramebuffers;
};
