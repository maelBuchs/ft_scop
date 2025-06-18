#pragma once

#include "Window.h"

class App {
public:
  App(uint32_t width, uint32_t height, std::string title);
  ~App();
  void run();

private:
  void createInstance();
  void mainLoop();
  void drawFrame();
  void initRenderer();
  void recreateSwapChain();
  void cleanupSwapChain();
  void cleanup();
  Window window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT callback;
};
