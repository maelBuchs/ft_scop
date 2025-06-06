#pragma once

#include "Window.h"

class App {
public:
  App();
  ~App();
  void run() {}

private:
  Window window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT callback;
};
