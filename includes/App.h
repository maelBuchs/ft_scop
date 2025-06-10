#pragma once

#include "Window.h"

class App {
public:
  App(uint32_t width, uint32_t height, std::string title);
  ~App();
  void run();

private:
  Window window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT callback;
};
