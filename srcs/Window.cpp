#include "../includes/Includes.h"

Window::Window(uint32_t width, uint32_t height, const std::string &title) {
  this->width = width;
  this->height = height;
  this->title = title;
}

Window::~Window() {}

void Window::init() {
  /*
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
  */

  std::cout << title << std::endl;
}
