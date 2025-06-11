#include "../includes/Includes.h"

Window::Window(uint32_t width, uint32_t height, const std::string &title) {
  this->width = width;
  this->height = height;
  this->title = title;
}

Window::~Window() {}
void Window::framebufferResizeCallback(GLFWwindow *window, int width,
                                       int height) {
  auto win = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  win->setBufferResized(true);
}
void Window::init() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void Window::createSurface(VkInstance instance) {
  if (glfwCreateWindowSurface(instance, window, nullptr, &surface) !=
      VK_SUCCESS) {
    throw std::runtime_error("Failed to create window surface!");
  }
}