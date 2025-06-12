#pragma once

#include "../Libs.h"

class SwapChain {
public:
  SwapChain();
  ~SwapChain();
  void init(VkDevice device, VkPhysicalDevice physicalDevice,
            VkSurfaceKHR surface, GLFWwindow *window);
  VkSwapchainKHR getSwapChain() const { return swapChain; }
  VkExtent2D getSwapChainExtent() const { return swapChainExtent; }
  VkFormat getSwapChainImageFormat() const { return swapChainImageFormat; }
  const std::vector<VkImage> &getSwapChainImages() const {
    return swapChainImages;
  }
  const std::vector<VkImageView> &getSwapChainImageViews() const {
    return swapChainImageViews;
  }
  const std::vector<VkFramebuffer> &getSwapChainFramebuffers() const {
    return swapChainFramebuffers;
  }
  void createFrameBuffers(VkDevice device, VkRenderPass renderPass);

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
