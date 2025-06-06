#pragma once
#include "Device.h"
#include "GUI.h"
#include "Scene.h"

class Window {
public:
  Window();
  ~Window();

private:
  Device device;
  Scene scene;
  GUI gui;

  GLFWwindow *window;
  VkSurfaceKHR surface;
  bool framebufferResized = false;
};
