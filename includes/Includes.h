#pragma once
#include "App.h"
#include "Libs.h"
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

const std::vector<const char *> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

#ifndef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};


struct UniformBufferObject {
  alignas(16) glm::mat4 model;
  alignas(16) glm::mat4 view;
  alignas(16) glm::mat4 proj;
};

// const std::vector<Vertex> vertices = {{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//                                       {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
//                                       {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
//                                       {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};
// const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,
                                     VkSurfaceKHR surface);

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                  VkMemoryPropertyFlags properties, VkBuffer &buffer,
                  VkDeviceMemory &bufferMemory, VkDevice device,
                  VkPhysicalDevice physicalDevice);

void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size,
                VkCommandPool commandPool, VkDevice device,
                VkQueue graphicsQueue);

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties,
                        VkPhysicalDevice physicalDevice);

void updateUniformBuffer(uint32_t currentImage, VkDevice device,
                         VkExtent2D swapChainExtent,
                         std::vector<VkDeviceMemory> &uniformBuffersMemory);