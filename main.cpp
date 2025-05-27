#devine GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <stdexcept>

class HelloTriangleApplication {
public:
  void run() {
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  void initWindow() {}

  void initVulkan() {}

  void mainLoop() {}

  void cleanup() {}
};

void run() {
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
}

int main() {
  HelloTriangleApplication app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
