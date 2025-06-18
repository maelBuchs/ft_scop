#include "../includes/Includes.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::init(VkDevice device, VkPhysicalDevice physicalDevice,
                    VkSurfaceKHR surface, GLFWwindow *glfwWindow,
                    VkQueue graphicsQueue, Scene scene,
                    std::vector<VkImage> swapChainImages) {
  swapChain.init(device, physicalDevice, surface, glfwWindow);
  pipeline.init(device, swapChain.getSwapChainImageFormat(),
                swapChain.getSwapChainExtent(), true);
  swapChain.createFrameBuffers(device, pipeline.getRenderPass());
  commandManager.init(device, physicalDevice, surface);
  bufferManager.init(device, physicalDevice, commandManager.getCommandPool(),
                     graphicsQueue, swapChain.getSwapChainImages());
  scene.createCube();
  std::cout << "Buffer Manager ok" << std::endl;
  // Extract VkBuffer handles from BufferInfo objects
  std::vector<VkBuffer> uniformBuffers;
  for (const auto &bufInfo : bufferManager.getUniformBuffers()) {
    uniformBuffers.push_back(bufInfo.buffer);
  }
  descriptorManager.init(
      device, physicalDevice, pipeline.getDescriptorSetLayout(), bufferManager,
      swapChain.getSwapChainImages(), swapChain.getSwapChainImageViews());
  std::cout << "Descriptor Manager ok" << std::endl;
  commandManager.createCommandBuffers(
      swapChain.getSwapChainFramebuffers(), pipeline.getRenderPass(),
      pipeline.getGraphicsPipeline(), pipeline.getPipelineLayout(),
      descriptorManager.getDescriptorSets(), swapChain.getSwapChainExtent(),
      device, scene, bufferManager);
  std::cout << "Command Manager ok" << std::endl;
  syncObjects.init(device, swapChain.getSwapChainImages());
  std::cout << "Sync Objects ok" << std::endl;
  std::cout << "Renderer initialized successfully!" << std::endl;
}