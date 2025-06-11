#include "../includes/Includes.h"

Renderer::Renderer() {}

Renderer::~Renderer() {
  // Cleanup code for Renderer
  // This will typically involve destroying Vulkan objects created in the
  // Renderer such as swap chain, pipeline, command buffers, etc.
}

void Renderer::init(VkDevice device, VkPhysicalDevice VkPhysicalDevice,
                    VkSurfaceKHR surface, GLFWwindow *window) {
  swapChain.init(device, VkPhysicalDevice, surface, window);
}