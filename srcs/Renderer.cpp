#include "../includes/Includes.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::init(VkDevice device, VkPhysicalDevice physicalDevice,
                    VkSurfaceKHR surface, GLFWwindow *window,
                    VkQueue graphicsQueue) {
  swapChain.init(device, physicalDevice, surface, window);
  pipeline.init(device, swapChain.getSwapChainImageFormat(),
                swapChain.getSwapChainExtent(), true);
  swapChain.createFrameBuffers(device, pipeline.getRenderPass());
  commandManager.init(device, physicalDevice, surface);
  bufferManager.init(device, physicalDevice, commandManager.getCommandPool(),
                     graphicsQueue, swapChain.getSwapChainImages());
  std::cout << "Buffer Manager ok" << std::endl;
  descriptorManager.init(
      device, physicalDevice, pipeline.getDescriptorSetLayout(),
      bufferManager.getUniformBuffers(), swapChain.getSwapChainImages(),
      swapChain.getSwapChainImageViews());
  std::cout << "Descriptor Manager ok" << std::endl;
  commandManager.createCommandBuffers(
      swapChain.getSwapChainFramebuffers(), pipeline.getRenderPass(),
      pipeline.getGraphicsPipeline(), bufferManager.getVertexBuffer(),
      bufferManager.getIndexBuffer(), pipeline.getPipelineLayout(),
      descriptorManager.getDescriptorSets(), swapChain.getSwapChainExtent(),
      device);
  std::cout << "Command Manager ok" << std::endl;
  syncObjects.init(device, swapChain.getSwapChainImages());
  std::cout << "Sync Objects ok" << std::endl;
  std::cout << "Renderer initialized successfully!" << std::endl;
}