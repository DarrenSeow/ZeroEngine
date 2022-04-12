#include "pch.h"
#include "GraphicsEngine.h"

#include <fstream>
#include <iostream>

namespace ZeroEngine
{
    std::vector<char> GraphicsEngine::ReadShaderFile(const std::string& _path)
    {
        std::ifstream file(_path, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    void GraphicsEngine::CreateInstance()
    {
        VkApplicationInfo appInfo{ };
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Zero Engine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Zero Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo  createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        std::vector<const char*> extensions = GetRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (m_enableValidationLayers)
        {
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            m_debug.PopulateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
            //createInfo.pNext = nullptr;
        }
        else
        {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Instance");
        }
    }

    void GraphicsEngine::CreateVkSurface(const ZeroWindow& _window)
    {
        auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(m_instance, "vkCreateWin32SurfaceKHR");
        VkWin32SurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.hwnd = _window.GetHWND();
        createInfo.hinstance = _window.GetInstance();

        if (!CreateWin32SurfaceKHR || CreateWin32SurfaceKHR(m_instance, &createInfo, nullptr, &m_surface))
        {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void GraphicsEngine::DestroyVkSurface()
    {
        vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
    }


    bool GraphicsEngine::CheckValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    std::vector<const char*> GraphicsEngine::GetRequiredExtensions()
    {
        if (m_enableValidationLayers)
        {
            requiredInstanceExtension.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return requiredInstanceExtension;
    }


    VkDevice GraphicsEngine::GetDevice()
    {
        return m_logicalDevice.GetDevice();
    }

    GraphicsEngine::GraphicsEngine(const ZeroWindow& _window) :
       
        m_debug{},
        m_physicalDevice{},
        m_logicalDevice{}
    {
        CreateInstance();

        m_debug.SetupDebugMessenger(m_instance, m_enableValidationLayers);
        CreateVkSurface(_window);
       // m_window.CreateSurface(m_instance);

        m_physicalDevice.PickPhysicalDevice(m_instance, m_surface);

        m_logicalDevice.CreateLogicalDevice(
            m_physicalDevice.GetPhysicalDevice(),
            m_surface, 
            m_enableValidationLayers,
            m_physicalDevice.GetDeviceExtensions(),
            validationLayers
        );

        m_frameBuffer.CreateSwapChain(
            m_physicalDevice.GetPhysicalDevice(), 
            m_logicalDevice.GetDevice(), 
            m_surface, 
            _window);

        m_frameBuffer.CreateImageViews(m_logicalDevice.GetDevice());
        m_frameBuffer.CreateRenderPass(m_logicalDevice.GetDevice(), m_physicalDevice.GetPhysicalDevice());
       
        m_frameBuffer.CreateGraphicsPipeLine(m_logicalDevice.GetDevice());
        m_frameBuffer.CreateCommandPool(m_logicalDevice.GetDevice(), m_physicalDevice.GetPhysicalDevice(),m_surface);
        m_frameBuffer.CreateFrameBuffers(m_logicalDevice.GetDevice());
        m_frameBuffer.CreateCommandBuffers(m_logicalDevice.GetDevice());
        m_frameBuffer.CreateSyncObjects(m_logicalDevice.GetDevice());
    }



    void GraphicsEngine::DrawFrame(ZeroWindow& _window)
    {
        bool isResized = _window.GetIsResized();
        m_frameBuffer.DrawFrame(m_logicalDevice.GetDevice(),m_logicalDevice.GetGraphicsQueue(), m_logicalDevice.GetPresentQueue(),isResized);
        _window.SetIsResized(isResized);
    }

    GraphicsEngine::~GraphicsEngine()
    {
        m_frameBuffer.CleanUpSwapChain(m_logicalDevice.GetDevice());
        m_frameBuffer.DestroyCommandPool(m_logicalDevice.GetDevice());
        m_logicalDevice.DestroyLogicalDevice();
        m_debug.DestroyDebugUtlisMessenger(m_instance,m_enableValidationLayers);
        DestroyVkSurface();
       
        vkDestroyInstance(m_instance,nullptr);
    }

}