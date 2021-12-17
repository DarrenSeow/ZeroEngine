#include "pch.h"
#include "ZeroVkPhysicalDevice.h"

#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "ZeroVkHelper.h"

#include <set>
#include <string>
namespace ZeroEngine
{
    bool ZeroVkPhysicalDevice::IsDeviceSuitable(const VkPhysicalDevice& _physicalDevice,
        const VkSurfaceKHR _surface)
    {
        QueueFamilyIndices indices = FindQueueFamilies(_physicalDevice, _surface);

        bool extensionsSupported = CheckDeviceExtensionSupport(_physicalDevice);

        bool swapChainAdequate = false;
        if (extensionsSupported)
        {
            SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(_physicalDevice, _surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        VkPhysicalDeviceFeatures supportedFeatures;
        vkGetPhysicalDeviceFeatures(_physicalDevice, &supportedFeatures);

        return indices.IsComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }

    bool ZeroVkPhysicalDevice::CheckDeviceExtensionSupport(const VkPhysicalDevice& _physicalDevice)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }
    ZeroVkPhysicalDevice::ZeroVkPhysicalDevice() :
        m_physicalDevice{ VK_NULL_HANDLE }

    {

    }

    void ZeroVkPhysicalDevice::PickPhysicalDevice(
        const VkInstance& _instance,
        const VkSurfaceKHR& _surface)
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

        for (const auto& device : devices)
        {
            if (IsDeviceSuitable(device,_surface))
            {
                m_physicalDevice = device;
                break;
            }
        }

        if (m_physicalDevice == VK_NULL_HANDLE)
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    VkPhysicalDevice ZeroVkPhysicalDevice::GetPhysicalDevice()
    {
        // TODO: insert return statement here
        return m_physicalDevice;
    }
    const std::vector<const char*> ZeroVkPhysicalDevice::GetDeviceExtensions()
    {
        return m_deviceExtensions;
    }
}