//
// Created by kolya on 8/18/2021.
//
#pragma once

#define NOMINMAX

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <iostream>
#include "fstream"
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <optional>
#include "array"
#include <glm/glm.hpp>
#include "imgui.h"
#include "backends/imgui_impl_vulkan.h"

#include "Scene.h"

namespace
{
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
             const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
             const VkAllocationCallbacks* pAllocator,
             VkDebugUtilsMessengerEXT* pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance,
            VkDebugUtilsMessengerEXT debugMessenger,
            const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }
}

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

const std::string MODEL_PATH = "../models/vikingroom.obj";
const std::string TEXTURE_PATH = "../textures/viking.png";

class Renderer {


    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;

        bool isComplete() const
        {
            return graphics_family.has_value() && present_family.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> present_modes;
    };

    // Methods //
    // ======= //
public:
    void run()
    {
        initWindow();
        initVulkan();
        InitializeImgui();
        mainLoop();
        cleanup();
    }

private:
    void initVulkan();

    void initWindow();

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    void pickPhysicalDevice();

    void mainLoop();

    void drawFrame();

    void cleanup();

    void createInstance();

    void createLogicalDevice();

    void createSurface();

    void createSwapChain();

    void createImageViews();

    void createRenderPass();

    void createGraphicsPipeline();

    void createFramebuffers();

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void loadModel();
    void createVertexBuffers();
    void createIndexBuffers();
    void createUniformBuffers();

    void updateUniformBuffer(uint32_t currentImage);

    void createCommandBuffers();

    void createCommandPool();

    void createDepthResources();

    void createImage(uint32_t width, uint32_t height, uint32_t mip_levels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory, VkSampleCountFlagBits numSamples);
    void createTextureImage();

    void createColorResources();

    void createTextureImageView();

    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mip_levels);

    void createTextureSampler();

    void createSyncObjects();

    void createDescriptorSetLayout();
    void createDescriptorPool();

    void createDescriptorSets();

    void recreateSwapChain();

    void cleanupSwapChain();

    void createImguiContext();
    void InitializeImgui();
    void createImguiRenderPass();

    void createImguiCommandPools();
    void createImguiCommandBuffers();
    void createImguiCommandBufferAtIndex(uint32_t ImageIndex);
    void createImguiFramebuffers();

    VkShaderModule createShaderModule(const std::vector<char>& code);

    bool checkValidationLayerSupport();

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

    void setupDebugMessenger();

    bool isDeviceSuitable(VkPhysicalDevice device);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void transitionImageLayout(
            VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mip_levels);

    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    std::vector<const char*> getRequiredExtensions();

    VkSampleCountFlagBits getMaxUsableSampleCount();

    void CreateVertexBufferAndMemoryAtIndex(size_t index);
    void CreateIndexBufferAndMemoryAtIndex(size_t index);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void*  pUserData
            )
    {
        std::cerr << "validation layer" << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    static std::vector<char> readFile(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("failed to open file");
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    // State //
    // ===== //
    VkSurfaceKHR m_Surface;

    GLFWwindow* m_Window = nullptr;

    VkInstance m_Instance;

    VkPhysicalDevice m_PhysDevice;

    VkDevice m_LogicalDevice;

    VkSwapchainKHR m_SwapChain;

    VkQueue graphics_queue;

    VkQueue present_queue;

    VkDescriptorSetLayout m_DescriptorSetLayout;
    VkRenderPass m_RenderPass;
    VkPipelineLayout m_PipelineLayout;

    VkPipeline m_GraphicsPipeline;

    VkCommandPool m_CommandPool;
    VkDescriptorPool m_DescriptorPool;
    std::vector<VkDescriptorSet> m_DescriptorSets;

    std::unordered_map<omp::Vertex, uint32_t> m_UniqueVertices;

    std::vector<VkBuffer> m_VertexBuffers;
    std::vector<VkDeviceMemory> m_VertexBufferMemories;

    std::vector<VkBuffer> m_IndexBuffers;
    std::vector<VkDeviceMemory> m_IndexBufferMemories;

    VkImage m_TextureImage;
    VkDeviceMemory m_TextureImageMemory;
    VkImageView m_TextureImageView;
    VkSampler m_TextureSampler;

    VkImage m_ColorImage;
    VkDeviceMemory m_ColorImageMemory;
    VkImageView m_ColorImageView;

    std::vector<VkBuffer> m_UniformBuffers;
    std::vector<VkDeviceMemory> m_UniformBuffersMemory;

    std::vector<VkImage> m_SwapChainImages;

    std::vector<VkImageView> m_SwapChainImageViews;

    std::vector<VkFramebuffer> m_SwapChainFramebuffers;

    std::vector<VkCommandBuffer> m_CommandBuffers;

    std::vector<VkSemaphore> m_ImageAvailableSemaphores;
    std::vector<VkSemaphore> m_RenderFinishedSemaphores;

    std::vector<VkFence> m_InFlightFences;
    std::vector<VkFence> m_ImagesInFlight;

    VkImage m_DepthImage;
    VkDeviceMemory m_DepthImageMemory;
    VkImageView m_DepthImageView;

    omp::Scene m_CurrentScene;

    VkFormat m_SwapChainImageFormat;

    VkExtent2D m_SwapChainExtent;

    size_t m_CurrentFrame = 0;

    bool m_FramebufferResized = false;

    VkDebugUtilsMessengerEXT debugMessenger;

    VkRenderPass m_ImguiRenderPass;
    VkCommandPool m_ImguiCommandPool;
    std::vector<VkCommandBuffer> m_ImguiCommandBuffers;
    std::vector<VkFramebuffer> m_ImguiFramebuffers;
    VkDescriptorPool m_ImguiDescriptorPool;

    uint32_t m_MipLevels;

    VkSampleCountFlagBits m_MSAASamples = VK_SAMPLE_COUNT_1_BIT;

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    const int MAX_FRAMES_IN_FLIGHT = 2;

};

