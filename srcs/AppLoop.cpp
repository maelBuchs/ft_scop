#include "../includes/Includes.h"

void App::mainLoop() {
  while (!glfwWindowShouldClose(window.getGLFWWindow())) {
    glfwPollEvents();
    drawFrame();
  }
  vkDeviceWaitIdle(window.device.getDevice());
}

void App::recreateSwapChain() {
  int width = 0, height = 0;
  glfwGetFramebufferSize(window.getGLFWWindow(), &width, &height);
  while (width == 0 || height == 0) {
    glfwGetFramebufferSize(window.getGLFWWindow(), &width, &height);
    glfwWaitEvents();
  }

  vkDeviceWaitIdle(window.device.getDevice());

  cleanupSwapChain();

  window.renderer.swapChain.init(window.device.getDevice(),
                                 window.device.getPhysicalDevice(),
                                 window.getSurface(), window.getGLFWWindow());
  window.renderer.pipeline.init(
      window.device.getDevice(),
      window.renderer.swapChain.getSwapChainImageFormat(),
      window.renderer.swapChain.getSwapChainExtent(), false);
  window.renderer.swapChain.createFrameBuffers(
      window.device.getDevice(), window.renderer.pipeline.getRenderPass());

  window.renderer.bufferManager.createUniformBuffers(
      window.renderer.swapChain.getSwapChainImages(), window.device.getDevice(),
      window.device.getPhysicalDevice());
  window.renderer.descriptorManager.init(
      window.device.getDevice(), window.device.getPhysicalDevice(),
      window.renderer.pipeline.getDescriptorSetLayout(),
      window.renderer.bufferManager.getUniformBuffers(),
      window.renderer.swapChain.getSwapChainImages(),
      window.renderer.swapChain.getSwapChainImageViews());
  window.renderer.commandManager.createCommandBuffers(
      window.renderer.swapChain.getSwapChainFramebuffers(),
      window.renderer.pipeline.getRenderPass(),
      window.renderer.pipeline.getGraphicsPipeline(),
      window.renderer.bufferManager.getVertexBuffer(),
      window.renderer.bufferManager.getIndexBuffer(),
      window.renderer.pipeline.getPipelineLayout(),
      window.renderer.descriptorManager.getDescriptorSets(),
      window.renderer.swapChain.getSwapChainExtent(),
      window.device.getDevice());
}

void App::drawFrame() {
  uint32_t imageIndex;
  auto &syncObjects = window.renderer.syncObjects;
  auto device = window.device;
  auto &swapChain = window.renderer.swapChain;
  auto &bufferManager = window.renderer.bufferManager;
  auto &commandManager = window.renderer.commandManager;

  VkFence fence =
      syncObjects.getInFlightFences()[syncObjects.getCurrentFrame()];
  vkWaitForFences(device.getDevice(), 1, &fence, VK_TRUE, UINT64_MAX);

  VkResult result = vkAcquireNextImageKHR(
      device.getDevice(), swapChain.getSwapChain(), UINT64_MAX,
      syncObjects.getImageAvailableSemaphores()[syncObjects.getCurrentFrame()],
      VK_NULL_HANDLE, &imageIndex);

  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    recreateSwapChain();
    return;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error(
        "échec de la présentation d'une image à la swap chain!");
  }

  if (syncObjects.getImagesInFlight()[imageIndex] != VK_NULL_HANDLE) {
    vkWaitForFences(device.getDevice(), 1,
                    &syncObjects.getImagesInFlight()[imageIndex], VK_TRUE,
                    UINT64_MAX);
  }
  syncObjects.getImagesInFlight()[imageIndex] =
      syncObjects.getInFlightFences()[syncObjects.getCurrentFrame()];

  std::vector<VkDeviceMemory> uniformBuffersMemory =
      bufferManager.getUniformBuffersMemory();
  updateUniformBuffer(imageIndex, device.getDevice(),
                      swapChain.getSwapChainExtent(), uniformBuffersMemory);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  VkSemaphore waitSemaphores[] = {
      syncObjects.getImageAvailableSemaphores()[syncObjects.getCurrentFrame()]};
  VkPipelineStageFlags waitStages[] = {
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  submitInfo.commandBufferCount = 1;
  auto commandBuffers = commandManager.getCommandBuffers();
  submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

  VkSemaphore signalSemaphores[] = {
      syncObjects.getRenderFinishedSemaphores()[syncObjects.getCurrentFrame()]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;
  vkResetFences(
      device.getDevice(), 1,
      &syncObjects.getInFlightFences()[syncObjects.getCurrentFrame()]);

  if (vkQueueSubmit(
          device.getGraphicsQueue(), 1, &submitInfo,
          syncObjects.getInFlightFences()[syncObjects.getCurrentFrame()]) !=
      VK_SUCCESS) {
    throw std::runtime_error("échec de l'envoi d'un command buffer!");
  }

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = {swapChain.getSwapChain()};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &imageIndex;

  presentInfo.pResults = nullptr;
  vkQueuePresentKHR(device.getPresentQueue(), &presentInfo);

  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
      window.isBufferResized()) {
    window.setBufferResized(false);
    recreateSwapChain();
  } else if (result != VK_SUCCESS) {
    throw std::runtime_error("échec de la présentation d'une image!");
  }

  vkQueueWaitIdle(device.getPresentQueue());
  syncObjects.incrementCurrentFrame(MAX_FRAMES_IN_FLIGHT);
}

