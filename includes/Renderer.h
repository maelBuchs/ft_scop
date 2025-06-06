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

private:
  SwapChain swapChain;
  Pipeline pipeline;
  CommandManager commandManager;
  DescriptorManager descriptorManager;
  SyncObjects syncObjects;
  BufferManager bufferManager;
};
