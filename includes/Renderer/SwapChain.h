#pragma once

#include "../Libs.h"

class SwapChain {
public:
  SwapChain();
  ~SwapChain();

private:
  VkSwapchainKHR swapChain;
  VkExtent2D swapChainExtent;
  VkFormat swapChainImageFormat;
  std::vector<VkImage> swapChainImages;
  std::vector<VkImageView> swapChainImageViews;
  std::vector<VkFramebuffer> swapChainFramebuffers;
};
