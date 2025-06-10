#pragma once
#include "Device.h"
#include "GUI.h"
#include "Scene.h"

class Window {
public:
  Window(uint32_t width, uint32_t height, const std::string &title);
  ~Window();
  void init();

private:
  // Device device;
  // Scene scene;
  // GUI gui;

  uint32_t width, height;
  std::string title;

  GLFWwindow *window;
  VkSurfaceKHR surface;
  bool framebufferResized = false;
};
