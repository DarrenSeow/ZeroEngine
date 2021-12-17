#pragma once

#include <vulkan\vulkan.hpp>
namespace ZeroEngine
{
	class ZeroVkPhysicalDevice
	{
		VkPhysicalDevice m_physicalDevice;
	
		const std::vector<const char*> m_deviceExtensions = 
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		bool IsDeviceSuitable(
			const VkPhysicalDevice&  _physicalDevice,
			const VkSurfaceKHR _surface);

		bool CheckDeviceExtensionSupport(const VkPhysicalDevice& _physicalDevice);
	public:

		ZeroVkPhysicalDevice();

		void PickPhysicalDevice(
			const VkInstance& _instance,
			const VkSurfaceKHR& _surface);
		
		VkPhysicalDevice GetPhysicalDevice();

		const std::vector<const char*> GetDeviceExtensions();


	};
}