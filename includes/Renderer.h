#pragma once

#include "Renderer/BufferManager.h"
#include "Renderer/CommandManager.h"
#include "Renderer/DescriptorManager.h"
#include "Renderer/Pipeline.h"
#include "Renderer/SwapChain.h"
#include "Renderer/SyncObjects.h"

class Renderer {
public:
  Renderer();
  ~Renderer();
  void init(VkDevice device, VkPhysicalDevice physicalDevice,
            VkSurfaceKHR surface, GLFWwindow *window, VkQueue graphicsQueue);

  SwapChain swapChain;
  Pipeline pipeline;
  CommandManager commandManager;
  DescriptorManager descriptorManager;
  SyncObjects syncObjects;
  BufferManager bufferManager;

private:
};
