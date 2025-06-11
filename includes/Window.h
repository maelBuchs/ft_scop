#pragma once
#include "Device.h"
#include "GUI.h"
#include "Renderer.h"
#include "Scene.h"
#include <vulkan/vulkan_core.h>

class App;
class Window {
public:
  Window(uint32_t width, uint32_t height, const std::string &title);
  ~Window();
  void init();
  static void framebufferResizeCallback(GLFWwindow *window, int width,
                                        int height);
  void createSurface(VkInstance instance);
  bool isBufferResized() { return framebufferResized; }
  void setBufferResized(bool i) { framebufferResized = i; }
  std::string getTitle() { return title; }
  VkSurfaceKHR getSurface() { return surface; }
  GLFWwindow *getGLFWWindow() { return window; }
  uint32_t getWidth() { return width; }
  uint32_t getHeight() { return height; }
  
  Device device;
  Renderer renderer;
  // Scene scene;
  // GUI gui;

private:
  uint32_t width, height;
  std::string title;

  bool framebufferResized = false;
  GLFWwindow *window;
  VkSurfaceKHR surface;
};
