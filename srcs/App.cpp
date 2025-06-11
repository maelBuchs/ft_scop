#include "../includes/Includes.h"

App::App(uint32_t width, uint32_t height, std::string title)
    : window(width, height, title) {}

App::~App() {}

void App::run() {
  window.init();
  std::cout << "Windows init OK" << std::endl;
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
                       window.getGLFWWindow());

  // createRenderPass();
  // createDescriptorSetLayout();
  // createGraphicsPipeline();
  // createFramebuffers();
  // createCommandPool();
  // createVertexBuffer();
  // createIndexBuffer();
  // createUniformBuffers();
  // createDescriptorPool();
  // createDescriptorSet();
  // createCommandBuffers();
  // createSyncObjects();
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
