#pragma once

#include "../Libs.h"

class SyncObjects {
public:
  SyncObjects();
  ~SyncObjects();

private:
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  std::vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;
};
