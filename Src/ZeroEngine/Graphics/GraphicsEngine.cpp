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


    GraphicsEngine::GraphicsEngine() :
        m_window{},
        m_debug{},
        m_physicalDevice{},
        m_logicalDevice{}
    {
        CreateInstance();

        m_debug.SetupDebugMessenger(m_instance, m_enableValidationLayers);

        m_window.CreateSurface(m_instance);

        m_physicalDevice.PickPhysicalDevice(m_instance, m_window.GetSurface());

        m_logicalDevice.CreateLogicalDevice(
            m_physicalDevice.GetPhysicalDevice(),
            m_window.GetSurface(), 
            m_enableValidationLayers,
            m_physicalDevice.GetDeviceExtensions(),
            validationLayers
        );
    }

    bool GraphicsEngine::WindowProcessMessage()
    {
        return m_window.ProcessMessage();
    }

    GraphicsEngine::~GraphicsEngine()
    {
        m_logicalDevice.DestroyLogicalDevice();
        m_debug.DestroyDebugUtlisMessenger(m_instance,m_enableValidationLayers);
        m_window.DestroySurface(m_instance);
        vkDestroyInstance(m_instance,nullptr);
    }

}