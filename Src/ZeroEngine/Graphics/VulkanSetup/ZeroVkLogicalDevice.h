#pragma once

#include <vulkan\vulkan.hpp>
namespace ZeroEngine
{
	class ZeroVkLogicalDevice
	{
		VkDevice m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;

	public:
		ZeroVkLogicalDevice();

		void CreateLogicalDevice(
			const VkPhysicalDevice& _physicalDevice,
			const VkSurfaceKHR& _surface,
			const bool _enableValidationLayers,
			const std::vector<const char*> _deviceExtensions,
			const std::vector<const char*> _validationLayers
			);

		void DestroyLogicalDevice();
		const VkDevice& GetDevice();
		const VkQueue& GetGraphicsQueue();
		const VkQueue& GetPresentQueue();
	};
}