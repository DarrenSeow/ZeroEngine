#include "pch.h"
#include "ZeroVkLogicalDevice.h"

#include "QueueFamilyIndices.h"
#include "ZeroVkHelper.h"
#include <set>
namespace ZeroEngine
{
    void ZeroVkLogicalDevice::DestroyLogicalDevice()
    {
        vkDestroyDevice(m_device, nullptr);
    }
    const VkDevice& ZeroVkLogicalDevice::GetDevice()
    {
        // TODO: insert return statement here
        return m_device;
    }

    const VkQueue& ZeroVkLogicalDevice::GetGraphicsQueue()
    {
        // TODO: insert return statement here
        return m_graphicsQueue;
    }

    const VkQueue& ZeroVkLogicalDevice::GetPresentQueue()
    {
        // TODO: insert return statement here
        return m_presentQueue;
    }

    ZeroVkLogicalDevice::ZeroVkLogicalDevice() :
        m_device{VK_NULL_HANDLE},
        m_graphicsQueue{},
        m_presentQueue{}
    {
    }
    void ZeroVkLogicalDevice::CreateLogicalDevice(
        const VkPhysicalDevice& _physicalDevice, 
        const VkSurfaceKHR& _surface,
        const bool _enableValidationLayers, 
        const std::vector<const char*> _deviceExtensions, 
        const std::vector<const char*> _validationLayers)
    {
        QueueFamilyIndices indices = FindQueueFamilies(_physicalDevice, _surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(_deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = _deviceExtensions.data();

        if (_enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
            createInfo.ppEnabledLayerNames = _validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(m_device, indices.m_graphicsFamily.value(), 0, &m_graphicsQueue);
        vkGetDeviceQueue(m_device, indices.m_presentFamily.value(), 0, &m_presentQueue);
    }

}