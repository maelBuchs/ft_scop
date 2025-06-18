#pragma once

#include "../Libs.h"
#include <vector>

class SyncObjects {
public:
  SyncObjects();
  ~SyncObjects();
  void init(VkDevice device, std::vector<VkImage> swapChainImages);
  void createSyncObjects(VkDevice device, std::vector<VkImage> swapChainImages);
  std::vector<VkSemaphore> getImageAvailableSemaphores() const {
    return imageAvailableSemaphores;
  }
  std::vector<VkSemaphore> getRenderFinishedSemaphores() const {
    return renderFinishedSemaphores;
  }
  std::vector<VkFence> getInFlightFences() const { return inFlightFences; }
  std::vector<VkFence> getImagesInFlight() const { return imagesInFlight; }
  size_t getCurrentFrame() const { return currentFrame; }
  void setCurrentFrame(size_t frame) { currentFrame = frame; }
  void incrementCurrentFrame(uint32_t max_frames_in_flight) {
    currentFrame = (currentFrame + 1) % max_frames_in_flight;
  }

private:
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  std::vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;
};
