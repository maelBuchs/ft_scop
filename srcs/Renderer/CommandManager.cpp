#include "../../includes/Includes.h"
#include <vulkan/vulkan_core.h>

CommandManager::CommandManager() {}

CommandManager::~CommandManager() {}

void CommandManager::createCommandPool(VkDevice device,
                                       VkPhysicalDevice physicalDevice,
                                       VkSurfaceKHR surface) {
  QueueFamilyIndices queueFamilyIndices =
      findQueueFamilies(physicalDevice, surface);

  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
  poolInfo.flags = 0;

  if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) !=
      VK_SUCCESS) {
    throw std::runtime_error("échec de la création d'une command pool!");
  }
}

void CommandManager::init(VkDevice device, VkPhysicalDevice physicalDevice,
                          VkSurfaceKHR surface) {
  createCommandPool(device, physicalDevice, surface);
}

void CommandManager::createCommandBuffers(
    const std::vector<VkFramebuffer> &swapChainFramebuffers,
    VkRenderPass renderPass, VkPipeline graphicsPipeline,
    VkPipelineLayout pipelineLayout,
    const std::vector<VkDescriptorSet> &descriptorSets,
    VkExtent2D swapChainExtent, VkDevice device, const Scene &scene,
    BufferManager bufferManager) {

  commandBuffers.resize(swapChainFramebuffers.size());

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

  if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) !=
      VK_SUCCESS) {
    throw std::runtime_error("Échec de l'allocation des command buffers !");
  }

  for (size_t i = 0; i < commandBuffers.size(); i++) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
      throw std::runtime_error("Erreur lors du début du command buffer !");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = swapChainFramebuffers[i];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainExtent;

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo,
                         VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS,
                      graphicsPipeline);

    for (size_t objIndex = 0; objIndex < scene.objs3d.size(); objIndex++) {
      const Obj3d &obj = scene.objs3d[objIndex];
      const Mesh &mesh = scene.meshes[obj.getMeshIndex()];

      VkBuffer vertexBuffers[] = {
          bufferManager.getBuffer(mesh.getVertexBuffer())};
      VkDeviceSize offsets[] = {0};
      vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

      vkCmdBindIndexBuffer(commandBuffers[i],
                           bufferManager.getBuffer(mesh.getIndexBuffer()), 0,
                           VK_INDEX_TYPE_UINT16);

      // Sélectionne le descriptor set pour cet objet et cette frame
      const VkDescriptorSet &descriptorSet =
          descriptorSets[i * scene.objs3d.size() + objIndex];

      vkCmdBindDescriptorSets(commandBuffers[i],
                              VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout,
                              0, 1, &descriptorSet, 0, nullptr);

      vkCmdDrawIndexed(commandBuffers[i], mesh.indices.size(), 1, 0, 0, 0);
    }

    vkCmdEndRenderPass(commandBuffers[i]);

    if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("Échec de l'enregistrement du command buffer !");
    }
  }
}
