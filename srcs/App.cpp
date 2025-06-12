#include "../includes/Includes.h"

App::App(uint32_t width, uint32_t height, std::string title)
    : window(width, height, title) {}

App::~App() {}

void App::initRenderer() {
  createInstance();
  std::cout << "Instance created OK" << std::endl;
  window.createSurface(instance);
  std::cout << "Surface created OK" << std::endl;
  window.device.pickPhysicalDevice(instance, window.getSurface());
  std::cout << "Physical device picked OK" << std::endl;
  window.device.createLogicalDevice(window.getSurface());
  std::cout << "Logical device created OK" << std::endl;
  window.renderer.init(window.device.getDevice(),
                       window.device.getPhysicalDevice(), window.getSurface(),
                       window.getGLFWWindow(),
                       window.device.getGraphicsQueue());
}

void App::run() {
  window.init();
  std::cout << "Windows init OK" << std::endl;
  initRenderer();
  std::cout << "Renderer init OK" << std::endl;
  mainLoop();
  // cleanup();
}

void App::cleanupSwapChain() {
  auto device = window.device.getDevice();
  auto &swapChain = window.renderer.swapChain;
  auto commandManager = window.renderer.commandManager;
  auto &pipeline = window.renderer.pipeline;
  vkDeviceWaitIdle(device);
  auto &swapChainFramebuffers =
      window.renderer.swapChain.getSwapChainFramebuffers();
  for (size_t i = 0; i < swapChainFramebuffers.size(); i++) {
    vkDestroyFramebuffer(device, swapChainFramebuffers[i], nullptr);
  }

  vkFreeCommandBuffers(
      device, commandManager.getCommandPool(),
      static_cast<uint32_t>(commandManager.getCommandBuffers().size()),
      commandManager.getCommandBuffers().data());

  vkDestroyPipeline(device, pipeline.getGraphicsPipeline(), nullptr);
  vkDestroyPipelineLayout(device, pipeline.getPipelineLayout(), nullptr);
  vkDestroyRenderPass(device, pipeline.getRenderPass(), nullptr);

  auto &swapChainImageViews = swapChain.getSwapChainImageViews();
  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    vkDestroyImageView(device, swapChainImageViews[i], nullptr);
  }

  vkDestroySwapchainKHR(device, swapChain.getSwapChain(), nullptr);

  auto uniformBuffers = window.renderer.bufferManager.getUniformBuffers();

  for (size_t i = 0; i < uniformBuffers.size(); i++) {
    vkDestroyBuffer(device, uniformBuffers[i], nullptr);
    vkFreeMemory(device,
                 window.renderer.bufferManager.getUniformBuffersMemory()[i],
                 nullptr);
  }
  vkDestroyDescriptorPool(
      device, window.renderer.descriptorManager.getDescriptorPool(), nullptr);
}

std::vector<const char *> getRequiredExtensions() {
  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char *> extensions(glfwExtensions,
                                       glfwExtensions + glfwExtensionCount);

  if (enableValidationLayers) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  return extensions;
}

void App::createInstance() {
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  std::string appName = window.getTitle();
  appInfo.pApplicationName = appName.c_str();
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  auto extensions = getRequiredExtensions();
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  createInfo.ppEnabledExtensionNames = extensions.data();

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create Vulkan instance!");
  }
}

void App::cleanup() {
  cleanupSwapChain();

  auto device = window.device.getDevice();
  vkDestroyDescriptorSetLayout(
      device, window.renderer.pipeline.getDescriptorSetLayout(), nullptr);

  window.renderer.bufferManager.cleanup(device);
  auto &syncObjects = window.renderer.syncObjects;
  auto renderFinishedSemaphores = syncObjects.getRenderFinishedSemaphores();
  auto imageAvailableSemaphores = syncObjects.getImageAvailableSemaphores();
  auto inFlightFences = syncObjects.getInFlightFences();
  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
    vkDestroyFence(device, inFlightFences[i], nullptr);
  }

  vkDestroyCommandPool(device, window.renderer.commandManager.getCommandPool(),
                       nullptr);

  vkDestroyDevice(window.device.getDevice(), nullptr);

  vkDestroySurfaceKHR(instance, window.getSurface(), nullptr);
  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(window.getGLFWWindow());

  glfwTerminate();
}